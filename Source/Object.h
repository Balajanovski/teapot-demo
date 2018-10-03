// 
// Created by Balajanovski on 2/10/2018.
//

#ifndef TEAPOT_DEMO_OBJECT_H
#define TEAPOT_DEMO_OBJECT_H

#include "Material.h"

#include <glm/glm.hpp>
#include <memory>

class Model;
class Object {
public:
    Object(const std::shared_ptr<Model>& model, const glm::mat4& matrix, const Material& mat);

    void Draw();
    void DrawInstances(unsigned int primcount);

    void ChangeModelMatrix(const glm::mat4 matrix) { model_matrix = matrix; }
    void ChangeMaterial(const Material mat) { material = mat; }

    glm::mat4 getModelMatrix() { return model_matrix; }
    Material getMaterial() { return material; }
    unsigned int getModelKey();
private:
    std::shared_ptr<Model> model;

    glm::mat4 model_matrix;
    Material material;
};


#endif //TEAPOT_DEMO_OBJECT_H
