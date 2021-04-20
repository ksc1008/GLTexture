#ifndef GLTEXTURE_MAINHEADER_H
#define GLTEXTURE_MAINHEADER_H

#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Texture.h"

void InitGlfw();
void InitLight();

extern int movingHoriz;
extern int movingVert;
extern double scailing;
extern double xRot;
extern double yRot;
extern double Scale;
extern void KeyUp(unsigned char key, int x, int z);
extern void KeyDown(unsigned char key, int x, int z);
extern void UpdateMove();
extern int loadFile(std::string s);

extern unsigned int vertexShader;
extern unsigned int fragmentShader;
extern unsigned int shaderProgram;

extern unsigned int triangleBufferArray;
extern unsigned int triangleBufferObject;
extern Texture texture0;
extern Texture texture1;


void InitObject();
void InitTexture();
#endif //GLTEXTURE_MAINHEADER_H
