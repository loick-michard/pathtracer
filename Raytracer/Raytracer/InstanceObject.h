//
//  InstanceObject.h
//  Raytracer
//
//  Created by Loick Michard on 4/3/14.
//  Copyright (c) 2014 Loick Michard. All rights reserved.
//

#ifndef __Raytracer__InstanceObject__
#define __Raytracer__InstanceObject__

#include <iostream>
#include "Object.h"
#include "Matrix34.h"
#define GLM_SWIZZLE
#include "glm/glm.hpp"

class InstanceObject : public Object {
public:
    InstanceObject();
    InstanceObject(Object *obj);
    bool intersect(const Ray &ray, Intersection &hit);
    void setChild(Object *obj);
    void setMatrix(glm::mat4 &mtx);
    
private:
    void _computeBox();
    
    glm::mat4 _matrix;
    glm::mat4 _inverse; // Pre-computed inverse of Matrix
    Object *_child;
};

#endif /* defined(__Raytracer__InstanceObject__) */
