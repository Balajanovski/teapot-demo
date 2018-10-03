// 
// Created by Balajanovski on 2/10/2018.
//

#ifndef TEAPOT_DEMO_MATERIAL_H
#define TEAPOT_DEMO_MATERIAL_H

#include <glm/glm.hpp>

struct Material {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
};

#endif //TEAPOT_DEMO_MATERIAL_H
