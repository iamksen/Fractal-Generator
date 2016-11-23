#include <bits/stdc++.h>
#include <GL/glut.h>
#include "variables.h"


using namespace std;
// Produces animation
void anim_timer(int ak)
{
	if (cRedecreasing == 0)
		RealofC += change_in_c;
	else
		RealofC -= change_in_c;

	if (RealofC > 1)
		cRedecreasing = 1;
	if (RealofC < -2)
		cRedecreasing = 0;

	glutPostRedisplay();
	if (control_animation == 0)
	glutTimerFunc(60, anim_timer, 0);
}

// Produces moving and scaling
void move_timer(int kl)
{
	glutPostRedisplay();

	if (control_motion == 1)
		glutTimerFunc(60, move_timer, 1);
}

void moveup()
{
	change_in_y = -moveFast;
}

void movedown()
{
	change_in_y = moveFast;
}

void moveleft()
{
	change_in_x =  moveFast;
}

void moveright()
{
	change_in_x = -moveFast;
}

// Handles keyboard calls
void pressSpecialKey(int key, int x, int y)
{
	//Play pause
	if (key == GLUT_KEY_F3) {
		if( control_animation == 0)
			control_animation = 1;
		else
			control_animation = 0;

		if (control_animation == 0)
			glutTimerFunc(60,anim_timer, 0);
		return;
	}

	if( key == GLUT_KEY_F4 ){ //To rotate left
		angle =+ 0.5;
	}
	else if( key == GLUT_KEY_F5 ){ //To rotate right
		angle -= 0.5;
	}
	else if( key == GLUT_KEY_F6 ){ //To stop rotation
		angle = 0.0;
	}

	else if( key == GLUT_KEY_F1 ){ //To translate fast
		moveFast++;
		if( moveFast >= 5 ) moveFast = 5;
	}
	else if( key == GLUT_KEY_F2 ){ //To translate fast
		moveFast--;
		if( moveFast <= 0 ) moveFast = 0;
	}
	else if( key == GLUT_KEY_LEFT)
		moveleft();
	else if( key == GLUT_KEY_RIGHT )
		moveright();
	else if( key == GLUT_KEY_UP )
		moveup();
	else if( key == GLUT_KEY_DOWN )
		movedown();

	control_motion = 1;
	glutTimerFunc(60, move_timer, 1);
}

void mouseclick(int button, int state, int x, int y)
{
	if( button == 3)
		change_in_scale = 1;
	else if ( button == 4 )
		change_in_scale = -1;
		
	/* any other button recenters */
	if( button == GLUT_LEFT_BUTTON  ){
		change_in_x = 0.0f;
		change_in_scale = 0.0f;
		change_in_y = 0.0;
	} 
	control_motion = 0;
}

// Also handles keyboard calls
void releaseKey(int key, int x, int y)
{
	//For controlling the fractal
	//lets try with mouse
	if( key == GLUT_KEY_F1 || key == GLUT_KEY_F2 || key == GLUT_KEY_LEFT || key == GLUT_KEY_RIGHT || key == GLUT_KEY_RIGHT || key == GLUT_KEY_UP || key == GLUT_KEY_DOWN ){
		change_in_x = 0.0f;
		change_in_scale = 0.0f;
		change_in_y = 0.0;
	}
	control_motion = 0;
	glutTimerFunc(60, move_timer, 1);
}

float getRealPixelValue(int x, int ishalf = 0)
{	if(ishalf)
		return (x - WINDOW_WIDTH / 2) / (0.5 * WINDOW_WIDTH);
	else
		return (x - WINDOW_WIDTH/2) / ( WINDOW_WIDTH * scale );
}	

float getImaginaryPixelValue(int y, int ishalf = 0)
{
	if(ishalf)
		return (y - WINDOW_HEIGHT / 2) / (0.5 * WINDOW_HEIGHT);
	else
		return (y - WINDOW_HEIGHT/2) / ( WINDOW_HEIGHT * scale );
}

// Drawing function
void display_julia() {
	float Realofpixel, Imaginaryofpixel, RealofZ, ImaginaryofZ;
	
	vector< pair<float, float> > points;

	if (change_in_x)
		move_x = (change_in_x > 0)?( move_x + 0.01) : ( move_x - 0.01);
	if (change_in_y)
		move_y = (change_in_y > 0)?( move_y + 0.01) : ( move_y - 0.01);

	if (change_in_scale)
		scale = (change_in_scale > 0)? ( scale + 0.01) : ( scale - 0.01);

	glClear(GL_COLOR_BUFFER_BIT);
	
	glRotatef(angle, 0, 0, 1);
	glBegin(GL_POINTS);

	int x = 0, y = 0;
	for (int x = 0; x < WINDOW_WIDTH; x++) {
		for (int y = 0; y < WINDOW_HEIGHT; y++) {
			Realofpixel      = getRealPixelValue(x)      + move_x;
			Imaginaryofpixel = getImaginaryPixelValue(y) + move_y;

			glColor3f(0, 0, 0);

			//Source: https://en.wikipedia.org/wiki/Julia_set
			for (int iter = 0; iter < maxNoIter; iter++) {
				//f(z) = z^2 + C
				//Realofz = a^2 - b^2 + RealofC  ;for z = a+ib
				//Imaginaryofz = 2ab + ImaginaryofC
				RealofZ = Realofpixel * Realofpixel - Imaginaryofpixel * Imaginaryofpixel + RealofC;
				ImaginaryofZ = 2 * Realofpixel * Imaginaryofpixel + ImaginaryofC;

				if ( (RealofZ * RealofZ + ImaginaryofZ * ImaginaryofZ) > 4 ){ //if value is out of circle of radius of 2
					float red = 10*iter/ 255.0f;
					glColor3f(red, 0.2, 0.7);
					break;
				}

				//using complex library of c++
				//complex<float> iss(RealofZ, ImaginaryofZ);
				//cout<<exp(iss);
				Realofpixel = RealofZ;
				Imaginaryofpixel = ImaginaryofZ;
			}

			Realofpixel      = getRealPixelValue(x, 1);
			Imaginaryofpixel = getImaginaryPixelValue( y, 1);
			
			glVertex2f(Realofpixel, Imaginaryofpixel);
			//points.push_back( make_pair( Realofpixel, Imaginaryofpixel ));
		}
	}
	//glTranslatef(transx, transy, 0);

	/*glBegin(GL_POINTS);
	for(int i = 0 ; i < points.size(); i++)
		glVertex2f(points[i].first, points[i].second);
	glEnd();*/

	glEnd();
	
	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	int cc;
	cout<<"Julia Fractal\n";
	cout<<"Instruction\n";
	cout<<"Use arrow key to move the fractal left, right, up and down\n";
	cout<<"Use mouse scroll the zoom in and zoom out and press the mouse button to stop zooming\n";
	cout<<"Press any keys to continue\n";
	getchar();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	
	glutCreateWindow("Fractal : Julia Fractal");

	//glutDisplayFunc sets the display callback for the current window
	glutDisplayFunc(display_julia);

	//glutTimerFunc registers a timer callback to be triggered in a specified number of milliseconds
	glutTimerFunc(45, anim_timer, 0);

	//glutSpecialFunc sets the special keyboard callback for the current window
	glutSpecialFunc(pressSpecialKey);

	//For mouse control
	glutMouseFunc(mouseclick);

	//Mouse wheel even
	//glutMouseWheelFunc(mouseWheel);

	//glutIgnoreKeyRepeat — determines if auto repeat keystrokes are reported to the current window
	glutIgnoreKeyRepeat(1);
	

	glutSpecialUpFunc(releaseKey);
	glutMainLoop();
	return 0;
}
