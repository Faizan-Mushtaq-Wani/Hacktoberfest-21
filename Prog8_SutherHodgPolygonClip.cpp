#include<iostream>
#include<GL/glut.h>
using namespace std;
int psize,ppts[20][2],opsize,oppts[20][2],csize,cppts[20][2];
const int MAX_POINTS =20;
void draw_poly(int p[][2],int n){
  glBegin(GL_POLYGON);
  for(int i=0;i<n;i++)
    glVertex2f(p[i][0],p[i][1]);
  glEnd();
}
int x_intersect(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4){
  int num=(x1*y2 - y1*x2)*(x3-x4) - (x1-x2)*(x3*y4 - y3*x4);
  int den=(x1-x2)*(y3-y4) - (y1-y2)*(x3-x4);
  return num/den;
}
int y_intersect(int x1, int y1, int x2, int y2,int x3, int y3, int x4, int y4){
  int num=(x1*y2 - y1*x2)*(y3-y4) - (y1-y2)*(x3*y4 - y3*x4);
  int den=(x1-x2)*(y3-y4) - (y1-y2)*(x3-x4);
  return num/den;
}
void clip(int ppts[][2],int &psize,int x1,int y1,int x2,int y2){
  int newpts[MAX_POINTS][2],newpsize=0;
  for(int i=0; i < psize; i++)
  {
    int k=(i+1)%psize;
    int ix=ppts[i][0],iy=ppts[i][1];
    int kx=ppts[k][0],ky=ppts[k][1];
    int ipos=(x2-x1)*(iy-y1) - (y2-y1)*(ix-x1);
    int kpos=(x2-x1)*(ky-y1) - (y2-y1)*(kx-x1);
    if(ipos>=0 && kpos >= 0){// Case 1 : When both points are inside
      newpts[newpsize][0]=kx;//Only second point is added
      newpts[newpsize][1]=ky;
      newpsize++;
    }
    else if(ipos<0 && kpos >=0){// Case 2: When only first point is outside
      newpts[newpsize][0]=x_intersect(x1,y1, x2, y2, ix, iy, kx, ky);// Point of intersection with edge
      newpts[newpsize][1]=y_intersect(x1,y1, x2, y2, ix, iy, kx, ky);	// and the second point is added
      newpsize++;
      newpts[newpsize][0]=kx;
      newpts[newpsize][1]=ky;
      newpsize++;
    }
    else if(ipos>=0 && kpos<0){// Case 3: When only second point is outside
      newpts[newpsize][0]=x_intersect(x1,y1, x2, y2, ix, iy, kx, ky);	//Only point of intersection with edge is added
      newpts[newpsize][1]=y_intersect(x1,y1, x2, y2, ix, iy, kx, ky);
      newpsize++;
    }
    else{
      //no points added
    }
  }
  //copying
  psize=newpsize;
  	for (int i = 0; i < psize; i++){
      ppts[i][0]=newpts[i][0];
      ppts[i][1]=newpts[i][1];
      }
}

void myinit(){
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 500.0, 0.0, 500.0, 0.0, 500.0);
	glClear(GL_COLOR_BUFFER_BIT);
}
void display(){
  myinit();
	glColor3f(1.0f, 0.0f, 0.0f);//red
	draw_poly(cppts,csize);
	glColor3f(0.0f, 1.0f, 0.0f);//green
	draw_poly(oppts, opsize);
  for(int i=0;i<csize;i++){
   int  k=(i+1)%csize;
    clip(ppts,psize,cppts[i][0],cppts[i][1],cppts[k][0],cppts[k][1]);
  }
  glColor3f(0.0f,0.0f,1.0f);//green
  draw_poly(ppts,psize);
  glFlush();
}
int main(int argc, char* argv[])
{
	printf("Enter no. of vertices: \n");
	scanf("%d", &psize);
	opsize = psize;
	for (int i = 0; i < psize; i++)
	{
		printf("Polygon Vertex:\n");
		scanf("%d%d", &ppts[i][0], &ppts[i][1]);
		oppts[i][0] = ppts[i][0];
		oppts[i][1] = ppts[i][1];
	}
  printf("Enter no. of vertices of clipping window:");
	scanf("%d", &csize);
	for (int i = 0; i < csize; i++)
	{
		printf("Clip Vertex:\n");
		scanf("%d%d", &cppts[i][0], &cppts[i][1]);
	}
  glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Polygon Clipping!");
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
