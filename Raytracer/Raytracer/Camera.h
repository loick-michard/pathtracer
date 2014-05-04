//
//  Camera.h
//  Raytracer
//
//  Created by Loick Michard on 4/3/14.
//  Copyright (c) 2014 Loick Michard. All rights reserved.
//

#ifndef __Raytracer__Camera__
#define __Raytracer__Camera__

#include <iostream>
#include "Matrix34.h"
#include "Vector3.h"
#include "Scene.h"
#define GLM_SWIZZLE
#include "glm/glm.hpp"

class Camera {
public:
    Camera();

    void setFOV(float f);
    void setAspect(float a);
    void lookAt(const glm::vec3 &pos, const glm::vec3 &target,const glm::vec3 &up);
    void getRay(float x, float y, Ray& ray);

private:
    
    glm::vec3 _worldMatrix[4];
    float _verticalFOV;
    float _aspect;
    float _w, _h;
    glm::vec3 topLeft;
    glm::vec3 bottomRight;
};

#endif /* defined(__Raytracer__Camera__) */
