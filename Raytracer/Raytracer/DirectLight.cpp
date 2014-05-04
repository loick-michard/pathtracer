//
//  DirectLight.cpp
//  Raytracer
//
//  Created by Loick Michard on 4/3/14.
//  Copyright (c) 2014 Loick Michard. All rights reserved.
//

#include "DirectLight.h"

DirectLight::DirectLight(const glm::vec3& dir) {
    _dir = glm::normalize(dir);
}

float DirectLight::illuminate(const glm::vec3 &pos, Color &col, glm::vec3 &toLight, glm::vec3 &ltPos, int k) {
    ltPos = pos - (1000000.0f * _dir);
    toLight = glm::normalize(-_dir);
    col = _baseColor;
    
    return _intensity;
}

float DirectLight::getIntensity() {
    return _intensity;
}