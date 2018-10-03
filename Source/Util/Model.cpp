// 
// Created by Balajanovski on 29/09/2018.
//

#include "Model.h"

#include "Scene.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>

Model::Model(const std::string &path, Scene &scene) {
    key = scene.GetUnusedModelKey();
    loadModel(path);
}

void Model::Draw() {
    for (int i = 0; i < meshes.size(); ++i) {
        meshes[i].Draw();
    }
}

void Model::DrawInstances(unsigned int primcount) {
    for (int i = 0; i < meshes.size(); ++i) {
        meshes[i].DrawInstances(primcount);
    }
}

void Model::loadModel(const std::string& path) {
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(path, aiProcess_FlipUVs |
                                                 aiProcess_Triangulate |
                                                 aiProcess_GenSmoothNormals);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "assimp error: " << import.GetErrorString() << std::endl;
        return;
    }
    directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene) {
    // Process all the node's meshes
    for (int i = 0; i < node->mNumMeshes; ++i) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }

    // Recur on children of node
    for (int i = 0; i < node->mNumChildren; ++i) {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    // Walk through each of the mesh's vertices
    for (int i = 0; i < mesh->mNumVertices; ++i) {
        Vertex vertex;
        glm::vec3 placeholder_vector;
        // positions
        placeholder_vector.x = mesh->mVertices[i].x;
        placeholder_vector.y = mesh->mVertices[i].y;
        placeholder_vector.z = mesh->mVertices[i].z;
        vertex.position = placeholder_vector;
        // normals
        placeholder_vector.x = mesh->mNormals[i].x;
        placeholder_vector.y = mesh->mNormals[i].y;
        placeholder_vector.z = mesh->mNormals[i].z;
        vertex.normal = placeholder_vector;

        vertices.push_back(vertex);
    }

    // Walk through each of the mesh's faces
    for (int i = 0; i < mesh->mNumFaces; ++i) {
        aiFace face = mesh->mFaces[i];
        // retrieve all face's indices and store them
        for (int j = 0; j < face.mNumIndices; ++j) {
            indices.push_back(face.mIndices[j]);
        }
    }

    return Mesh(vertices, indices);
}