#ifndef GLM_MESH_H
#define GLM_MESH_H


#include "../glm/glm.hpp"
#include <string>
#include <vector>
#include "Shader.h"

enum textureType{
    SPECULAR, DIFFUSE
};

struct Vertex{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;

};

struct Texture{
    unsigned int id;
    textureType type;
};

class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    Mesh(std::vector<Vertex> vertices,std::vector<unsigned int> indices,std::vector<Texture> textures);
    void Draw(Shader &shader);

private:
    unsigned int VAO, VBO, EBO;

    void setupMesh();
};


#endif //GLM_MESH_H
