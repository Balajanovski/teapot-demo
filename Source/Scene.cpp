// 
// Created by Balajanovski on 2/10/2018.
//

#include "Scene.h"

#include "Util/Cleanup.h"
#include "Util/Model.h"
#include "Util/Shader.h"

#include <climits>
#include <vector>
#include <string>
#include <glm/gtc/type_ptr.hpp>

void Scene::Draw(Shader& shader) {
    for (unsigned int i = 0; i < next_model_key; ++i) {
        auto range_of_key = objects.equal_range(i);
        unsigned int num_objects = objects.count(i);

        // Set model matrices and materials
        auto iter = range_of_key.first;
        for (unsigned int j = 0; j < num_objects; ++j, ++iter) {
            // Set model matrix
            int model_matrix_loc = glGetUniformLocation(static_cast<GLuint>(shader.ID()),
                                                        (std::string("models[") + std::to_string(j) + "]").c_str());
            glUniformMatrix4fv(model_matrix_loc, 1, GL_FALSE, glm::value_ptr(iter->second->getModelMatrix()));

            // Set object material
            auto material = iter->second->getMaterial();
            int vec_loc = glGetUniformLocation(static_cast<GLuint>(shader.ID()), "material.ambient");
            glUniform3fv(vec_loc, 1, glm::value_ptr(material.ambient));
            vec_loc = glGetUniformLocation(static_cast<GLuint>(shader.ID()), "material.diffuse");
            glUniform3fv(vec_loc, 1, glm::value_ptr(material.diffuse));
            vec_loc = glGetUniformLocation(static_cast<GLuint>(shader.ID()), "material.specular");
            glUniform3fv(vec_loc, 1, glm::value_ptr(material.specular));
            shader.set_float("material.shininess", material.shininess);
        }

        // Draw instances
        range_of_key.first->second->DrawInstances(num_objects);
    }
}

std::shared_ptr<Object> Scene::AddObject(const std::shared_ptr<Model> &mod, const glm::mat4 &matrix,
                      const Material &mat) {
    auto object = std::make_shared<Object>(mod, matrix, mat);
    unsigned int model_key = mod->getKey();

    if (objects.count(model_key) >= MAX_OBJS_SAME_MODEL) {
        throwRuntimeError("Scene error: too many objects of the same model");
    }

    objects.insert(std::make_pair(model_key, object));

    return object;
}

void Scene::AddObject(const std::shared_ptr<Object> &obj) {
    if (objects.count(obj->getModelKey()) >= MAX_OBJS_SAME_MODEL) {
        throwRuntimeError("Scene error: too many objects of the same model");
    }

    objects.insert(std::make_pair(obj->getModelKey(), obj));
}

unsigned int Scene::GetUnusedModelKey() {
    if (next_model_key > UINT_MAX) {
        throwRuntimeError("Scene error: too many models loaded.\nnext_model_key would overflow");
    }

    return next_model_key++;
}