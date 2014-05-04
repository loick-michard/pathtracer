//
//  BoxTreeObject.cpp
//  Raytracer
//
//  Created by Loick Michard on 4/15/14.
//  Copyright (c) 2014 Loick Michard. All rights reserved.
//

#include "BoxTreeObject.h"

BoxTreeObject::BoxTreeObject() : _root(NULL) {
    
}

BoxTreeObject::~BoxTreeObject() {
    
}

void BoxTreeObject::construct(MeshObject &mesh) {
    auto t_start = std::chrono::high_resolution_clock::now();

    _root = new BoxTreeNode();
    int total = 0;
    int depth = 0;
    Object **objects = new Object*[mesh._numTriangles];
    for (int k = 0; k < mesh._numTriangles; ++k)
        objects[k] = &mesh._triangles[k];
    _root->construct(mesh._numTriangles, objects, total, depth, 0);
    std::cout << "Triangles " << mesh._numTriangles << " total nodes " << total << " depth max " << depth << std::endl;

    auto t_end = std::chrono::high_resolution_clock::now();
    
    std::cout << "Wall clock time passed: "
    << std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_start).count()
    << " ms\n";
    
    _minimum = _root->_min;
    _maximum = _root->_max;
    _center = (_root->_min + _root->_max) / 2.0f;
}

bool BoxTreeObject::intersect(const Ray &ray, Intersection &hit) {
    if  (_root->intersect(ray, hit)) {
        return true;
    }
    return false;
}

void BoxTreeObject::construct(std::vector<Object*>& allObjects) {
    auto t_start = std::chrono::high_resolution_clock::now();
    
    _root = new BoxTreeNode();
    int total = 0;
    int depth = 0;
    Object **objects = new Object*[allObjects.size()];
    for (int k = 0; k < allObjects.size(); ++k)
        objects[k] = allObjects[k];
    _root->construct(allObjects.size(), objects, total, depth, 0);
    std::cout << "Objects " << allObjects.size() << " total nodes " << total << " depth max " << depth << std::endl;
    
    auto t_end = std::chrono::high_resolution_clock::now();
    
    std::cout << "Wall clock time passed: "
    << std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_start).count()
    << " ms\n";
    
    _minimum = _root->_min;
    _maximum = _root->_max;
    _center = (_root->_min + _root->_max) / 2.0f;
}