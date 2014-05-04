//
//  SphereObject.h
//  Raytracer
//
//  Created by Loick Michard on 4/4/14.
//  Copyright (c) 2014 Loick Michard. All rights reserved.
//

#ifndef __Raytracer__SphereObject__
#define __Raytracer__SphereObject__

#include <iostream>
#include "Object.h"

class SphereObject : public Object {
public:
    SphereObject();
    bool intersect(const Ray &ray,Intersection &hit);
    void setOrigin(const glm::vec3& origin);
    void setRadius(float radius);
private:
    glm::vec3 _origin;
    float _radius;
};

#endif /* defined(__Raytracer__SphereObject__) */
