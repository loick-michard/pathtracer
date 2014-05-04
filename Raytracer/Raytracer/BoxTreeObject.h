//
//  BoxTreeObject.h
//  Raytracer
//
//  Created by Loick Michard on 4/15/14.
//  Copyright (c) 2014 Loick Michard. All rights reserved.
//

#ifndef __Raytracer__BoxTreeObject__
#define __Raytracer__BoxTreeObject__

#include <iostream>
#include "Object.h"
#include "BoxTreeNode.h"
#include "MeshObject.h"

class BoxTreeObject : public Object {
public:
    BoxTreeObject();
    ~BoxTreeObject();
    void construct(MeshObject &mesh);
    void construct(std::vector<Object*>& objects);
    bool intersect(const Ray &ray, Intersection &hit);
    
private:
    BoxTreeNode*    _root;
};

#endif /* defined(__Raytracer__BoxTreeObject__) */
