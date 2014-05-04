//
//  Camera.cpp
//  Raytracer
//
//  Created by Loick Michard on 4/3/14.
//  Copyright (c) 2014 Loick Michard. All rights reserved.
//

#include <iostream>
#include "Camera.h"

Camera::Camera() {

}

void Camera::setFOV(float f) {
    _verticalFOV = PI * f / 180.0;
}

void Camera::setAspect(float a) {
    _aspect = a;
    float hFOV = 2 * atan(_aspect * tan(_verticalFOV / 2));
    topLeft = ((-tanf(hFOV / 2)) * _worldMatrix[0]) + ((tanf(_verticalFOV / 2)) * _worldMatrix[1]) - _worldMatrix[2];
    _w = 2 * tan(hFOV / 2);
    _h = 2 * tan(_verticalFOV / 2);
    //std::cout << topLeft.x << " " << topLeft.y << " " << topLeft.z << " " << std::endl;

}

void Camera::lookAt(const glm::vec3 &pos,const glm::vec3 &target,const glm::vec3 &up) {
    _worldMatrix[3] = pos;
    _worldMatrix[2] = glm::normalize(pos - target);
    _worldMatrix[0] = glm::normalize(glm::cross(up, _worldMatrix[2]));
    _worldMatrix[1] = glm::cross(_worldMatrix[2], _worldMatrix[0]);
    /*std::cout << _worldMatrix.c.x << " " << _worldMatrix.c.y << " " << _worldMatrix.c.z << " " << std::endl;
    std::cout << _worldMatrix.a.x << " " << _worldMatrix.a.y << " " << _worldMatrix.a.z << " " << std::endl;
    std::cout << _worldMatrix.b.x << " " << _worldMatrix.b.y << " " << _worldMatrix.b.z << " " << std::endl;*/
}

void Camera::getRay(float x, float y, Ray& ray) {
    ray.origin = _worldMatrix[3];
    ray.direction = glm::normalize((topLeft + ((x * _w) * _worldMatrix[0]) + ((-y * _h) * _worldMatrix[1])));
    //std::cout << x << " " << y << " " << ray.direction.x << " " << ray.direction.y << " " << ray.direction.z << std::endl;
}