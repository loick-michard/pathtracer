//
//  DielectricMaterial.cpp
//  Raytracer
//
//  Created by Loick Michard on 4/22/14.
//  Copyright (c) 2014 Loick Michard. All rights reserved.
//

#include "DielectricMaterial.h"
#include "Renderer.h"

DielectricMaterial::DielectricMaterial(float index, float alphaRed, float alphaGreen, float alphaBlue, float m, float spec) : _index(index), _alphaRed(alphaRed), _alphaGreen(alphaGreen), _alphaBlue(alphaBlue), _m(m), _spec(spec) {

}

void DielectricMaterial::computeReflectance(Color &col, const glm::vec3 &in, const glm::vec3 &out, const Intersection &hit, float index) const {
    float n2 = (index == 1.0) ? _index : 1.0;
    col = Color(0.0, 0.0, 0.0);
    col.addScaled(Color(1.0, 1.0, 1.0), max(_spec * Material::cookTorranceMetal(hit.normal, -out, in, index, n2, _m, Renderer::getInstance().isPhong()), 0.0));
}

void DielectricMaterial::computeReflection(Color& col, const glm::vec3& in, glm::vec3& out, const Intersection &hit, float index) const {
    Material::getReflectedRay(in, out, hit.normal);
    float n2 = (index == 1.0) ? _index : 1.0;
    Color intensity = Color(1.0, 1.0, 1.0);
    if (index != 1.0) {
        intensity = Color(exp(-_alphaRed * hit.hitDistance), exp(-_alphaGreen * hit.hitDistance), exp(-_alphaBlue * hit.hitDistance));
    }
    col.scale(intensity, max(Material::getFresnelDielectricReflection(in, hit.normal, index, n2), 0.0));
}

float DielectricMaterial::computeRefraction(Color& col, const glm::vec3& in, glm::vec3& out, const Intersection &hit, float index) const {
    float n2 = (index == 1.0) ? _index : 1.0;
    Color intensity = Color(1.0, 1.0, 1.0);
    if (index != 1.0) {
        intensity = Color(exp(-_alphaRed * hit.hitDistance), exp(-_alphaGreen * hit.hitDistance), exp(-_alphaBlue * hit.hitDistance));
    }
    col.scale(intensity, max(1.0 - Material::getFresnelDielectricReflection(in, hit.normal, index, n2), 0.0f));
    
    Material::getRefractedRay(in, out, hit.normal, index, n2);
    
    return n2;
}