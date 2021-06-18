#ifndef GLM_MODEL_H
#define GLM_MODEL_H
#include "Shader.h"
#include "Mesh.h"
#include <vector>
#include <fstream>
#include <string>
#include "stb_image.h"
#include "OBJ_Loader.h"

class Model {
public:
    Model(std::string path);
    void Draw(Shader &shader);

private:
    std::vector<Mesh> meshes;
    std::string directory;
    std::map<std::string,unsigned int> textures;

    void loadModel(std::string path);

    void loadTextures();

    Mesh processMesh(objl::Mesh* mesh,std::map<std::string,unsigned int>& modelTextures);
};


#endif //GLM_MODEL_H
