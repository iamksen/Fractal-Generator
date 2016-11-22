#include <GL/glut.h>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

float scale = 2.0f;
float transx = 0.0f;
float transy = 0.0f;
float eyeX = 0.0f, eyeY = 0.0f, eyeZ = 10.0f;
float centerX = 0.0f, centerY = 0.0f, centerZ = 0.0f;
float upX = 0.0f, upY = 1.0f, upZ = 0.0;

float initialx1 = -1.0f, initialy1 = -1.0f, initialx2 = 1.0f;
float initialy2 = -1.0f, initialx3 = 0.0f, initialy3 = 1.0f;
int depth = 7;
int window_width = 800, window_height = 500;

void drawInsideTriangle( vector< pair<float , float > > pts, int depth_left, int color);

//To handle the mouse click events
void mouseclick(int button, int state, int x, int y)
{

	switch(button) {
		case 3:
			scale += 0.09f;
			break;
		case 4:
			scale -= 0.09f;
			break;
    }
}

//To draw traingle with pts as three coordinate points
void drawInitialTriangle( vector< pair<float, float> > pts )
{
	glColor3f(1.0f, 0.0f, 1.0f);
	glBegin(GL_TRIANGLES);
	
	glVertex3f(pts[0].first, pts[0].second, 0.0f);
	glVertex3f(pts[1].first, pts[1].second, 0.0f);
	glVertex3f(pts[2].first, pts[2].second, 0.0f);
	//glVertex3f(pts[0].first, pts[0].second, 0.0f);
	glEnd();
}

//Function to Draw inner triangle
void drawInsideTriangle(vector < pair<float, float> > pts, int depth_left, int color )
{
	if( color == 1 )
		glColor3f(1.0f,0.0f, 0.0f);
	else if( color == 2 )
		glColor3f(0.0f,1.0f, 0.0f);
	else 
		glColor3f(0.0f,0.0f, 1.0f);

	glBegin(GL_TRIANGLES);
	glVertex3f(pts[0].first, pts[0].second, 0.0f);
	glVertex3f(pts[1].first, pts[1].second, 0.0f);
	glVertex3f(pts[2].first, pts[2].second, 0.0f);
	//glVertex3f(pts[0].first, pts[0].second, 0.0f);
	glEnd();

	
	if ( depth_left < depth )
	{
		vector< pair<float ,float> > temp;

		float x1 = (pts[0].first  + pts[1].first)/2  + (pts[1].first  - pts[2].first)/2;
		float y1 = (pts[0].second + pts[1].second)/2 + (pts[1].second - pts[2].second)/2;

		float x2 = (pts[0].first  + pts[1].first)/2  + (pts[0].first  - pts[2].first)/2;
		float y2 = (pts[0].second + pts[1].second)/2 + (pts[0].second - pts[2].second)/2;

		float x3 = (pts[0].first  + pts[1].first)/2;
		float y3 = (pts[0].second + pts[1].second)/2;
		temp.push_back( make_pair(x1, y1));
		temp.push_back( make_pair(x2, y2));
		temp.push_back( make_pair(x3, y3));
		drawInsideTriangle(temp, depth_left + 1, 1);
		//cout<<"Draw first\n";
		temp.clear();

		x1 = (pts[2].first  + pts[1].first)/2  + (pts[1].first  - pts[0].first)/2;
		y1 = (pts[2].second + pts[1].second)/2 + (pts[1].second - pts[0].second)/2;

		x2 = (pts[2].first  + pts[1].first)/2  + (pts[2].first  - pts[0].first)/2;
		y2 = (pts[2].second + pts[1].second)/2 + (pts[2].second - pts[0].second)/2;

		x3 = (pts[2].first  + pts[1].first)/2;
		y3 = (pts[2].second + pts[1].second)/2;
		temp.push_back( make_pair(x1, y1));
		temp.push_back( make_pair(x2, y2));
		temp.push_back( make_pair(x3, y3));
		drawInsideTriangle(temp, depth_left + 1, 2);
		//cout<<"Draw second\n";
		temp.clear();

		x1 = (pts[0].first  + pts[2].first)/2  + (pts[2].first  - pts[1].first)/2;
		y1 = (pts[0].second + pts[2].second)/2 + (pts[2].second - pts[1].second)/2;

		x2 = (pts[0].first  + pts[2].first)/2  + (pts[0].first  - pts[1].first)/2;
		y2 = (pts[0].second + pts[2].second)/2 + (pts[0].second - pts[1].second)/2;

		x3 = (pts[0].first  + pts[2].first)/2;
		y3 = (pts[0].second + pts[2].second)/2;
		temp.push_back( make_pair(x1, y1));
		temp.push_back( make_pair(x2, y2));
		temp.push_back( make_pair(x3, y3));
		drawInsideTriangle(temp, depth_left + 1, 3);
		//cout<<"Draw third\n";
		temp.clear();
	}
}

void changeDimension(int width, int height) {

	float width_by_height_ratio;

	if( height == 0)
		width_by_height_ratio = width*1.0;
	else 
		width_by_height_ratio = width*1.0/height;
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(45.0f, width_by_height_ratio, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
}

float angle = 0.0;
void display(void) {

	depth = 7 + (int)scale / 7;

	//Clearing of the Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

	
	// Setting the camera
	gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ );
		
	glScalef(scale, scale, scale);
	glTranslatef(transx, transy, 0);
	glRotatef(angle, 0, 0, 1);
	vector< pair<float, float> > pt;
	pt.push_back( make_pair(initialx1, initialy1));
	pt.push_back( make_pair(initialx2, initialy2));
	pt.push_back( make_pair(initialx3, initialy3));

	drawInitialTriangle( pt );
	pt.clear();

	pt.push_back( make_pair((initialx1+initialx2)/2, (initialy1 + initialy2)/2) );
	pt.push_back( make_pair((initialx1+initialx3)/2, (initialy1 + initialy3)/2) );
	pt.push_back( make_pair((initialx2+initialx3)/2, (initialy2 + initialy3)/2) );
	drawInsideTriangle(pt, 1, 1);
		
	glutSwapBuffers();
}

void moveup()
{
	transy += 0.09f;
}

void movedown()
{
	transy -= 0.09f;
}

void moveleft()
{
	transx -= 0.09f;
}

void moveright()
{
	transx += 0.09f;
}

void rotateleft()
{
	angle += 1.0;
}

void rotateright()
{
	angle -= 1.0;
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
	else if( key == GLUT_KEY_F1)
		rotateleft();
	else if( key == GLUT_KEY_F2)
		rotateright();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(window_width, window_height);
	glutCreateWindow("Fractal : Sierpinski Triangle");

	glutDisplayFunc( display );
	glutReshapeFunc(changeDimension);

	glutIdleFunc( display );

	glutSpecialFunc(processSpecialKeys);

	//To handle mouse click and scrolling things
	glutMouseFunc(mouseclick);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;

}