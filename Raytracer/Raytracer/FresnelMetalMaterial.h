//
//  FresnelMetalMaterial.h
//  Raytracer
//
//  Created by Loick Michard on 4/22/14.
//  Copyright (c) 2014 Loick Michard. All rights reserved.
//

#ifndef __Raytracer__FresnelMetalMaterial__
#define __Raytracer__FresnelMetalMaterial__

#include <iostream>
#include "Material.h"
#define GLM_SWIZZLE
#include "glm/glm.hpp"

class FresnelMetalMaterial : public Material {
public:
    
    FresnelMetalMaterial(const Color& diffuseColor, float k, float n, float m = 0.2f, float spec = 1.0f);
    
	void computeReflectance(Color &col, const glm::vec3 &in, const glm::vec3 &out, const Intersection &hit, float index) const;
    void computeReflection(Color& col, const glm::vec3& in, glm::vec3& out, const Intersection &hit, float index) const;
    float computeRefraction(Color& col, const glm::vec3& in, glm::vec3& out, const Intersection &hit, float index) const;
    
    void setDiffuseColor(const Color& diffuseColor);
    
private:
	Color _diffuseColor;
    float _n;
    float _k;
    float _m;
    float _spec;
};
#endif /* defined(__Raytracer__FresnelMetalMaterial__) */
