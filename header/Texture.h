#ifndef GLM_TEXTURE_H
#define GLM_TEXTURE_H

#include "glad/glad.h"
#include <string>

class Texture {
private:
    std::string FileName;
    unsigned int textureID;
    int width;
    int height;
    int nrChannels;
    GLenum rgbMode;

    bool loaded = false;

public:
    Texture(std::string Name, GLenum RGBMode = GL_RGB){
        FileName = Name;
        rgbMode = RGBMode;
    }

    ~Texture(){
        if(loaded){
            UnLoadTexture();
        }
    }

    void LoadTexture();

    void UnLoadTexture(){
        glDeleteTextures(1,&textureID);
        loaded = false;
    }

    void Bind(){
        glBindTexture(GL_TEXTURE_2D,textureID);
    }
};


#endif //GLM_TEXTURE_H
