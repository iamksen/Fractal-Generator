#include <GL/glut.h>
#include <stdio.h>
#include <bits/stdc++.h>
using namespace std;

float angle = 0.0f;
float scale = 1.0f;
float transx = 0.0f;
float transy = 0.0f;

int rotatex = 0, rotatey = 0, rotatez = 0;
int inp;
struct node{
    float x,y,z;
};


typedef node points;
points vec[] = {               // vertices of the initial tetrahedron
    {0.0,0.0,1.0},{0.0,0.942809,-0.333333},
    {-0.816497,-0.471405,-0.333333},
    {0.816497,-0.471405,-0.333333}
};
 
//plots each triangle with the given points
void draw_triangle(points a,points b,points c){
    glBegin(GL_POLYGON);
    glVertex3f(a.x,a.y,a.z);
    glVertex3f(b.x,b.y,b.z);
    glVertex3f(c.x,c.y,c.z);
    glEnd();
}

void inner_triangle(points a,points b,points c,int div){
    points v1,v2,v3;
    if(div>0){
        v1.x=(a.x+b.x)/2;
        v1.y=(a.y+b.y)/2;
        v1.z=(a.z+b.z)/2;
        v2.x=(a.x+c.x)/2;
        v2.y=(a.y+c.y)/2;
        v2.z=(a.z+c.z)/2;
        v3.x=(c.x+b.x)/2;
        v3.y=(c.y+b.y)/2;
        v3.z=(c.z+b.z)/2;
//Now we consider the midpoint as a new vertex and divide the bigger triangle into 3 parts recursively
        inner_triangle(a,v1,v2,div-1);
        inner_triangle(c,v2,v3,div-1);
        inner_triangle(b,v3,v1,div-1);
    }
//draw the inner traingles
    else{
        draw_triangle(a,b,c);
    }
}

void tetrahedral_frac(int nu){
    glColor3f(0.0,0.0,1.0);
    inner_triangle(vec[0],vec[1],vec[2],nu);
    glColor3f(1.0,0.0,0.0);
    inner_triangle(vec[3],vec[2],vec[1],nu);
    glColor3f(0.0,1.0,0.0);
    inner_triangle(vec[0],vec[3],vec[1],nu);
    glColor3f(0.0,0.0,0.0);
       inner_triangle(vec[0],vec[2],vec[3],nu);
        glFlush();
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

void myShape(int width,int height){
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float w=-2.0*(GLfloat)height/(GLfloat)width;
    float h=2.0*(GLfloat)height/(GLfloat)width;
    if(width<=height){
        glOrtho(-2.0,2.0,w,h,-10.0,10.0);
    }
    else{
        glOrtho(w,h,-2.0,2.0,-10.0,10.0);
    }
    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();      
}

void display(void){

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glScalef(scale, scale, scale);
    glTranslatef(transx,transy,0);

    glRotatef(angle,rotatex,rotatey,rotatez);
    tetrahedral_frac(inp);
    glutSwapBuffers();
}

int main(int argc,char **argv){
    inp = 5;
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(500,500);
    //window with a title
    glutCreateWindow("Sierpinsky 3D Fractal");
  
    glutReshapeFunc(myShape);
    glutDisplayFunc(display);
    glEnable(GL_DEPTH_TEST);
    glutIdleFunc(display);
    //handling mouse clicks
    glutMouseFunc(mouseclick);
    //handling keyboard buttons
    glutSpecialFunc(processSpecialKeys);

  
    glClearColor(1.0,1.0,1.0,1.0);
    glutMainLoop();
}
