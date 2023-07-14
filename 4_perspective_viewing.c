#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
int view[] = {0,0,5};
float v[8][3] = {
	{-1,-1,-1},//0
	{1,-1,-1},//1
	{1,1,-1},//2
	{-1,1,-1},//3
	{-1,1,1},//4
	{1,1,1},//5
	{-1,-1,1},//6
	{1,-1,1},//7
};
void init()
{
	glMatrixMode(GL_PROJECTION);
	glFrustum(-2,2,-2,2,2,20);
	glMatrixMode(GL_MODELVIEW);
}
void drawsquare(int a, int b, int c, int d)
{
	
	glBegin(GL_POLYGON);
		glVertex3fv(v[a]);
		glVertex3fv(v[b]);
		glVertex3fv(v[c]);
		glVertex3fv(v[d]);
	glEnd();
}
void cube()
{
	glColor3f(0,0,1);
	drawsquare(0,1,2,3);

	glColor3f(0,1,0);
	drawsquare(4,6,7,5);

	glColor3f(0,1,1);
	drawsquare(0,6,7,1);

	glColor3f(1,0,0);
	drawsquare(3,4,6,0);

	glColor3f(1,0,1);
	drawsquare(3,4,5,2);

	glColor3f(1,1,0);
	drawsquare(2,5,7,1);
}
void keyboardfun(unsigned char key, int x, int y) 
{
	if(key=='x') view[0]-=1;
	if(key=='X') view[0]+=1;

	if(key=='y') view[1]-=1;
	if(key=='Y') view[1]+=1;

	if(key=='z') view[2]-=1;
	if(key=='Z') view[2]+=1;
	glutPostRedisplay();
}
void display()
{
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	gluLookAt(view[0],view[1],view[2],0,0,0,0,1,0);
	cube();
	glutSwapBuffers();
	glFlush();
}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("perspective viewing");
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboardfun);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	return 0;
}