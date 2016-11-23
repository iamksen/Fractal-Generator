#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <bits/stdc++.h>
using namespace std;
 
/* initial parameters */
double x_i = -1.5;
double y_i = -1.5;
double z_i = -1.5;
double length_i = 3.0;
int level_i = 3; // orde fractal
 
float x_rot = 0.0f;
float y_rot = 0.0f;
 
float x_diff = 0.0f;
float y_diff = 0.0f;
 
float angle = 0.0f;
float scale = 1.0f;
float transx = 0.0f;
float transy = 0.0f;
int rotatex = 0, rotatey = 0, rotatez = 0;

//Drawing each face individually
void face1(double x, double y , double z, double length)
{
    glColor3f(0.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f(x, y, z);
    glVertex3f(x+length, y, z);
    glVertex3f(x+length, y+length, z);
    glVertex3f(x, y+length, z);
    glVertex3f(x, y, z);
    glEnd();
}

void face2(double x, double y , double z, double length)
{
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(x+length, y, z);
    glVertex3f(x+length, y, z+length);
    glVertex3f(x+length, y+length, z+length);
    glVertex3f(x+length, y+length, z);
    glVertex3f(x+length, y, z);
    glEnd();
}

void face3(double x, double y , double z, double length)
{
    glColor3f(0.5, 0.5, 0.8);
    glBegin(GL_POLYGON);
    glVertex3f(x+length, y, z+length);
    glVertex3f(x, y, z+length);
    glVertex3f(x, y+length, z+length);
    glVertex3f(x+length, y+length, z+length);
    glVertex3f(x+length, y, z+length);
    glEnd();
}

void face4(double x, double y , double z, double length)
{
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(x, y, z+length);
    glVertex3f(x, y, z);
    glVertex3f(x, y+length, z);
    glVertex3f(x, y+length, z+length);
    glVertex3f(x, y, z+length);
    glEnd();
}

void face5(double x, double y , double z, double length)
{
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f(x, y+length, z);
    glVertex3f(x+length, y+length, z);
    glVertex3f(x+length, y+length, z+length);
    glVertex3f(x, y+length, z+length);
    glVertex3f(x, y+length, z);
     glEnd();
}

void face6(double x, double y , double z, double length)
{
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(x, y, z+length);
    glVertex3f(x+length, y, z+length);
    glVertex3f(x+length, y, z);
    glVertex3f(x, y, z);
    glVertex3f(x, y, z+length);
    glEnd();
}

void DrawCube(double x, double y, double z, double length){
    face1(x, y, z, length);
    face2(x, y, z, length);
    face3(x, y, z, length);
    face4(x, y, z, length);
    face5(x, y, z, length);
    face6(x, y, z, length);
}
 
void DrawRecur(double x, double y, double z, double length, int orde){
    if (orde == 0){
        DrawCube(x, y, z, length);
        return;
    }

    length = length/3.;
    for (int i=0;i<3;i++){
        for (int j=0;j<3;j++){
            for (int k=0;k<3;k++){
                if (i==1 && j==1 || i==1 && k==1 || j==1 && k==1 || i==1 && j==1 && k==1){
                    continue; 
                } else {
                    DrawRecur(x+i*length, y+j*length, z+k*length, length, orde-1); 
                }
            }
        }
    }
}

void rotatein(int direction){
    angle += 1.0;
    //rotatex = rotatey = rotatez = 0;
    if( direction == 0 ){ rotatex = 1; rotatey = 0; rotatez = 0;}
    else if( direction == 1 ){ rotatex = 0; rotatey = 1; rotatez = 0;}
    else if( direction == 2 ){ rotatex = 0; rotatey = 0; rotatez = 1;}
}

void rotateout(int direction){
    angle -= 1.0;
    //rotatex = rotatey = rotatez = 0;
    if( direction == 0 ){ rotatex = 1; rotatey = 0; rotatez = 0;}
    else if( direction == 1 ){ rotatex = 0; rotatey = 1; rotatez = 0;}
    else if( direction == 2 ){ rotatex = 0; rotatey = 0; rotatez = 1;}
}

void mouseclick(int buttonpressed, int state, int x, int y){
    switch(buttonpressed) {
        case 3:
            //cout<<"wheel - up"<<endl;
            scale += 0.09;
            break;
        case 4:
            //cout<<"wheel - down"<<endl;
            scale -= 0.09;
            break;
    }
}

void moveup(){
    transy += 0.09f;
}

void movedown(){
    transy -= 0.09f;
}

void moveleft(){
    transx -= 0.09f;
}

void moveright(){
    transx += 0.09f;
}


void processSpecialKeys(int key, int x, int y) {
    int mod;
    mod = glutGetModifiers();

    if( key == GLUT_KEY_UP )
        moveup();
    else if( key == GLUT_KEY_DOWN )
        movedown();
    else if( key == GLUT_KEY_LEFT )
        moveleft();
    else if( key == GLUT_KEY_RIGHT)
        moveright();
    else if( key == GLUT_KEY_F1) //X direction
        rotatein(0);
    else if( key == GLUT_KEY_F2)
        rotateout(0);

    else if( key == GLUT_KEY_F3) //y direction
        rotatein(1);
    else if( key == GLUT_KEY_F4)
        rotateout(1);

    else if( key == GLUT_KEY_F5) //z direction
        rotatein(2);
    else if( key == GLUT_KEY_F6)
        rotateout(2);
}
 
void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);  
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glLoadIdentity();
  
    gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    glScalef(scale, scale, scale);
    glTranslatef(transx,transy,0);
    glRotatef(angle,rotatex,rotatey,rotatez);   
    
    DrawRecur(x_i, y_i, z_i, length_i, level_i); 
    glutSwapBuffers();
}
 
void resize(int w, int h){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45.0f, 1.0f * w / h, 1.0f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
  
int main(int argc, char *argv[]){
    glutInit(&argc, argv);
 
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(500, 500);    
    glutCreateWindow("Fractal Cube");
     
    glutReshapeFunc(resize);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glutDisplayFunc(display);
    glutIdleFunc(display);
 
    //handling mouse clicks
    glutMouseFunc(mouseclick);
    //handling keyboard buttons
    glutSpecialFunc(processSpecialKeys);
    glClearColor(1.0,1.0,1.0,1.0);
    glutMainLoop();
    return 0;
}
