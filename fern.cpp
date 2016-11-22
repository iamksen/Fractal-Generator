# include <bits/stdc++.h>
# include <GL/glut.h>

#define NO_OF_POINTS 1000000
using namespace std;

float matrix[2][2]; 		//affine matrix
float pt[2]; 				//For storing coordinates
float probability[4] = { 0.85, 0.92, 0.99, 1.00 };
float a, b, c, d, e, f; 	//used in affine transform
float angle = 0.0, transx = 0.0f, transy = 0.0f;

//Vector to store the point of fern
vector< pair<float, float> > points;

void init_matrix()
{
	matrix[0][0] = a;
	matrix[0][1] = b;
	matrix[1][0] = c;
	matrix[1][1] = d;
}

void affine_transform()
{
	/*
	https://en.wikipedia.org/wiki/Barnsley_fern
	affine transformation
	*/
	float x  = pt[0]*a + pt[1]*b + e;
	float y  = pt[0]*c + pt[1]*d + f;
	pt[0] = x;	//update the current point
	pt[1] = y;	
}

void init_variable(int i)
{
	switch(i){
		case 1: 
				a = 0.0, b = 0.0, e = 0.0;
				c = 0.0, d = 0.16, f=0.0;
				break;
		case 2: 
				a = 0.85,  b = 0.04, e = 0.0;
				c = -0.04, d = 0.85, f = 1.60;
				break;
		case 3: 
				a = 0.20, b = -0.26, e = 0.0;
				c = 0.23, d = 0.22,  f = 1.60;
				break;
		default:
				a = -0.15,  b = 0.28, e = 0.0;
				c = 0.26,   d = 0.24,  f = 0.44;
				break;
	}

	init_matrix();
	affine_transform();
}

void calculate_points ()
{
	pt[0] = drand48( );
	pt[1] = drand48( );

	for (int i = 0; i < NO_OF_POINTS; i++ ){
		double r = drand48 ( );
		if ( r < probability[0] )
			init_variable(2);
		else if ( r < probability[1] )
			init_variable(3);
		else if ( r < probability[2] )
			init_variable(4);
		else 
			init_variable(1);
		points.push_back( make_pair(pt[0], pt[1]));
	}
}

void init( )
{
	//background color : black
	glClearColor ( 1.0, 1.0, 1.0, 1.0 );

	//viewing window, origin at the lower left.
	glMatrixMode ( GL_PROJECTION );
	glLoadIdentity ( );
	gluOrtho2D ( -4.0, 4.0, -1.0, 11.0 );
	glMatrixMode ( GL_MODELVIEW );
	return;
}

void draw_leaf()
{
	glClear ( GL_COLOR_BUFFER_BIT );
	//Plot the new point.
	for(int i = 0 ; i < points.size(); i++){
		if(i&1)
			//Leaf color
			glColor3f ( 0.828, 0.4, 0.09 );
		else
			//Leaf color
			glColor3f ( 0.56, 0.66, 0.023 );
		glBegin ( GL_POINTS );
		glVertex2f( points[i].first, points[i].second );
		glEnd ( );
		
		//Clear all buffers.
		//glFlush();
	}
	glRotatef(angle, 0, 0, 1);
	glTranslatef(transx, transy, 0);
	glFlush();
}

//Function to scale vector of points
void scale(float value)
{
	for(int i = 0 ; i < points.size(); i++){
		points[i].first = points[i].first*value;
		points[i].second = points[i].second*value;
	}
}

void mouseclick(int button, int state, int x, int y)
{
	//Zoom in/out using mouse scroll
	switch(button) {
		case 3: //For zoom in
			scale(1.01);
			break;
		case 4: //For zoom out
			scale(0.99);
			break;
    }
    draw_leaf();
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

void processkeyboardkeys(int key, int x, int y) {
	
	if( key == GLUT_KEY_UP ){
		moveup();
		draw_leaf();
	}
	else if( key == GLUT_KEY_DOWN ){
		movedown();
		draw_leaf();
	}
	else if( key == GLUT_KEY_LEFT )
		moveleft();
	else if( key == GLUT_KEY_RIGHT)
		moveright();
	else if( key == GLUT_KEY_F1)
		rotateleft();
	else if( key == GLUT_KEY_F2)
		rotateright();
	//draw_leaf();
}

int main ( int argc, char *argv[] )
{
	calculate_points();
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB );
	glutInitWindowSize (500,1000);
	glutInitWindowPosition (0, 0);
	glutCreateWindow("Fractal : Barnsley Fern");
	glutDisplayFunc( draw_leaf );
	
	//To handle the keyboard events
	//glutSpecialFunc( processkeyboardkeys );

	//To handle mouse click and scrolling things
	glutMouseFunc(mouseclick);

	init( );
	glutMainLoop( );

	return 0;
}
