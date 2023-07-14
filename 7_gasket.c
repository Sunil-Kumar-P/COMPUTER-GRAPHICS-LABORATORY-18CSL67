#include<stdio.h>
#include<GL/glut.h>

typedef float point[3];
int m;
point v[]={
{0.0,0.0,1.0},
{0.0,1.0,0.0},
{-1.0,-1.0,0.0},
{1.0,-1.0,0.0}
};
void init()
{
	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
}
void triangles(point a, point b, point c)
{
	glBegin(GL_TRIANGLES);
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
	glEnd();
}

void div_triangle(point a, point b, point c, int m)
{
	point v1,v2,v3;
	int j;
	if(m>0)
	{
		for(j=0;j<3;j++)
		v1[j]=(a[j]+b[j])/2;

		for(j=0;j<3;j++)
		v2[j]=(a[j]+c[j])/2;

		for(j=0;j<3;j++)
		v3[j]=(b[j]+c[j])/2;

		div_triangle(a,v1,v2,m-1);
		div_triangle(c,v2,v3,m-1);
		div_triangle(b,v3,v1,m-1);
	}
	else
	{
		triangles(a,b,c);
	}
}
void tetrahedron(int m)
{
	glColor3d(0,0,1);
	div_triangle(v[0],v[3],v[1],m);

	glColor3d(1,0,0);
	div_triangle(v[0],v[1],v[2],m);
	glColor3d(0,1,0);
	div_triangle(v[3],v[2],v[1],m);

	glColor3d(1,1,0);
	div_triangle(v[0],v[2],v[3],m);
}
void display()
{
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	tetrahedron(3);
	glFlush();
}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("3D sierpinski gasket");
	init();
	glutDisplayFunc(display);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	return 0;
}