#include "header/mainheader.h"
#include "header/stb_image.h"

unsigned int vertexShader;
unsigned int fragmentShader;
unsigned int shaderProgram;
unsigned int texture0;
unsigned int texture1;

unsigned int triangleElementBufferObject;
unsigned int triangleBufferArray;
unsigned int triangleBufferObject;

int width, height, nrChannels;

float uniVertices[32];

float triangleVertices[] = {
        -.5f,-.5f, -0.0f,
        .5f, -.5f, 0.0f,
        0.0f, .5f, 0.0f
};

float rectVertices[] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left
};

float rectColors[] = {
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
};

unsigned int rectIndices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
};

unsigned int uniSize;

float texCoords[] = {
    1.0f, 1.0f,
    1.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 1.0f
};

void CreateUniVertices(int num){
    int verticesSize = (sizeof(rectVertices)/sizeof(rectVertices[0]))/3;
    //uniVertices = new float(verticesSize*num);
    int j;
    for(int i = 0;i<verticesSize;i++){
        for(j = 0;j<3;j++)
            uniVertices[i*num+j] = rectVertices[3*i+j];
        for(j = 0;j<3;j++)
            uniVertices[i*num+j+3] = rectColors[3*i+j];
        for(j = 0;j<2;j++)
            uniVertices[i*num+j+6] = texCoords[2*i+j];
    }
    uniSize = num*sizeof(rectVertices);
}

void InitTexture(){
    stbi__vertically_flip_on_load =true;
    unsigned char* data = stbi_load("Dirt.png",&width,&height,&nrChannels,0);
    if(!data){
        std::cout<<"No data\n";
    }
    glGenTextures(1,&texture0);
    glBindTexture(GL_TEXTURE_2D, texture0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    data = stbi_load("awesomeface.png",&width,&height,&nrChannels,0);
    if(!data){
        std::cout<<"No data\n";
    }
    glGenTextures(1,&texture1);
    glBindTexture(GL_TEXTURE_2D,texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

}

void InitObject(){
    glGenBuffers(1,&triangleBufferArray);
    glGenVertexArrays(1,&triangleBufferObject);
    glGenBuffers(1,&triangleElementBufferObject);

    glBindVertexArray(triangleBufferObject); //VAO 연결

    CreateUniVertices(8);

    glBindBuffer(GL_ARRAY_BUFFER,triangleBufferArray); //VBO 연결
    glBufferData(GL_ARRAY_BUFFER,uniSize,uniVertices,GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,triangleElementBufferObject); //EBO 연결
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(rectIndices),rectIndices,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)0);  //정점 좌표
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(3*sizeof(float)));  //색상
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(6*sizeof(float)));  //텍스처 좌표
    glEnableVertexAttribArray(2);
}

void InitGlfw(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
}