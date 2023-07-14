#include<GL/glut.h>
#include<stdio.h>

float x0,y0,x1,y1,df,dx,dy;
void init()
{

	gluOrtho2D(0,500,0,500);
}
void display()
{
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	int i;
	dy=abs (y1-y0);
	dx=abs (x1-x0);
	df=(2*dy)-dx;
	float x=x0;
	float y=y0;
	float incrx,incry;
	incrx =1;
	if(x1<x0)
	{
		incrx =-1;
	}
	incry =1;
	if(y1<y0)
	{
		incry =-1;
	}
	if(dx>dy)
	{
		glColor3f(1,0,0);
		glBegin(GL_POINTS);
		for(i=0;i<dx;i++)
		{
			if(df>0)
			{
				x=x+incrx;
				y=y+incry;
				df=df+(2*dy)-(2*dx);
			}
			else
			{
				x=x+incrx;
				df=df+(2*dy);
			}
			printf("%f %f\n",x,y);
			glVertex2f(x,y);
		}
		glEnd();
	}
	else
	{
		glColor3f(1,0,0);
		glBegin(GL_POINTS);
			for(i=0;i<dy;i++)
			{
				if(df>0)
				{
					y=y+incry;
					x=x+incrx;
					df=df+(2*dx)-(2*dy);
				}
				else
				{
					y=y+incry;
					df=df+(2*dx);
				}
				printf("%f %f\n",x,y);
				glVertex2f(x,y);
			}

			glEnd();
	}
	glFlush();
}
int main(int argc,char **argv)
{	
	printf("Enter (x0,y0,x1,y1)\n");
	scanf("%f %f %f %f",&x0,&y0,&x1,&y1);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("bresenham's line drawing algorithm");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}