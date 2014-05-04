//
//  Triangle.cpp
//  Raytracer
//
//  Created by Loick Michard on 4/3/14.
//  Copyright (c) 2014 Loick Michard. All rights reserved.
//

#include "Triangle.h"

Triangle::Triangle() {
    
}

void Triangle::init(Vertex *v0,Vertex *v1,Vertex *v2,Material *m) {
    _vtx[0]=v0;
    _vtx[1]=v1;
    _vtx[2]=v2;
    _mtl=m;
    
    _minimum = glm::min(glm::min(_vtx[0]->position, _vtx[1]->position), _vtx[2]->position);
    _maximum = glm::max(glm::max(_vtx[0]->position, _vtx[1]->position), _vtx[2]->position);
    _center = (_vtx[0]->position + _vtx[1]->position + _vtx[2]->position) / 3.0f;
}

bool Triangle::intersect(const Ray &ray, Intersection &hit) {
    
    glm::vec3 P, Q, T;
    float det, inv_det, u, v;
    float t;
    
    glm::vec3 e1 = _vtx[1]->position - _vtx[0]->position;
    glm::vec3 e2 = _vtx[2]->position - _vtx[0]->position;

    P = glm::cross(ray.direction, e2);

    //if determinant is near zero, ray lies in plane of triangle
    det = glm::dot(e1, P);
    //NOT CULLING
    if(det == 0.0)
        return false;
    inv_det = 1.f / det;
    
    //calculate distance from V1 to ray origin
    T = ray.origin - _vtx[0]->position;
    
    //Calculate u parameter and test bound
    u = glm::dot(T, P) * inv_det;
    //The intersection lies outside of the triangle
    if(u < 0.f || u > 1.f) return false;
    
    //Prepare to test v parameter
    Q = glm::cross(T, e1);
    
    //Calculate V parameter and test bound
    v = glm::dot(ray.direction, Q) * inv_det;
    //The intersection lies outside of the triangle
    if(v < 0.f || u + v  > 1.f) return false;
    
    t = glm::dot(e2,Q) * inv_det;
    
    if(t > EPSILON && t < hit.hitDistance - EPSILON) { //ray intersection
        hit.hitDistance = t;
        if (ray.type != Ray::SHADOW) {
            hit.mtl = _mtl;
            hit.light = _light;
            hit.normal = glm::normalize((1-u-v) * _vtx[0]->normal
            + u * _vtx[1]->normal
            + v * _vtx[2]->normal);
            //hit.normal = _vtx[0]->normal;
            hit.position = ray.origin + t * ray.direction;
        }
        return true;
    }
    
    // No hit, no win
    return false;
}
/*
bool Triangle::intersect(const Ray &ray, Intersection &hit) const {
    
    float det, inv_det, alpha, beta;
    float t;
    
    glm::vec3 e1 = _vtx[1]->position - _vtx[0]->position;
    glm::vec3 e2 = _vtx[2]->position - _vtx[0]->position;
    
    det = - glm::dot(ray.direction, glm::cross(e1, e2));
    if(det > -EPSILON && det < EPSILON)
        return false;
    inv_det = 1.f / det;
    
    alpha = - glm::dot(ray.direction, glm::cross(ray.origin - _vtx[0]->position, e2)) * inv_det;
    if(alpha < 0.f || alpha > 1.f) return false;
    
    beta = - glm::dot(ray.direction, glm::cross(e1, ray.origin - _vtx[0]->position)) * inv_det;
    if(beta < 0.f || alpha + beta  > 1.f) return false;
    
    t = glm::dot(ray.origin - _vtx[0]->position, glm::cross(e1, e2)) * inv_det;
    
    if(t > EPSILON && t < hit.hitDistance) { //ray intersection
        hit.hitDistance = t;
        if (ray.type != Ray::SHADOW) {
            hit.mtl = _mtl;
            hit.normal = glm::normalize((1-alpha-beta) * _vtx[0]->normal
                                        + alpha * _vtx[1]->normal
                                        + beta * _vtx[2]->normal);
            //hit.normal = _vtx[2]->normal;
            hit.position = ray.origin + t * ray.direction;
        }
        return true;
    }
    
    // No hit, no win
    return false;
}*/
