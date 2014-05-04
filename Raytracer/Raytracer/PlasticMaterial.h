//
//  PlasticMaterial.h
//  Raytracer
//
//  Created by Loick Michard on 4/23/14.
//  Copyright (c) 2014 Loick Michard. All rights reserved.
//

#ifndef __Raytracer__PlasticMaterial__
#define __Raytracer__PlasticMaterial__

#include <iostream>
#include "Material.h"
#define GLM_SWIZZLE
#include "glm/glm.hpp"

class PlasticMaterial : public Material {
public:
    
    PlasticMaterial(const Color& color, float index, float m=0.2f, float spec=1.0f);
    
	void computeReflectance(Color &col, const glm::vec3 &in, const glm::vec3 &out, const Intersection &hit, float index) const;
    void computeReflection(Color& col, const glm::vec3& in, glm::vec3& out, const Intersection &hit, float index) const;
    float computeRefraction(Color& col, const glm::vec3& in, glm::vec3& out, const Intersection &hit, float index) const;
    
private:
    Color _color;
    float _index;
    float _m;
    float _spec;
};

#endif /* defined(__Raytracer__PlasticMaterial__) */
