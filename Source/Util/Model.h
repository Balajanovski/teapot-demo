// 
// Created by Balajanovski on 29/09/2018.
//

#ifndef TEAPOT_DEMO_MODEL_H
#define TEAPOT_DEMO_MODEL_H

#include "Mesh.h"

#include <string>
#include <vector>

// Assimp forward declarations
class aiNode;
class aiMesh;
class aiScene;

// Scene forward declaration
class Scene;

class Model {
public:
    Model(const std::string& path, Scene& scene);
    Model() { }
    void Draw();
    void DrawInstances(unsigned int primcount);

    unsigned int getKey() { return key; }
private:
    // Model data
    std::vector<Mesh> meshes;
    std::string directory;
    unsigned int key; // Used to take advantage of instancing

    // Functions
    void loadModel(const std::string& path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
};


#endif //TEAPOT_DEMO_MODEL_H
