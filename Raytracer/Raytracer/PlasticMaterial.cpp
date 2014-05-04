//
//  PlasticMaterial.cpp
//  Raytracer
//
//  Created by Loick Michard on 4/23/14.
//  Copyright (c) 2014 Loick Michard. All rights reserved.
//

#include <iostream>
#include "PlasticMaterial.h"
#include "Renderer.h"

PlasticMaterial::PlasticMaterial(const Color& color, float index, float m, float spec) : _color(color), _index(index), _m(m), _spec(spec) {
    
}

void PlasticMaterial::computeReflectance(Color &col, const glm::vec3 &in, const glm::vec3 &out, const Intersection &hit, float index) const {
    col.scale(_color, 1.0 - Material::getFresnelDielectricReflection(-in, hit.normal, 1.0, _index));
    col.addScaled(Color(1.0, 1.0, 1.0), max(_spec * Material::cookTorranceMetal(hit.normal, -out, in, 1.0, _index, _m, Renderer::getInstance().isPhong()), 0.0f));
}

void PlasticMaterial::computeReflection(Color& col, const glm::vec3& in, glm::vec3& out, const Intersection &hit, float index) const {
    Material::getReflectedRay(in, out, hit.normal);
    float n2 = (index == 1.0) ? _index : 1.0;
    col.scale(Color(1.0, 1.0, 1.0), max(Material::getFresnelDielectricReflection(in, hit.normal, index, n2), 0.0f));
}

float PlasticMaterial::computeRefraction(Color& col, const glm::vec3& in, glm::vec3& out, const Intersection &hit, float index) const {
    col = Color(0, 0, 0);
    
    return 1.0;
}