// 
// Created by Balajanovski on 2/10/2018.
//

#ifndef TEAPOT_DEMO_SCENE_H
#define TEAPOT_DEMO_SCENE_H

#include "Object.h"

#include <map>
#include <memory>

class Shader;
class Scene {
public:
    Scene() = default;

    void Draw(Shader& shader);
    std::shared_ptr<Object> AddObject(const std::shared_ptr<Model> &mod, const glm::mat4 &matrix,
                                      const Material& mat);
    void AddObject(const std::shared_ptr<Object> &obj);

    // The model key system is used to ensure model re-use and instancing
    unsigned int GetUnusedModelKey();
private:
    unsigned int next_model_key = 0;

    // Associate objects of the same model key
    std::multimap<unsigned int, std::shared_ptr<Object>> objects;

    static constexpr unsigned char MAX_OBJS_SAME_MODEL = 100;
};


#endif //TEAPOT_DEMO_SCENE_H
