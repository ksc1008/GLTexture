#include <cmath>
#include "header/mainheader.h"
#include "header/Shader.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
//#include "GL/glu.h"
int id;
GLFWwindow* window;
unsigned int colorid;
float green;
Shader* myShader = nullptr;

glm::mat4 ScaleAndTranslate(float translateX, float translateY, float translateZ, float scaleX = 1, float scaleY = 1, float scaleZ = 1){
    return glm::mat4(scaleX,0,0,translateX,
                                    0,scaleY,0,translateY,
                                    0,0,scaleZ,translateZ,
                                    0,0,0,1);
}

void MainDisplay(){

    float timeValue = glfwGetTime()*.1;

    glm::mat4 trans = glm::identity<glm::mat4>();
    trans = glm::rotate(trans,timeValue*5,glm::vec3(0,0,1));
    trans = glm::rotate(trans,timeValue*5,glm::vec3(1,1,0));
    trans *= ScaleAndTranslate(-.2+timeValue,0,0,.5,.5,.5);

    glClearColor(.2f,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT);
    myShader->use();
    myShader->setInt("texture1",0);
    myShader->setInt("texture2",1);
    unsigned int transformLoc = glGetUniformLocation(myShader->ID, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));


    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glBindVertexArray(triangleBufferObject);
    glDrawElements(GL_TRIANGLES, 6,GL_UNSIGNED_INT,0);
    glBindVertexArray(0);
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


int main(int argc, char**argv) {
    InitGlfw();
    window = glfwCreateWindow(800,600,"HAHA",NULL,NULL);
    if(window == NULL){
        std::cout <<"OOPS"<<"\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    myShader = new Shader("vertexShader.glsl","fragmentShader.glsl");
    InitTexture();
    InitObject();
    colorid = glGetUniformLocation(shaderProgram,"ourColor");
    glViewport(0, 0, 800, 600);
    while(!glfwWindowShouldClose(window))
    {
        MainDisplay();
    }
    glfwTerminate();
    return 0;
}
