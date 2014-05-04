//
//  SphereObject.cpp
//  Raytracer
//
//  Created by Loick Michard on 4/4/14.
//  Copyright (c) 2014 Loick Michard. All rights reserved.
//

#include "SphereObject.h"

SphereObject::SphereObject() {
    _origin = glm::vec3(0.0, 0.0, 0.0);
    _radius = 1.0;
}

bool SphereObject::intersect(const Ray &ray, Intersection &hit) {
    float t = - glm::dot(ray.origin - _origin, ray.direction);
    glm::vec3 q = ray.origin + t * ray.direction;
    glm::vec3 qmc = q - _origin;
    float dot = glm::dot(qmc, qmc);
    if (dot > _radius * _radius)
        return false;

    float a = sqrt(_radius * _radius  - dot);
    
    if (t - a >= EPSILON)
        t = t - a;
    else
        t = t + a;
                    
    if(t > EPSILON && t < hit.hitDistance - EPSILON) { //ray intersection
        hit.hitDistance = t;
        if (ray.type != Ray::SHADOW) {
            hit.mtl = _mtl;
            hit.position = ray.origin + t * ray.direction;
            hit.normal = (hit.position - _origin) / _radius;
        }
        return true;
    }
    return false;
}

void SphereObject::setOrigin(const glm::vec3& origin) {
    _origin = origin;
}

void SphereObject::setRadius(float radius) {
    _radius = radius;
}