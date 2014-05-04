//
//  Renderer.h
//  Raytracer
//
//  Created by Loick Michard on 4/3/14.
//  Copyright (c) 2014 Loick Michard. All rights reserved.
//

#ifndef __Raytracer__Renderer__
#define __Raytracer__Renderer__

#include <iostream>
#include <SFML/Graphics.hpp>
#include <deque>
#include <mutex>
#include "Scene.h"
#include "Camera.h"
#include "Ray.h"
#include "Color.h"
#define GLM_SWIZZLE
#include "glm/glm.hpp"

class Renderer {
public:
    
    Renderer() : _shadows(false), _subSamples(5000), _nbThreads(8), _antialiasing(1), _jittered(false), _weighted(false), _phong(false) {}
    Renderer(Renderer const&);

    static Renderer& getInstance() {
        static Renderer instance;
        return instance;
    }
    
    void setImage(float width, float height, sf::Image* image);
    void enableShadows(bool enable);
    void render(Scene& scene, Camera& camera);
    Color getPixel(Scene& scene, Ray& ray, Camera* camera, float x, float y);
    Color getColor(Scene& scene, const Ray& ray, int depth = 0);
    bool  isLighted(Intersection& hit, Scene& scene, glm::vec3& toLight, glm::vec3& lightPos);

    void setAntialiasing(int antialiasing);
    void setAntialiasingJittered(bool enable);
    void setAntialiasingWeighted(bool enable);
    void setPhong(bool enable);
    bool isPhong();

    void run(Scene* scene, Camera* camera);
private:
    
    struct Task {
        int startX;
        int endX;
        int startY;
        int endY;
    };
    
    void operator=(Renderer const&);
    
    float _width, _height;
    sf::Image* _image;
    bool _shadows;
    int _subSamples;
    int _nbThreads;
    
    std::deque<Task> _tasks;
    std::mutex _tasksMutex;
    
    int     _antialiasing;
    bool    _jittered;
    bool    _weighted;
    
    bool    _phong;
};

#endif /* defined(__Raytracer__Renderer__) */
