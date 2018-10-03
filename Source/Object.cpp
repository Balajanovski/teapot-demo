// 
// Created by Balajanovski on 2/10/2018.
//

#include "Object.h"

#include "Util/Model.h"

Object::Object(const std::shared_ptr<Model> &mod, const glm::mat4 &matrix, const Material& mat)
        : model(mod), model_matrix(matrix), material(mat) { }

void Object::Draw() {
    model->Draw();
}

void Object::DrawInstances(unsigned int primcount) {
    model->DrawInstances(primcount);
}

unsigned int Object::getModelKey() {
    return model->getKey();
}