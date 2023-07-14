#include<stdio.h>
#include<GL/glut.h>
float xmin=50, xmax=100,ymin=50, ymax=100;
float x0 = 70, x1 = 110, y0=40, y1=70;
int left=8, right=4, bottom=2, top=1;
void drawClipWindow()
{
	glBegin(GL_LINE_LOOP);
		glVertex2f(xmin,ymin);
		glVertex2f(xmin,ymax);
		glVertex2f(xmax,ymax);
		glVertex2f(xmax,ymin);
	glEnd();
}
void drawline(float x0, float y0, float x1, float y1)
{
	glBegin(GL_LINE_LOOP);
		glVertex2f(x0,y0);
		glVertex2f(x1,y1);
	glEnd();
}
int computeoutcode(float x, float y)
{
	int code=0;
	if(x<xmin)
		code=code|left;
	else if(x>xmax)
		code=code|right;
	else if(y<ymin)
		code=code|bottom;
	else if(y>ymax)
		code=code|top;
	return code;
}
void lineClipping(float x0, float y0, float x1, float y1)
{
	int outcode, outcode1, outcode0;
	float x,y;
	outcode0 = computeoutcode(x0,y0);
	outcode1 = computeoutcode(x1,y1);

	int accept=0, done=0; 
	do{
		
	if((outcode0|outcode1)==0)
	{
		accept = 1;
		done = 1;
	}
	else if((outcode0&outcode1)!=0)
	{
		done = 1;
	}
	else
	{
		if(outcode0!=0)
			outcode = outcode0;
		else
			outcode = outcode1;
		printf("%d\n",outcode);

		if(outcode&bottom)
		{
			y=ymin;
			x=x0+(ymin-y0)*(x1-x0)/(y1-y0);
		}else if(outcode&top)
		{
			y=ymax;
			x=x0+(ymax-y0)*(x1-x0)/(y1-y0);
		}
		else if(outcode&left)
		{
			x=xmin;
			y=y0+(xmin-x0)*(y1-y0)/(x1-x0);
		}
		else if(outcode&right)
		{
			x=xmax;
			y=y0+(xmax-x0)*(y1-y0)/(x1-x0);
		}
		if(outcode==outcode0)
		{
			x0=x;
			y0=y;	
			outcode0 = computeoutcode(x0,y0);		
		}else{
			x1=x;
			y1=y;	
			outcode1 = computeoutcode(x1,y1);
		}
	}
	}while(!done);
	if(accept==1)
	{
		glPushMatrix();
		glTranslated(150,150,0);
		glColor3f(0,0,1);
		printf("%f %f\n",x0,y0);
		drawClipWindow();
		drawline(x0,y0,x1,y1);
		printf("clipped line is x0 %f y0 %f x1 %f y1 %f \n",x0,y0,x1,y1);
	}
}
void init()
{
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,500,0,500);
	glMatrixMode(GL_MODELVIEW);
}
void display()
{
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glColor3f(1,0,0);
	drawClipWindow();
	drawline(x0,y0,x1,y1);
	lineClipping(x0,y0,x1,y1);
	glFlush();
}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("Clip a lines using Cohen-Sutherland algorithm");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}