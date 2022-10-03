#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#define bucketsize 512
void bktInput(int,int);
int main()
{
  int oprate,pktSize,max=1000,min=1,i;
  printf("Enter Output rate: ");
  scanf("%d",&oprate);
  srand(time(0));
  for(i=1;i<=5;i++)
  {

    pktSize=rand()% (max+1-min)+min;
    printf("Packet no: %d,PacketSize= %d\n",i,pktSize);
    bktInput(pktSize,oprate);
  }
  return 0;
}
void bktInput(int ps,int opr)
{
  if(ps>bucketsize)
  {
    printf("Bucket OverFlow\n");
  }
  else
  {
    while(ps>opr){
      printf("\n\t %d bytes Outputted",opr);
      ps=ps-opr;
    }
    if(ps>0)
    printf("\nLast %d bytes sent\t\n",ps);

    printf("Bucket output successful\n");
  }
}
