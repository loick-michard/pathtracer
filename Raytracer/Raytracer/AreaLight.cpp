//
//  AreaLight.cpp
//  Raytracer
//
//  Created by Loick Michard on 4/15/14.
//  Copyright (c) 2014 Loick Michard. All rights reserved.
//

#include "AreaLight.h"

AreaLight::AreaLight(Triangle* triangle) : _triangle(triangle) {
    _sampling = 10;
    _area = glm::length(glm::cross(_triangle->_vtx[1]->position - _triangle->_vtx[0]->position, _triangle->_vtx[2]->position - _triangle->_vtx[0]->position)) / 2.f;
}

float AreaLight::illuminate(const glm::vec3 &pos, Color &col, glm::vec3 &toLight, glm::vec3 &ltPos, int k) {
    float u = (1.0f / _samplingW) * ((float)(k % _samplingW) + random01());
    float v = (1.0f / _samplingW) * ((float)(k / _samplingW) + random01());
    float alpha = sqrt(u) * v;
    float beta = 1 - sqrt(u);
    
    ltPos = _triangle->_vtx[0]->position + alpha * (_triangle->_vtx[1]->position - _triangle->_vtx[0]->position) + beta * (_triangle->_vtx[2]->position - _triangle->_vtx[0]->position);
    toLight = glm::normalize(ltPos - pos);
    col = _baseColor;

    return (_intensity / (_area * glm::dot(ltPos - pos, ltPos - pos))) * max(glm::dot(_triangle->_vtx[0]->normal, -toLight), 0.0) / _sampling;
}

float AreaLight::getIntensity() {
    return _intensity / _area;
}