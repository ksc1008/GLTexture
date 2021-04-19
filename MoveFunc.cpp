#include "GL/glut.h"
#include "GL/gl.h"
#include "math.h"

int movingHoriz = 0;
int movingVert = 0;
double scailing = 0;
double xRot = 0;
double yRot = 0;
double Scale = 2;

void KeyDown(unsigned char key, int x, int z){
    switch(key){
        case 'a':
            movingHoriz = -1;
            break;
        case 'd' :
            movingHoriz = 1;
            break;
        case 'w' :
            movingVert = 1;
            break;
        case 's' :
            movingVert = -1;
            break;
        case 'z' :
            scailing = 1;
            break;
        case 'x' :
            scailing = -1;
            break;

        case 'r':
            xRot = 0;
            yRot = 0;
            Scale = 2;
            glutPostRedisplay();
            break;
    }
}
void KeyUp(unsigned char key, int x, int z){
    switch(key) {
        case 'a':
            movingHoriz = 0;
            break;
        case 'd' :
            movingHoriz = 0;
            break;
        case 'w' :
            movingVert = 0;
            break;
        case 's' :
            movingVert = 0;
            break;
        case 'z' :
            scailing = 0;
            break;
        case 'x' :
            scailing = 0;
            break;
    }
}

void UpdateMove(){
    xRot += movingHoriz* 0.03;
    yRot += movingVert * 0.03;
    Scale += scailing * 0.03;
    if(yRot>.3*M_PI){
        yRot = .3*M_PI;
    }
    else if(yRot<-.3*M_PI){
        yRot = -.3*M_PI;
    }

    if(Scale<1){
        Scale = 1;
    }
}