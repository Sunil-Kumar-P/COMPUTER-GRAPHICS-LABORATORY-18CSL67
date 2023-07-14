#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
float mx;
int flag=0;
int i;
int le[500],re[500];
float x1=200,ya=200,x2=100,y2=300,x3=200,y3=400 ,x4=300,y4=300;
void edgedetect(float x1,float ya,float x2,float y2)
{
	int x;
	if((y2-ya)!=0)
	mx=(x2-x1)/(y2-ya);
	x=x1;
	for(i=ya;i<=y2;i++)
	{
	if(x<le[i])
		le[i]=(int)x;
	if(x>re[i])
		re[i]=(int)x;
	x=x+mx;
	}
}
void scanline()
{
	int y;
	for(i=0;i<500;i++)
	{
		le[i]=500;
		re[i]=0;
	}
	edgedetect(x1,ya,x2,y2);
	edgedetect(x1,ya,x4,y4);
	edgedetect(x2,y2,x3,y3);
	edgedetect(x4,y4,x3,y3);
	for(y=0;y<500;y++)
	{
		for(i=le[y];i<=re[y];i++)
		{
			glColor3f(1,0,0);
			glBegin(GL_POINTS);
			glVertex2i(i,y);
			glEnd();
		}
	}
}

void init()
{
	glClearColor(1,1,1,1);
	gluOrtho2D(0,500,0,500);
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3d(1,0,0);
	glBegin(GL_LINE_LOOP);
		glVertex2f(x1,ya);
		glVertex2f(x2,y2);
		glVertex2f(x3,y3);
		glVertex2f(x4,y4);
	glEnd();
	if(flag==2)
	{
	scanline();
	}
	glFlush();
}
void menu(int id)
{
	if(id==1)
		flag=1;
	if(id==2)
		flag=2;
	if(id==3)
		exit(0);
	display();
}
int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("fill the polygon using scan line algorithm");
	
	init();
	glutDisplayFunc(display);

	glutCreateMenu(menu);
	glutAddMenuEntry("without color",1);
	glutAddMenuEntry("with the color",2);
	glutAddMenuEntry("Exit",3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}	
