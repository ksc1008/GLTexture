#include "header/Model.h"
#include <map>

Model::Model(std::string path) {
    loadModel(path);
}

unsigned int TextureFromFile(std::string FileName) {
    int width;
    int height;
    int nrChannels;
    GLuint textureID;

    unsigned char* data = stbi_load(FileName.c_str(), &width, &height, &nrChannels, 0);
    if(!data){
        std::cout<<"No data\n";
        return 0;
    }

    GLenum rgbMode;
    switch (nrChannels)
    {
        case 1:
            std::cout<<"rgbMode = LUMINANCE"<<std::endl;
            rgbMode = GL_LUMINANCE;
            break;
        case 2:
            std::cout<<"rgbMode = LUMINANCE_ALPHA"<<std::endl;
            rgbMode = GL_LUMINANCE_ALPHA;
            break;
        case 3:
            std::cout<<"rgbMode = RGB"<<std::endl;
            rgbMode = GL_RGB;
            break;
        case 4:
            std::cout<<"rgbMode = RGBA"<<std::endl;
            rgbMode = GL_RGBA;
            break;
    }


    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D,0,rgbMode,width,height,0,rgbMode,GL_UNSIGNED_BYTE,data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,0);
    stbi_image_free(data);

    return textureID;
}

void Model::loadModel(std::string path) {
    objl::Loader Loader;
    bool loadout = Loader.LoadFile(path);
    if(!loadout){
        std::cout<<"Failed to Load Obj File.\n";
        return;
    }
    for(int i = 0;i<Loader.LoadedMeshes.size();i++){
        meshes.push_back(processMesh(&Loader.LoadedMeshes[i],textures));
    }
}

Texture TextureLoaded(std::string name, textureType type,unsigned int id){
    Texture t;
    t.type = type;
    t.path = name;
    t.id = id;

    return t;
}

Texture TextureFromMaterial(std::string name, textureType type){
    Texture t;
    t.type = type;
    t.path = name;
    t.id = TextureFromFile(name);

    std::cout<<"Loaded Texture : " + name<<std::endl;

    return t;
}

Mesh Model::processMesh(objl::Mesh* mesh, std::map<std::string,unsigned int>& modelTextures) {
    Vertex vertex;
    glm::vec3 vector;
    glm::vec2 vec2;

    std::vector<Vertex> vertices;
    std::vector<unsigned int>indices;
    std::vector<Texture> textures;

    for(int i = 0;i<mesh->Vertices.size();i++){
        vector.x = mesh->Vertices[i].Position.X;
        vector.y = mesh->Vertices[i].Position.Y;
        vector.z = mesh->Vertices[i].Position.Z;
        vertex.Position = vector;
        vector.x = mesh->Vertices[i].Normal.X;
        vector.y = mesh->Vertices[i].Normal.Y;
        vector.z = mesh->Vertices[i].Normal.Z;
        vertex.Normal = vector;
        vec2.x = mesh->Vertices[i].TextureCoordinate.X;
        vec2.y = mesh->Vertices[i].TextureCoordinate.Y;
        vertex.TexCoords = vec2;
        vertices.push_back(vertex);

    }

    for(int i = 0;i<mesh->Indices.size();i++){
        indices.push_back(mesh->Indices[i]);
    }

    if(!mesh->MeshMaterial.map_Kd.empty()){
        if(!modelTextures.count(mesh->MeshMaterial.map_Kd)){
            textures.push_back(TextureFromMaterial("../models/"+mesh->MeshMaterial.map_Kd,DIFFUSE));
            modelTextures[mesh->MeshMaterial.map_Kd] = textures.back().id;
        }
        else{
            textures.push_back(TextureLoaded("../models/"+mesh->MeshMaterial.map_Kd,DIFFUSE,modelTextures[mesh->MeshMaterial.map_Kd]));
        }
    }
    if(!mesh->MeshMaterial.map_Ks.empty()){
        if(!modelTextures.count(mesh->MeshMaterial.map_Ks)){
            textures.push_back(TextureFromMaterial("../models/"+mesh->MeshMaterial.map_Ks,SPECULAR));
            modelTextures[mesh->MeshMaterial.map_Ks] = textures.back().id;
        }
        else{
            textures.push_back(TextureLoaded("../models/"+mesh->MeshMaterial.map_Ks,SPECULAR,modelTextures[mesh->MeshMaterial.map_Ks]));
        }
    }

    return Mesh(vertices, indices, textures);
}

void Model::Draw(Shader &shader) {
    for(int i = 0;i<meshes.size();i++)
        meshes[i].Draw(shader);

}
