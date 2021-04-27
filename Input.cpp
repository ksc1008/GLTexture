#include "header/mainheader.h"

double lastTime = glfwGetTime();

void InputEvent(GLFWwindow* window){
    if(glfwGetKey(window,GLFW_KEY_LEFT)== GLFW_PRESS){
        Rot-=deltaTime*1;
    }
    else if(glfwGetKey(window,GLFW_KEY_RIGHT)==GLFW_PRESS){
        Rot+=deltaTime*1;
    }
}