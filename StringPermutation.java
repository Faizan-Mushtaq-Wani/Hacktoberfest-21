/*package whatever //do not write package name here */

import java.util.*;
import java.lang.*;
import java.io.*;

class GFG {
    
    
    	
	public static void main (String[] args) {
		//code
		Scanner sc=new Scanner(System.in);
		int tc=sc.nextInt();
		for(int t=0;t<tc;t++){
		    
		    List<String> set=new ArrayList<>();
		    String s=sc.next();
		    permute(s,0,s.length()-1,set);
		    Collections.sort(set);
		    for(String ans:set){
		        System.out.print(ans+" ");
		    }
		    System.out.println();
		}
	}
	
		static void permute(String s,int l,int r,List<String> set){
		    if(l==r){
		        //System.out.print(s+" ");
		        set.add(s);
		    }
		    else{
		        for(int i=l;i<=r;i++){
		            s=swap(s,l,i);
		            permute(s,l+1,r,set);
		            s=swap(s,l,i);
		        }
		    }
		}
		
		public static String swap(String a,int i,int j){
		    char temp;
		    char[] arr=a.toCharArray();
		    temp=arr[i];
		    arr[i]=arr[j];
		    arr[j]=temp;
		    
		    return String.valueOf(arr);
		}
	
}