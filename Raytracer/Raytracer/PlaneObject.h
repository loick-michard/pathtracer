//
//  PlaneObject.h
//  Raytracer
//
//  Created by Loick Michard on 4/4/14.
//  Copyright (c) 2014 Loick Michard. All rights reserved.
//

#ifndef __Raytracer__PlaneObject__
#define __Raytracer__PlaneObject__

#include <iostream>
#include "Object.h"

class PlaneObject : public Object {
public:
    PlaneObject();
    bool intersect(const Ray &ray,Intersection &hit);
    void setOrigin(glm::vec3 origin);

    glm::vec3 _origin;
    glm::vec3 _normal;
    float _distance;
};

#endif /* defined(__Raytracer__PlaneObject__) */
