//
//  BoxTreeNode.cpp
//  Raytracer
//
//  Created by Loick Michard on 4/15/14.
//  Copyright (c) 2014 Loick Michard. All rights reserved.
//

#include <algorithm>
#include "BoxTreeNode.h"

BoxTreeNode::BoxTreeNode() : _numObjects(0), _left(NULL), _right(NULL) {
    
}

BoxTreeNode::~BoxTreeNode() {
    
}

bool BoxTreeNode::intersect(const Ray &ray, Intersection &hit) {
    float tx1 = (_min.x - ray.origin.x) / ray.direction.x;
    float tx2 = (_max.x - ray.origin.x) / ray.direction.x;
    float ty1 = (_min.y - ray.origin.y) / ray.direction.y;
    float ty2 = (_max.y - ray.origin.y) / ray.direction.y;
    float tz1 = (_min.z - ray.origin.z) / ray.direction.z;
    float tz2 = (_max.z - ray.origin.z) / ray.direction.z;
    
    float tmin = max(max(min(tx1, tx2), min(ty1, ty2)), min(tz1, tz2));
    float tmax = min(min(max(tx1, tx2), max(ty1, ty2)), max(tz1, tz2));
    
    if (tmin <= tmax) {
        if ((tmin <= EPSILON && tmax <= EPSILON) || tmin >= hit.hitDistance - EPSILON)
            return false;
    } else
        return false;
    
    bool result = false;
    if (_numObjects > 0) {
        for (int idx = 0; idx < _numObjects; ++idx) {
            result |= _objects[idx]->intersect(ray, hit);
            if (ray.type == ray.SHADOW && result)
                return true;
        }
        return result;
    }
    
    if (ray.direction[_dimension] > 0) {
        result |= _left->intersect(ray, hit);
        if (ray.type == ray.SHADOW && result)
            return true;
        result |= _right->intersect(ray, hit);
    } else {
        result |= _right->intersect(ray, hit);
        if (ray.type == ray.SHADOW && result)
            return true;
        result |= _left->intersect(ray, hit);
    }
    
    return result;
}

int dim = 0;

bool compare(Object* t1, Object* t2) {
    return (t1->_center[dim] < t2->_center[dim]);
}

void BoxTreeNode::construct(int count, Object **objects, int& total, int& maxDepth, int depth) {
    total += 1;
    //std::cout << count << " " << depth << std::endl;
    if (depth > maxDepth)
        maxDepth = depth;
    
    _min = _max = objects[0]->_minimum;
    for (int idx = 0; idx < count; ++idx) {
        _min = glm::min(_min, objects[idx]->_minimum);
        _max = glm::max(_max, objects[idx]->_maximum);
    }
    
    
    
    if (count <= MAX_OBJECTS) {
        _numObjects = count;
        for (int idx = 0; idx < count; ++idx) {
            _objects[idx] = objects[idx];
        }
        return;
    }
    
    _dimension = 0;
    float size = _max.x - _min.x;
    float split = (_min.x + _max.x) / 2;
    if (_max.y - _min.y > size) {
        _dimension = 1;
        size = _max.y - _min.y;
        split = (_min.y + _max.y) / 2;
    }
    if (_max.z - _min.z > size) {
        _dimension = 2;
        size = _max.z - _min.z;
        split = (_min.z + _max.z) / 2;
    }
    
    Object** left = new Object*[count];
    Object** right = new Object*[count];
    int countLeft=0, countRight=0;
    
    for (int idx = 0; idx < count; ++idx) {
        if (objects[idx]->_center[_dimension] < split) {
            left[countLeft] = objects[idx];
            ++countLeft;
        } else {
            right[countRight] = objects[idx];
            ++countRight;
        }
    }
    //std::cout << dimension << " " << split << " " << count << " " << countLeft << " " << countRight << std::endl;
    
    /*
     if (countLeft == 0) {
     left[countLeft] = right[countRight - 1];
     ++countLeft;
     --countRight;
     }
     if (countRight == 0) {
     right[countRight] = left[countLeft - 1];
     --countLeft;
     ++countRight;
     }
     */
    dim = _dimension;
    if (countLeft == 0 || countRight == 0) {
        std::nth_element(&objects[0], &objects[count / 2], &objects[count], compare);
        countLeft = 0;
        countRight = 0;
        for (int idx = 0; idx < count / 2; ++idx) {
            left[countLeft] = objects[idx];
            ++countLeft;
        }
        for (int idx = count / 2; idx < count; ++idx) {
            right[countRight] = objects[idx];
            ++countRight;
        }
    }
    
    _left = new BoxTreeNode();
    _right = new BoxTreeNode();
    
    _left->construct(countLeft, left, total, maxDepth, depth + 1);
    _right->construct(countRight, right, total, maxDepth, depth + 1);
    
    delete[] left;
    delete[] right;
    
}