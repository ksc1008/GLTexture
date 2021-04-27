#ifndef GLTEXTURE_SHADER_H
#define GLTEXTURE_SHADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "../glm/glm.hpp"

class Shader {
public:
    unsigned int ID;
    Shader(const char* vertexPath, const char* fragmentPath);
    void use();
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;

    void set4f(const std::string &name, float x, float y,float z, float w)const;
    void setVec3(const std::string &name, float x, float y, float z)const;
    void setVec3(const std::string &name, glm::vec3 &vector)const;
};


#endif //GLTEXTURE_SHADER_H
