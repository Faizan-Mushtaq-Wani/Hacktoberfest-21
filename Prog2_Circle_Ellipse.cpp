#include<GL/glut.h>
#include<stdio.h>
#include<iostream>
#include<math.h>
using namespace std;
int xc,yc,r;
int rx,ry,xce,yce;
void draw_circle(int xc,int yc,int x,int y)
{
  glBegin(GL_POINTS);
  glVertex2i(xc+x,yc+y);
  glVertex2i(xc+x,yc-y);
  glVertex2i(xc-x,yc-y);
  glVertex2i(xc-x,yc+y);
  glVertex2i(xc+y,yc+x);
  glVertex2i(xc-y,yc+x);
  glVertex2i(xc+y,yc-x);
  glVertex2i(xc-y,yc-x);
  glEnd();
}
void circleBres()
{
  glClear(GL_COLOR_BUFFER_BIT);
  int x=0,y=r;
  int d=3-2*r;
  while(x<=y){
    x++;
    if(d<0){
      d=d+ 4*x +6;
    }else{
      y--;
      d=d+4*(x-y)+10;
    }
    draw_circle(xc,yc,x,y);
  }
  glFlush();
}
int p1x,p1y,p2x,p2y;
int pt1done=0;

void mymouseCircle(int btn,int st,int x,int y){
  if(btn==GLUT_LEFT_BUTTON && st==GLUT_DOWN && pt1done==0){
    p1x=x-250;
    p1y=250-y;
    pt1done=1;
  }
  else if(btn==GLUT_LEFT_BUTTON && st==GLUT_DOWN){
    p2x=x-250;
    p2y=250-y;
    xc=p1x;
    yc=p1y;
    float exp=pow((p2x-p1x),2)+pow((p2y-p1y),2);
    r=(int)sqrt(exp);
    circleBres();
    pt1done=0;
  }
}

void draw_ellipse(int xce,int yce,int x,int y){
  glBegin(GL_POINTS);
  glVertex2i(xce+x,yce+y);
  glVertex2i(xce-x,yce+y);
  glVertex2i(xce+x,yce-y);
  glVertex2i(xce-x,yce-y);
  glEnd();
}
void midptellipse(){
  glClear(GL_COLOR_BUFFER_BIT);
  float dx,dy,d1,d2,x,y;
  x=0;
  y=ry;
  d1=(ry*ry)-(rx*rx*ry)+(0.25*rx*rx);
  dx=2*ry*ry*x;
  dy=2*rx*rx*y;
  while(dx<dy)
  {
    draw_ellipse(xce,yce,x,y);

    if(d1<0){
      x++;//y=y;
      dx=dx+(2*ry*ry);
      d1=d1+dx+(ry*ry);
    }else{
      x++;y--;
      dx=dx+(2*ry*ry);
      dy=dy-(2*rx*rx);
      d1=d1+dx-dy+(ry*ry);
    }
  }
  d2=((ry*ry)*((x+0.5)*(x+0.5))) + ((rx*rx)*((y-1)*(y-1))) -(rx*rx*ry*ry);
  while(y>=0)
  {
    draw_ellipse(xce,yce,x,y);
    if(d2>0){
      y--;//x=x;
      dy=dy-(2*rx*rx);
      d2=d2+(rx*rx) -dy;
    }else{
      x++;y--;
      dx=dx+(2*ry*ry);
      dy=dy-(2*rx*rx);
      d2=d2+dx-dy+ (rx*rx);
    }
  }
  glFlush();
}

int pe1x,pe1y,pe2x,pe2y,pe3x,pe3y;
int ptedone=0;
void mymouseellipse(int btn,int st,int x,int y){
  if(btn==GLUT_LEFT_BUTTON && st==GLUT_DOWN && ptedone==0){
    pe1x=x-250;
    pe1y=250-y;
    xce=pe1x;
    yce=pe1y;
    ptedone=1;
  }
  else if(btn==GLUT_LEFT_BUTTON && st==GLUT_DOWN && ptedone==1){
    pe2x=x-250;
    pe2y=250-y;

    float exp= pow((pe2x-pe1x),2)+ pow((pe2y-pe1y),2);
    rx=(int)sqrt(exp);
    ptedone=2;
  }
  else if(btn==GLUT_LEFT_BUTTON && st==GLUT_DOWN && ptedone==2){
    pe3x=x-250;
    pe3y=250-y;

    float exp= pow((pe3x-pe1x),2)+ pow((pe3y-pe1y),2);
    ry=(int)sqrt(exp);
    midptellipse(); //to draw using mouse
    ptedone=0;
  }
}
void mydrawingc() {}
void mydrawinge() {}
void myinit(){
  glClearColor(1,1,1,1);
  glColor3f(1.0,0.0,0.0);
  glPointSize(3.0);
  gluOrtho2D(-250,250,-250,250);
}
int main(int argc,char ** argv){
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
  glutInitWindowSize(500,500);
  glutInitWindowPosition(0,0);
  int id1=glutCreateWindow("circle");
  glutSetWindow(id1);
  glutMouseFunc(mymouseCircle);
  glutDisplayFunc(mydrawingc);
  myinit();
  glutInitWindowSize(500,500);
  glutInitWindowPosition(600,100);
  int id2=glutCreateWindow("ellipse");
  glutSetWindow(id2);
  glutMouseFunc(mymouseellipse);
  glutDisplayFunc(mydrawinge);
  //for KEYBOARD
  // printf("1.circle 2.Ellipse");
  // int ch;
  // cin>> ch;
  // switch(ch){
  //   case 1: cout<<"enter xc yc r";
  //   cin>>xc>>yc>>r;
  //   glutCreateWindow("Circle");
  //   glutDisplayFunc(circleBres);
  //   break;
  //   case 2: cout<< "enter xce yce rx ry ";
  //   cin>>xce>>yce>>rx>>ry;
  //   glutCreateWindow("Ellipse");
  //   glutDisplayFunc(midptellipse);
  //   break;
  // }
  myinit();
  glutMainLoop();

}
