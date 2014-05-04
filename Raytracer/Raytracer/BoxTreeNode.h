//
//  BoxTreeNode.h
//  Raytracer
//
//  Created by Loick Michard on 4/15/14.
//  Copyright (c) 2014 Loick Michard. All rights reserved.
//

#ifndef __Raytracer__BoxTreeNode__
#define __Raytracer__BoxTreeNode__

#include <iostream>
#include "Ray.h"
#include "Intersection.h"
#include "Triangle.h"
#define GLM_SWIZZLE
#include "glm/glm.hpp"

#define MAX_OBJECTS 8

class BoxTreeNode {
public:
    BoxTreeNode();
    ~BoxTreeNode();
    bool intersect(const Ray &ray, Intersection &hit);
    void construct(int count, Object **objects, int& total, int& maxDepth, int depth);

    glm::vec3 _min, _max;

private:
    
    BoxTreeNode *_left, *_right;
    
    Object* _objects[MAX_OBJECTS];
    int _numObjects;
    int _dimension;
};

#endif /* defined(__Raytracer__BoxTreeNode__) */
