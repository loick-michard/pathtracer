//
//  Renderer.c
//  Raytracer
//
//  Created by Loick Michard on 4/3/14.
//  Copyright (c) 2014 Loick Michard. All rights reserved.
//

#include <thread>
#include "Renderer.h"
#include "Ray.h"
#include "Intersection.h"
#include "Material.h"

void Renderer::setImage(float width, float height, sf::Image* image) {
    _width = width;
    _height = height;
    _image = image;
}

void Renderer::render(Scene& scene, Camera& camera) {
    auto t_start = std::chrono::high_resolution_clock::now();
    
    int size = sqrt(_subSamples);
    while (size > _width || size > _height)
        size /= 2;
    for (int x = 0; x < _width; x += _width / size) {
        for (int y = 0; y < _height; y += _height / size) {
            Task task;
            task.startX = x;
            task.startY = y;
            task.endX = min(_width, x + _width / size);
            task.endY = min(_height, y + _height / size);
            _tasks.push_back(task);
        }
    }
    std::random_shuffle(_tasks.begin(), _tasks.end());
    std::thread* threads = new std::thread[_nbThreads];
    for (int i = 0; i < _nbThreads; ++i)
        threads[i] = std::thread(&Renderer::run, this, &scene, &camera);
    for (int i = 0; i < _nbThreads; ++i)
        threads[i].join();
    
    delete[] threads;
    
    auto t_end = std::chrono::high_resolution_clock::now();
    
    std::cout << "Wall clock time passed: "
    << std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_start).count()
    << " ms\n";
    
    if (_image)
        _image->saveToFile("test.bmp");
}

void Renderer::run(Scene* scene, Camera* camera) {
    Ray ray(1.0);
    ray.type = Ray::PRIMARY;
    Color color;
    while (true) {
        Task task;
        {
            std::unique_lock<std::mutex>
            lock(_tasksMutex);
            if (_tasks.empty()) {
                return;
            }
            task = _tasks.front();
            _tasks.pop_front();
        }
        for (float x = (float)task.startX; x < (float)task.endX; x += 1) {
            for (float y = (float)task.startY; y < (float)task.endY; y += 1) {
                color = getPixel(*scene, ray, camera, x, y);
                if (_image)
                    _image->setPixel(x, y, sf::Color(color.getRed(), color.getGreen(), color.getBlue()));
            }
        }
    }
}

Color Renderer::getPixel(Scene& scene, Ray& ray, Camera* camera, float x, float y) {
    Color color = Color(0, 0, 0);
    for (int dx = 0; dx < _antialiasing; ++dx) {
        for (int dy = 0; dy < _antialiasing; ++dy) {
            float sampleX = ((float)dx + ((_jittered) ? random01() : 0.5)) / _antialiasing;
            float sampleY = ((float)dy + ((_jittered) ? random01() : 0.5)) / _antialiasing;
            
            if (_weighted) {
                sampleX = (sampleX < 0.5) ? -0.5 + sqrt(2 * sampleX) : 1.5 - sqrt(2 - 2 * sampleX);
                sampleY = (sampleY < 0.5) ? -0.5 + sqrt(2 * sampleY) : 1.5 - sqrt(2 - 2 * sampleY);
            }
            
            sampleX += x;
            sampleY += y;
            camera->getRay(sampleX / _width, sampleY / _height, ray);
            color.addScaled(getColor(scene, ray), 1.0f / (_antialiasing * _antialiasing));
        }
    }
    return color;
}

Color Renderer::getColor(Scene& scene, const Ray& ray, int depth) {
    Intersection hit;
    if (!scene.intersect(ray, hit) || !hit.mtl)
        return scene.getSkyColor();
    if (glm::dot(-ray.direction, hit.normal) < 0)
        hit.normal = -hit.normal;
    if (hit.light) {
        Color color = hit.light->_baseColor;
        color.scale(hit.light->getIntensity());
        return color;
    }
    
    Color finalColor(0, 0, 0);
    for (Light* light : scene.getLights()) {
        for (int k = 0; k < light->getSampling(); ++k) {
            Color lightColor;
            glm::vec3 toLight;
            glm::vec3 lightPos;
            Color reflectColor;
            
            float bright = light->illuminate(hit.position, lightColor, toLight, lightPos, k);
            if (!(glm::dot(toLight, hit.normal) <= EPSILON || bright <= EPSILON)) {
                hit.mtl->computeReflectance(reflectColor, toLight, ray.direction, hit, ray.index);
                
                if (!reflectColor.isBlack() && isLighted(hit, scene, toLight, lightPos)) {
                    reflectColor.multiply(lightColor);
                    finalColor.addScaled(reflectColor, bright);
                }
            }
        }
    }

    if (depth < 5) {
        glm::vec3 reflection;
        Color reflectionColor;
        hit.mtl->computeReflection(reflectionColor, ray.direction, reflection, hit, ray.index);
        if (!reflectionColor.isBlack() && glm::dot(-ray.direction, hit.normal) > EPSILON) {
            reflectionColor.multiply(getColor(scene, Ray(hit.position, reflection, Ray::REFLECTED, ray.index), depth + 1));
            finalColor.add(reflectionColor);
        }
        
        glm::vec3 refraction;
        Color refractionColor;
        float index = hit.mtl->computeRefraction(refractionColor, ray.direction, refraction, hit, ray.index);
        if (!refractionColor.isBlack() && glm::dot(-ray.direction, hit.normal) > EPSILON) {
            refractionColor.multiply(getColor(scene, Ray(hit.position, refraction, Ray::REFRACTED, index), depth + 1));
            finalColor.add(refractionColor);
        }
    }
    return finalColor;
}

bool Renderer::isLighted(Intersection& hit, Scene& scene, glm::vec3& toLight, glm::vec3& lightPos) {
    Ray lightRay(hit.position, toLight, Ray::SHADOW, 1.0);
    Intersection hit2;
    hit2.hitDistance = glm::length(lightPos - hit.position);
    if (!_shadows || !scene.intersect(lightRay, hit2)) {
        return true;
    }
    return false;
}

void Renderer::enableShadows(bool enable) {
    _shadows = enable;
}

void Renderer::setAntialiasing(int antialiasing) {
    _antialiasing = antialiasing;
}

void Renderer::setAntialiasingJittered(bool enable) {
    _jittered = enable;
}

void Renderer::setAntialiasingWeighted(bool enable) {
    _weighted = enable;
}

void Renderer::setPhong(bool enable) {
    _phong = enable;
}

bool Renderer::isPhong() {
    return _phong;
}
