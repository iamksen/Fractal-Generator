#include <bits/stdc++.h>
#include <GL/glut.h>

#define window_width 600
#define window_height 600

using namespace std;

int depth = 0;

double transx = 0.0;
double transy = 0.0;
double angle = 0.0;
double scale = 1.0;
double angle_z = 0.0;

//To store the values of the coordinates
pair<double,double> starting_point,ending_point;

//get middle value of two points
double get_middle_point(double xx1,double xx2){
	return (((xx2-xx1)/2.0)+xx1);
}


double get_sum_div(double yy1,double xx1,double xx2){
	return (yy1 + ( abs(xx2-xx1)/2.0) );
}

double get_sub_div(double yy1,double xx1,double xx2){
	return (yy1-(abs(xx2-xx1)/2.0F));
}

void draw_lines(pair<double,double> a,pair<double,double> b){
	glBegin(GL_LINES);
		glColor3f(1,1,1); //Color of dragon
		glVertex3f(a.first,a.second,0);
		glVertex3f(b.first,b.second,0);
	glEnd();
}

void Dragon(pair<double,double> a,pair<double,double> b,int count1,int flag){
	
	if(count1 == 0){
		draw_lines(a,b);
		return;
	}

	pair<double,double> middlepoint;
	
	if(flag == 2) {  
		if(a.second == b.second) {  
			if(a.first <= b.first) 
				middlepoint = make_pair(get_middle_point(a.first,b.first),get_sub_div(a.second,a.first,b.first));
			else
				middlepoint = make_pair(get_middle_point(a.first,b.first),get_sum_div(a.second,a.first,b.first));
		} else if(a.first == b.first) { 
			if(a.second <= b.second)
				middlepoint = make_pair(get_sum_div(a.first,a.second,b.second),get_middle_point(a.second,b.second));
			else
				middlepoint = make_pair(get_sub_div(a.first,a.second,b.second), get_middle_point(a.second,b.second)); 

		} else if(b.first>a.first) {
			if(b.second<a.second) 
				middlepoint = make_pair(a.first,b.second);
			else if(b.second > a.second)
				middlepoint = make_pair(b.first,a.second);
		} else if(b.first<=a.first) {
			if(b.second<a.second) 
				middlepoint = make_pair(b.first,a.second);
			else if(b.second > a.second)
				middlepoint = make_pair(a.first,b.second);
		}
	}

	else if(flag == 1) {  
		if(a.first == b.first && a.second == b.second)
			middlepoint = make_pair(a.first,b.second);
		else if(a.second == b.second) {
			if(a.first<b.first) 
				middlepoint = make_pair(get_middle_point(a.first,b.first),get_sum_div(a.second,a.first,b.first));
			else if(a.first > b.first)
				middlepoint = make_pair(get_middle_point(a.first,b.first),get_sub_div(a.second,a.first,b.first));
			
		}
		
		else if(b.first>a.first) {
			if(b.second>a.second) 
				middlepoint = make_pair(a.first,b.second);
			else if(b.second < a.second)
				middlepoint = make_pair(b.first,a.second);
		}
		else if(a.first == b.first) {
			if(a.second<b.second)
				middlepoint = make_pair(get_sub_div(a.first,a.second,b.second),get_middle_point(a.second,b.second));
			else if(a.second > b.second)
				middlepoint = make_pair(get_sum_div(a.first,a.second,b.second),get_middle_point(a.second,b.second));
		}
		else if(b.first<=a.first) {
			if(b.second>a.second) 
				middlepoint = make_pair(b.first,a.second);
			else if(b.second < a.second)
				middlepoint = make_pair(a.first,b.second);
		}
	}
	
	Dragon(middlepoint,b,count1-1,2);
	Dragon(a,middlepoint,count1-1,1);
	
}


void display(void)  
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glFlush();
	glTranslatef(transx,transy,-500);
	glScalef(scale,scale,scale);
	glRotatef(angle, 0,0,1);
	
	starting_point = make_pair(-100,0);
	ending_point = make_pair(100,0);
	
	Dragon(starting_point,ending_point,depth,1);
	glutSwapBuffers();
}


void changeSize(int w, int h)  
{
	if(h == 0) h = 1;

	double ratio = 1.0* w / h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	 glClearColor(1,0,1,1);
	
	glViewport(0, 0, w, h);

	gluPerspective(45,ratio,1,1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0,0.0,5.0, 
		      0.0,0.0,-1.0,
			  0.0f,1.0f,0.0f);
}

void moveup()
{
	transy += 0.9f;
}

void movedown()
{
	transy -= 0.9f;
}

void moveleft()
{
	transx -= 0.9f;
}

void moveright()
{
	transx += 0.9f;
}

void rotateleft()
{
	angle += 1.0;
}

void rotateright()
{
	angle -= 1.0;
}
void rotate_zz(){
	angle_z += 10;
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
	else if( key == GLUT_KEY_F1){
		rotateright();
	}
	else if( key == GLUT_KEY_F2){
		rotateleft();	
	}
}

void mouseclick(int button, int state, int x, int y){
	switch(button) {
		case 3:
			scale += 0.09f;
			break;
		case 4:
			scale -= 0.09f;
			break;
		case 0:
			if(state == 0){
				depth++;
			}
			break;
		case 2:
			if(depth > 0 && state == 0){
				depth--;
			}	
			break;
    }

}
 
void init(int argc , char ** argv)
{
	glutInit(&argc, argv);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(window_width,window_height);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glClearColor(1,0,0,1);
    glutCreateWindow("Fractal : Linear Fractal");
}

int main(int argc, char **argv){
    init(argc, argv);
    glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(changeSize);
	glutSpecialFunc(processSpecialKeys);
	glutMouseFunc(mouseclick);

	glutMainLoop();
    return 0;
}
