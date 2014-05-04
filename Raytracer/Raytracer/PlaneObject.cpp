//
//  PlaneObject.cpp
//  Raytracer
//
//  Created by Loick Michard on 4/4/14.
//  Copyright (c) 2014 Loick Michard. All rights reserved.
//

#include "PlaneObject.h"

PlaneObject::PlaneObject() {
    _origin = glm::vec3(0.0, 0.0, 0.0);
    _normal = glm::normalize(glm::vec3(0.0, 1.0, 0.0));
    _distance = glm::dot(_normal, _origin);
}

void PlaneObject::setOrigin(glm::vec3 origin) {
    _origin = origin;
    _normal = glm::normalize(glm::vec3(0.0, 1.0, 0.0));
    _distance = glm::dot(_normal, _origin);
}

bool PlaneObject::intersect(const Ray &ray, Intersection &hit) {
    float den = glm::dot(ray.direction, _normal);
    if (den > -EPSILON && den < EPSILON)
        return false;
    float t = (_distance - glm::dot(ray.origin, _normal)) / den;
    
    if(t > EPSILON && t < hit.hitDistance - EPSILON) { //ray intersection
        hit.hitDistance = t;
        hit.mtl = _mtl;
        hit.normal = _normal;
        hit.position = ray.origin + t * ray.direction;
        return true;
    }
    return false;
}
