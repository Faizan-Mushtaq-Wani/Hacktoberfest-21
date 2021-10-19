#include<stdio.h>
#include<stdlib.h>
#define inf 999
void prims(int n,int cost[10][10],int s);
int main()
{
    int n,i,j,source,cost[10][10];
    printf("enter no of nodes: ");
    scanf("%d",&n);
    printf("enter cost matrix\n");
    for(i=1;i<=n;i++)
    for(j=1;j<=n;j++)
    scanf("%d",&cost[i][j]);
    printf("enter source vet: ");
    scanf("%d",&source);
    prims(n,cost,source);
    return 0;
}
void prims(int n,int cost[10][10],int s)
{
    int vis[10],vet[10],dis[10];
    int sum=0,i,j,min,v;
    for(i=1;i<=n;i++)
    {
        vis[i]=0;
        dis[i]=cost[s][i];
        vet[i]=s;
    }
    vis[s]=1;
    printf("edge in mst\n");
    for(i=1;i<n;i++)
    {
        min=inf;
        for(j=1;j<=n;j++)
        {
            if(vis[j]==0 && dis[j]<min)
            {
                min=dis[j];
                v=j;
            }
        }
        vis[v]=1;
        sum=sum+dis[v];
        printf("Edge (%d,%d):cost=%d\n",vet[v],v,dis[v]);
        for(j=1;j<=n;j++)
        {
            if(vis[j]==0&& cost[v][j]<dis [j])
            {
                dis[j]=cost[v][j];
                vet[j]=v;
            }
        }
    }
    printf("\ntotal cost of mst=%d",sum);
}
