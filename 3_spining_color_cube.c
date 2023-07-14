#include<stdio.h>
#include<GL/glut.h>
#include<math.h>

int axis = 0;
float ang[3] = {};
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
	glOrtho(-2,2,-2,2,-2,2);
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
void spin()
{
	ang[axis]+=0.001;
	if(ang[axis]>=360)
		ang[axis]=0.0;
}
void mymouse(int btn, int s, int x, int y) 
{
	if(btn==GLUT_LEFT_BUTTON && s==GLUT_DOWN)axis=0;
	if(btn==GLUT_RIGHT_BUTTON && s==GLUT_DOWN)axis=1;
	if(btn==GLUT_MIDDLE_BUTTON && s==GLUT_DOWN)axis=2;
	if(btn==GLUT_RIGHT_BUTTON && s==GLUT_DOWN && btn==GLUT_LEFT_BUTTON) axis=2;
	printf("%d",axis);
}
void display()
{
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glRotatef(ang[0],1,0,0);
	glRotatef(ang[1],0,1,0);
	glRotatef(ang[2],0,0,1);
	glRotatef(ang[3],1,1,1);
	cube();
	glutSwapBuffers();
	glutPostRedisplay();
	glFlush();
}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("a colour cube and spin it");
	init();
	glutDisplayFunc(display);
	glutMouseFunc(mymouse);
	glutIdleFunc(spin);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	return 0;
}