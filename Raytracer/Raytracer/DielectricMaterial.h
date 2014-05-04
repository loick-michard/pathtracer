//
//  DielectricMaterial.h
//  Raytracer
//
//  Created by Loick Michard on 4/22/14.
//  Copyright (c) 2014 Loick Michard. All rights reserved.
//

#ifndef __Raytracer__DielectricMaterial__
#define __Raytracer__DielectricMaterial__

#include <iostream>
#include "Material.h"
#define GLM_SWIZZLE
#include "glm/glm.hpp"

class DielectricMaterial : public Material {
public:
    
    DielectricMaterial(float index, float alphaRed=0.0f, float alphaGreen=0.0f, float alphaBlue=0.0f, float m=0.2f, float spec=1.0f);
    
	void computeReflectance(Color &col, const glm::vec3 &in, const glm::vec3 &out, const Intersection &hit, float index) const;
    void computeReflection(Color& col, const glm::vec3& in, glm::vec3& out, const Intersection &hit, float index) const;
    float computeRefraction(Color& col, const glm::vec3& in, glm::vec3& out, const Intersection &hit, float index) const;
    
private:
    float _index;
    float _alphaRed;
    float _alphaGreen;
    float _alphaBlue;
    float _m;
    float _spec;
};

#endif /* defined(__Raytracer__DielectricMaterial__) */
