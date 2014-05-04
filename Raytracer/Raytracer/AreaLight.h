//
//  AreaLight.h
//  Raytracer
//
//  Created by Loick Michard on 4/15/14.
//  Copyright (c) 2014 Loick Michard. All rights reserved.
//

#ifndef __Raytracer__AreaLight__
#define __Raytracer__AreaLight__

#include <iostream>
#include "Light.h"
#include "Triangle.h"
#define GLM_SWIZZLE
#include "glm/glm.hpp"

class AreaLight : public Light {
public:
    AreaLight(Triangle* triangle);
    
    float illuminate(const glm::vec3 &pos, Color &col, glm::vec3 &toLight, glm::vec3 &ltPos, int k);
    float getIntensity();
    
private:
    Triangle*   _triangle;
    float _area;
};

#endif /* defined(__Raytracer__AreaLight__) */
