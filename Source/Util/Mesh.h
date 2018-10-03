// 
// Created by Balajanovski on 27/09/2018.
//

#ifndef GRAPHICS_DEMO_MESH_H
#define GRAPHICS_DEMO_MESH_H

#include "Vertex.h"

#include <vector>

class Mesh {
public:
    // Mesh data
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
    void Draw();
    void DrawInstances(unsigned int primcount);
private:
    // OpenGL data
    unsigned int vao, vbo, ebo;

    void setupMesh();
};

#endif //GRAPHICS_DEMO_MESH_H
