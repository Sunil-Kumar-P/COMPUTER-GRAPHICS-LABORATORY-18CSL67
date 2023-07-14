#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
float ambient[] = {1,1,0,1};
float light_pos[] = {2,2,2,1};
void init()
{
	glOrtho(-2,2,-2,2,-2,2);
}
void align()
{
	glRotatef(50,0,1,0);
	glRotatef(10,-1,0,0);
	glRotatef(11,0,0,-1);
}
void obj(float tx, float ty, float tz, float sx, float sy, float sz)
{
	align();
	glTranslatef(tx,ty,tz);
	glScalef(sx,sy,sz);
	glutSolidCube(1.0);
	glLoadIdentity();

}
void teapot()
{
	glPushMatrix();
	glTranslatef(0,-0.1,0);
	glutSolidTeapot(0.1);
	glPopMatrix();
}
void display()
{
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	obj(0,0,0.5,1,1,0.04);
	obj(-0.5,0,0,0.04,1,1);
	obj(0,-0.5,0,1,0.04,1);
	//legs
	obj(0,-0.3,0,0.02,0.2,0.02);
	obj(0.3,-0.3,0,0.02,0.2,0.02);
	obj(0,-0.3,-0.4,0.02,0.2,0.02);
	obj(0.3,-0.3,-0.4,0.02,0.2,0.02);
	//table top
	obj(0.1,-0.21,-0.1,0.6,0.02,0.7);
	teapot();
	glFlush();
}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("a tea pot on a table");
	glutDisplayFunc(display);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glMaterialfv(GL_FRONT,GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	return 0;
}