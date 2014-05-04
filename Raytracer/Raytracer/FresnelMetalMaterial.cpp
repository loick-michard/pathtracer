//
//  FresnelMetalMaterial.cpp
//  Raytracer
//
//  Created by Loick Michard on 4/22/14.
//  Copyright (c) 2014 Loick Michard. All rights reserved.
//

#include "FresnelMetalMaterial.h"
#include "Renderer.h"

FresnelMetalMaterial::FresnelMetalMaterial(const Color& diffuseColor, float n, float k, float m, float spec) : _diffuseColor(diffuseColor), _n(n), _k(k), _m(m), _spec(spec) {
}

void FresnelMetalMaterial::computeReflectance(Color &col, const glm::vec3 &in, const glm::vec3 &out, const Intersection &hit, float index) const {
    //col.scale(_diffuseColor, glm::dot(in, hit.normal) * (1.0 - Material::fresnelEquationMetal(hit.normal, -in, _k, _n)));
    //col = _diffuseColor;
    col.scale(_diffuseColor, max(_spec * Material::cookTorranceMetal(hit.normal, -out, in, _n, _k, _m, Renderer::getInstance().isPhong()), 0.0));
}

void FresnelMetalMaterial::computeReflection(Color& col, const glm::vec3& in, glm::vec3& out, const Intersection &hit, float index) const {
    Material::getReflectedRay(in, out, hit.normal);
    col.scale(_diffuseColor, max(Material::fresnelEquationMetal(hit.normal, in, _n, _k), 0.0));
}

float FresnelMetalMaterial::computeRefraction(Color& col, const glm::vec3& in, glm::vec3& out, const Intersection &hit, float index) const {
    col = Color(0.0, 0.0, 0.0);
    
    return 1.0;
}

void FresnelMetalMaterial::setDiffuseColor(const Color& diffuseColor) {
    _diffuseColor = diffuseColor;
}