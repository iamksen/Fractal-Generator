#include <bits/stdc++.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

void fitTexture();

typedef struct {
    unsigned char r, g, b;
    } rgbValues;
rgbValues **RGB = 0;
GLuint texture;
int windowNum;

int textureWidth, textureHeight;
int width, height;
int transx=0,transy=0;
double scale = 1.0/256;
double xValue = -.6, yValue = 0;


int maxIterations = 256;

int cRotate = 0;
int sat = 1;

void renderTex()
{
		
	double	xVal = (double)width /textureWidth;
	double	yVal = (double)height/textureHeight;

	glClear(GL_COLOR_BUFFER_BIT);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glBindTexture(GL_TEXTURE_2D, texture);

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex2i(0, 0);
	glTexCoord2f(xVal, 0);
	glVertex2i(width, 0);
	glTexCoord2f(xVal, yVal);
	glVertex2i(width, height);
	glTexCoord2f(0, yVal);
	glVertex2i(0, height);
	glEnd();

	glFlush();
	glFinish();
	
}


void keypress(unsigned char key, int x, int y)
{
	switch(key) {
	case 'q':	
			glFinish();
			glutDestroyWindow(windowNum);
			return;


	case 'r':	cRotate = (cRotate + 1) % 6;
			break;

	}
	fitTexture();
}
void hsvtrgb(int hue, int min, int max, rgbValues *rgbVals)
{
	if (min == max) max = min + 1;

	if (!sat) {
		rgbVals->r = rgbVals->g = rgbVals->b = 255 * (max - hue) / (max - min);
		return;
	}

	double h = fmod(cRotate + 1e-4 + 4.0 * (hue - min) / (max - min), 6);

	double c = 255 * sat;
	double X = c * (1 - fabs(fmod(h, 2) - 1));

	rgbVals->r = rgbVals->g = rgbVals->b = 0;

	switch((int)h) {

	case 0:
	   rgbVals->r = c;
	   rgbVals->g = X;
	   return;
	case 1:
	   rgbVals->r = X;
	   rgbVals->g = c;
	   return;
	case 2:
	   rgbVals->g = c;
        rgbVals->b = X;
        return;
	case 3:
	   rgbVals->g = X;
	   rgbVals->b = c;
	   return;
	case 4:
	   rgbVals->r = X;
	   rgbVals->b = c;
	   return;
	default:
	   rgbVals->r = c;
	   rgbVals->b = X;
	   return;
	}
}


void calculateMandel()
{
	int i=0, j=0, iterations;
	int min, max;
	rgbValues *ansRGB;
	double x=0, y=0, zx=0, zy=0, zx2=0, zy2=0;

	min = maxIterations; max = 0;

	for (i = 0; i < height; i++) {

		ansRGB = RGB[i];
		y = (i - height/2) * scale + yValue;

		for (j = 0; j  < width; j++, ansRGB++) {

			x = (j - width/2) * scale + xValue;
			iterations = 0;

			zx = hypot(x - .25, y);

			if (x < zx - 2 * zx * zx + .25) iterations = maxIterations;
			if ((x + 1)*(x + 1) + y * y < 1/16) iterations = maxIterations;

			zx = zy = zx2 = zy2 = 0;
			while( iterations < maxIterations && zx2 + zy2 < 4) {
				zy = 2 * zx * zy + y;
				zx = zx2 - zy2 + x;
				zx2 = zx * zx;
				zy2 = zy * zy;
				iterations++;
			}
			if (iterations < min) min = iterations;
			if (iterations > max) max = iterations;
			*(unsigned short *)ansRGB = iterations;
		}

	}

	for (i = 0; i < height; i++)
		for (j = 0, ansRGB = RGB[i]; j  < width; j++, ansRGB++)
			hsvtrgb(*(unsigned short*)ansRGB, min, max, ansRGB);
}

void calculateTexture()
{
	int i;
	int neww = textureWidth;
	int newh = textureHeight;
    textureWidth=1;
    textureHeight=1;
	while( textureWidth < width)
        textureWidth=textureWidth<< 1;
	while (textureHeight < height)
	textureHeight =textureHeight<< 1;

	if (textureHeight != newh || textureWidth != neww)
		RGB = (rgbValues**)realloc(RGB, textureHeight * textureWidth * 3 + textureHeight * sizeof(rgbValues*));

	for (RGB[0] = (rgbValues *)(RGB + textureHeight), i = 1; i < textureHeight; i++)
		RGB[i] = RGB[i - 1] + textureWidth;
}

void fitTexture()
{
	calculateTexture();
	calculateMandel();

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(GL_TEXTURE_2D, 0, 3, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, RGB[0]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	renderTex();
}



void mouseclick(int button, int state, int x, int y)
{
	if (state != GLUT_UP) return;

	xValue += (x - width / 2) * scale;
	yValue -= (y - height/ 2) * scale;

	switch(button) {
	case 3:
		if (scale > fabs(x) * 1e-16 && scale > fabs(y) * 1e-16)
			scale /= 2;
		break;
	case 4:
		scale *= 2;
		break;

	}
	fitTexture();
}


void resize(int w, int h)
{

	width = w;
	height = h;

	glViewport(0, 0, w, h);
	glOrtho(0, w, 0, h, -1, 1);

	fitTexture();
}

void arrowKey(int key, int x, int y){


	switch (key) {
		case GLUT_KEY_LEFT:
                xValue -= (x - 0.1) * scale;
			        break;
		case GLUT_KEY_RIGHT:
		   xValue += (x - 0.1) * scale;
			        break;
		case GLUT_KEY_UP:
		   	yValue += (y - 0.1) * scale;
			        break;
		case GLUT_KEY_DOWN:
		   	yValue -= (y -0.1) * scale;
			        break;
	}
	fitTexture();
}

void init(int *c, char **v)
{
	glutInit(c,v);
		
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutDisplayFunc(renderTex);
 
	windowNum= glutCreateWindow("Mandelbrot");
 
	glutKeyboardFunc(keypress);
	glutMouseFunc(mouseclick);
	glutReshapeFunc(resize);
	glutSpecialFunc(arrowKey);
	glGenTextures(1, &texture);
	fitTexture();

}



int main(int c, char **v)
{

	init(&c,v);

	printf("Instructions:\n\tr: color rotation\n\tq: quit\n\tmouse scroll to zoom\n");

	glutMainLoop();
	return 0;
}