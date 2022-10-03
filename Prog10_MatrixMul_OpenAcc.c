#include<stdio.h>
#include<stdlib.h>
#include<openacc.h>
#include<sys/time.h>
#define MAX 1000
int SIZE;
double a[MAX][MAX];
double b[MAX][MAX];
double c[MAX][MAX];
double d[MAX][MAX];

int main(int argc,char **argv){
  SIZE=atoi(argv[1]);
  int i,j,k;
  struct timeval time;
  double t1, t2;
  double tmp;
  for (i = 0; i < SIZE; ++i) {
    for (j = 0; j < SIZE; ++j) {
      a[i][j] = (double)(i + j);
      b[i][j] = (double)(i - j);
      c[i][j] = 0.0f;
      d[i][j] = 0.0f;
    }
  }
  for(i=0;i<SIZE;++i){
    for(j=0;j<SIZE;++j){
      tmp=0.0f;
      for(k=0;k<SIZE;++k){
        tmp+=a[i][k]*b[k][j];
      }
      d[i][j]=tmp;
    }
  }
  gettimeofday(&time,NULL);
  t1=time.tv_sec+(time.tv_usec/1000000.0);
  #pragma acc data copyin(a,b)copy(c)
  #pragma acc kernels
  #pragma acc loop tile(32,32)
  for(i=0;i<SIZE;++i){
    for(j=0;j<SIZE;++j){
      tmp=0.0f;
      #pragma acc loop reduction(+:tmp)
      for(k=0;k<SIZE;++k){
        tmp+=a[i][k]*b[k][j];
      }
      c[i][j]=tmp;
    }
  }
  gettimeofday(&time,NULL);
  t2=time.tv_sec+(time.tv_usec/1000000.0);
  printf("Time %.6lf secs with openAcc\n",t2-t1);
  for (i = 0; i < SIZE; ++i)
    for (j = 0; j < SIZE; ++j)
      if(c[i][j] != d[i][j]) {
	       printf("Error %d %d %f %f \n", i,j, c[i][j], d[i][j]);
	        exit(1);
      }
  printf("OpenACC matrix multiplication test was successful!\n");
  return 0;

}
