#ifdef __APPLE__
# include <OpenGL/gl.h>
# include <OpenGL/glu.h>
# include <GLUT/glut.h>
#else
# include <GL/gl.h>
# include <GL/glu.h>
# include <GL/glut.h>
#endif
#include <windows.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <vector>
using namespace std;

#define maxWD 800
#define maxHT 600

vector<int> coor1, coor2;

GLsizei winWidth =800, winHeight =600;
int x1=-1,y1=-1,x2=-1,y2=-1;
bool bandx=false, bandy=false;

void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}
void displayFcn(void)
{
	glClear(GL_COLOR_BUFFER_BIT); 
	glColor3f(1.0,0.0,0.0); 
	glPointSize(2.0); 
}

void winReshapeFcn(GLint newWidth, GLint newHeight)
{
	glViewport(0, 0, newWidth, newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D (0.0 , GLdouble(newWidth),0.0 , GLdouble( newHeight));
	winWidth = newWidth;
	winHeight = newHeight;
}

void plotPoint(GLint x, GLint y)
{
	glBegin(GL_POINTS);
	glColor3f(1,0,0);
	glVertex2i(x,y);
	glEnd();
}

int round(int a) 
{ return float (a + 0.5); }
void linea(int x0, int y0, int xEnd, int yEnd)
{
	int dx = xEnd - x0, dy = yEnd - y0, steps, k;
	float xIncrement, yIncrement, x = x0, y = y0;
	if (fabs (dx) > fabs (dy))
		steps = fabs (dx);
	else
		steps = fabs (dy);
	xIncrement = float (dx) / float (steps);
	yIncrement = float (dy) / float (steps);
	plotPoint(round (x), round (y));
	for (k = 0; k < steps; k++)
	{
		x += xIncrement;
		y += yIncrement;
		plotPoint(round (x), round (y));
	}
}
void poligono()
{
	int tam=coor1.size();
	for(int i=1; i<tam; i++)
	{
		linea(coor1[i-1],coor2[i-1],coor1[i],coor2[i]);
	}
	linea(coor1[tam-1],coor2[tam-1],coor1[0],coor2[0]);
}

void mousePtPlot(GLint button , GLint action , GLint xMouse, GLint yMouse)
{
	if(button==GLUT_LEFT_BUTTON && action==GLUT_DOWN)
	{
		
		printf("obtiene coordenada: ");
		x1=xMouse;
		y1=winHeight-yMouse;
		plotPoint(x1,y1);
		printf("%d %d\n",x1,y1);
		coor1.push_back(x1);
		coor2.push_back(y1);
		
		
	}
	if(button==GLUT_RIGHT_BUTTON && action==GLUT_DOWN)
	{
		printf("ultima coordenada: ");
		x1=xMouse;
		y1=winHeight-yMouse;
		plotPoint(x1,y1);
		coor1.push_back(x1);
		coor2.push_back(y1);
		printf("%d %d\n",x1,y1);
		poligono();
		
		
	}
	glFlush();
	
}
int main(int argc, char**argv)
{
	
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(200,100);
	
	glutInitWindowSize(winWidth, winHeight );
	glutCreateWindow("Poligono con puntos por mouse" );
	init();
	glutDisplayFunc(displayFcn);
	glutReshapeFunc(winReshapeFcn);
	glutMouseFunc(mousePtPlot);
	glutMainLoop();
}

