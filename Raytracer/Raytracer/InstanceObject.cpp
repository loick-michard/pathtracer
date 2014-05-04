//
//  InstanceObject.cpp
//  Raytracer
//
//  Created by Loick Michard on 4/3/14.
//  Copyright (c) 2014 Loick Michard. All rights reserved.
//

#include "InstanceObject.h"

InstanceObject::InstanceObject() {
    _child = nullptr;
}

InstanceObject::InstanceObject(Object *obj) {
    _child = obj;
}

bool InstanceObject::intersect(const Ray &ray, Intersection &hit) {
    Ray ray2((_inverse * glm::vec4(ray.origin, 1.0)).xyz(),
    (_inverse * glm::vec4(ray.direction, 0.0)).xyz(),
    ray.type, ray.index);
    
    if(!_child || !_child->intersect(ray2, hit)) {
        return false;
    }
    
    if (ray.type == Ray::SHADOW)
        return true;
    
    hit.position = (_matrix * glm::vec4(hit.position, 1.0)).xyz();
    hit.normal = glm::normalize((_matrix * glm::vec4(hit.normal, 0.0)).xyz());
    hit.hitDistance = glm::distance(ray.origin, hit.position);
    if (_mtl)
        hit.mtl = _mtl;
    
    return true;
}

void InstanceObject::setChild(Object *obj) {
    _child = obj;
    _computeBox();
}

void InstanceObject::setMatrix(glm::mat4 &mtx) {
    _matrix = mtx;
    _inverse = glm::inverse(mtx);
    _computeBox();
}

void InstanceObject::_computeBox() {
    Object* obj = _child;
    _minimum = _maximum = (_matrix * glm::vec4(obj->_minimum.x, obj->_minimum.y, obj->_minimum.z, 1.0)).xyz();
    _minimum = glm::min(_minimum, (_matrix * glm::vec4(obj->_minimum.x, obj->_minimum.y, obj->_maximum.z, 1.0)).xyz());
    _minimum = glm::min(_minimum, (_matrix * glm::vec4(obj->_minimum.x, obj->_maximum.y, obj->_minimum.z, 1.0)).xyz());
    _minimum = glm::min(_minimum, (_matrix * glm::vec4(obj->_minimum.x, obj->_maximum.y, obj->_maximum.z, 1.0)).xyz());
    _minimum = glm::min(_minimum, (_matrix * glm::vec4(obj->_maximum.x, obj->_minimum.y, obj->_minimum.z, 1.0)).xyz());
    _minimum = glm::min(_minimum, (_matrix * glm::vec4(obj->_maximum.x, obj->_minimum.y, obj->_maximum.z, 1.0)).xyz());
    _minimum = glm::min(_minimum, (_matrix * glm::vec4(obj->_maximum.x, obj->_maximum.y, obj->_minimum.z, 1.0)).xyz());
    _minimum = glm::min(_minimum, (_matrix * glm::vec4(obj->_maximum.x, obj->_maximum.y, obj->_maximum.z, 1.0)).xyz());
    
    _maximum = glm::max(_maximum, (_matrix * glm::vec4(obj->_minimum.x, obj->_minimum.y, obj->_maximum.z, 1.0)).xyz());
    _maximum = glm::max(_maximum, (_matrix * glm::vec4(obj->_minimum.x, obj->_maximum.y, obj->_minimum.z, 1.0)).xyz());
    _maximum = glm::max(_maximum, (_matrix * glm::vec4(obj->_minimum.x, obj->_maximum.y, obj->_maximum.z, 1.0)).xyz());
    _maximum = glm::max(_maximum, (_matrix * glm::vec4(obj->_maximum.x, obj->_minimum.y, obj->_minimum.z, 1.0)).xyz());
    _maximum = glm::max(_maximum, (_matrix * glm::vec4(obj->_maximum.x, obj->_minimum.y, obj->_maximum.z, 1.0)).xyz());
    _maximum = glm::max(_maximum, (_matrix * glm::vec4(obj->_maximum.x, obj->_maximum.y, obj->_minimum.z, 1.0)).xyz());
    _maximum = glm::max(_maximum, (_matrix * glm::vec4(obj->_maximum.x, obj->_maximum.y, obj->_maximum.z, 1.0)).xyz());
    
    _center = (_minimum + _maximum) / 2.0f;
}