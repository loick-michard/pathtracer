//
//  PointLight.h
//  Raytracer
//
//  Created by Loick Michard on 4/3/14.
//  Copyright (c) 2014 Loick Michard. All rights reserved.
//

#ifndef __Raytracer__PointLight__
#define __Raytracer__PointLight__

#include <iostream>
#include "Vector3.h"
#include "Light.h"
#define GLM_SWIZZLE
#include "glm/glm.hpp"

class PointLight : public Light {
public:
    PointLight(const glm::vec3& pos);
    
    float illuminate(const glm::vec3 &pos, Color &col, glm::vec3 &toLight, glm::vec3 &ltPos, int k);
    float getIntensity();

private:
    glm::vec3 _pos;
};

#endif /* defined(__Raytracer__PointLight__) */
