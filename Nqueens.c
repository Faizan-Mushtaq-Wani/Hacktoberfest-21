#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int board[20],count;
void queen(int row,int n);
int main()
{
    int n;
    printf(" - N Queens Problem Using Backtracking -");
    printf("\nEnter number of Queens:");
    scanf("%d",&n);
    if(n==2 ||n==3)
    {
        printf("No Solution\n");
        return 0;
    }
    queen(1,n);
    printf("\n");
    return 0;
}
void print(int n)
{
    int i,j;
    printf("\n\nSolution %d:\n\n",++count);
    for(i=1;i<=n;++i)
    printf(" %d",i);
    for(i=1;i<=n;++i)
    {
        printf("\n%d",i);
        for(j=1;j<=n;++j)
        {
            if(board[i]==j)
            printf(" Q");
            else
            printf(" *");
        }
    }
}
int place(int row,int column)
{
    int i;
    for(i=1;i<=row-1;++i)
    {
        if(board[i]==column)
        return 0;
        else
        if(abs(board[i]-column)==abs(i-row))
        return 0;
    }
    return 1;
}
void queen(int row,int n)
{
    int column;
    for(column=1;column<=n;++column)
    {
        if(place(row,column))
        {
            board[row]=column;
            if(row==n)
            print(n);
            else
            queen(row+1,n);
        }
    }
}
