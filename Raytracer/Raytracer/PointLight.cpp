//
//  PointLight.cpp
//  Raytracer
//
//  Created by Loick Michard on 4/3/14.
//  Copyright (c) 2014 Loick Michard. All rights reserved.
//

#include "PointLight.h"

PointLight::PointLight(const glm::vec3& pos) {
    _pos = pos;
}

float PointLight::illuminate(const glm::vec3 &pos, Color &col, glm::vec3 &toLight, glm::vec3 &ltPos, int k) {
    ltPos = _pos;
    toLight = _pos - pos;
    float bright = _intensity / glm::dot(toLight, toLight);
    toLight = glm::normalize(toLight);
    col = _baseColor;
    
    return bright;
}

float PointLight::getIntensity() {
    return _intensity;
}