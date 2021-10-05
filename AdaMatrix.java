import java.io.*;
import java.util.*;

class AdaMatrix{
	public static void main (String[] args) {
		Scanner sc=new Scanner(System.in);
		int tc=sc.nextInt();
		for(int t=0;t<tc;t++){
		    int n=sc.nextInt();
		    int[][] a=new int[n+1][n+1];
		    for(int i=1;i<=n;i++){
		        for(int j=1;j<=n;j++){
		            a[i][j]=sc.nextInt();
		        }
		    }
		    
		    System.out.println(countTranpose(a,n));
		}
	}
	
	static int countTranpose(int[][] a,int n){
	    int count=0;
	    for(int i=n;i>1;i--){
	        if(a[1][i]!=i)
	        {
	            transpose(a,i);
	            count++;
	        }
	        
	    }
	     
	    return count;
	}
	static void transpose(int A[][],int N) 
    { 
        for (int i = 1; i <= N; i++) 
            for (int j = i+1; j <= N; j++) 
            { 
                 int temp = A[i][j]; 
                 A[i][j] = A[j][i]; 
                 A[j][i] = temp; 
            } 
    } 
}