#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<string.h>
using namespace std;

long int gcd(long int a,long int b)
{
  if (a==0)
    return b;
  if (b==0)
    return a;

    return (b,a%b);
}

long int isPrime(long int a)
{
  int i;
  for(i=2;i<a;i++)
  {
  if((a%i) == 0)
    return 0;
  }
  return 1;
}

long int encrypt(char ch,long int n,long int e)
{
  int i;
  long int temp =ch;
  for(i=1;i<e;i++)
  temp=(temp *ch)%n;

  return temp;
}

char decrypt(long int ch,long int n,long int d)
{
  int i;
  long int temp=ch;
  for(i=1;i<d;i++)
    ch=(temp*ch)%n;
    return ch;
}

int main()
{
  long int i,len;
  long int p,q,n,phi,e,d,cipher[50];
  char text[50];

  cout<<"Enter text to encrypt\n";
  cin.getline(text,sizeof(text));
  len=strlen(text);
  do{
    p=rand()%30;
  }while(!isPrime(p));
  do{
    q=rand()%30;
  }while(!isPrime(q));

  n=p*q;
  phi=(p-1)*(q-1);
  do{
    e=(rand()%phi);
  }while(gcd(phi,e)!=1);

  do{
    d=rand()%phi;
  }while(((d*e) %phi )!=1);

  cout<<"P:"<<p<<" Q:"<<q<<endl;
  cout<<"n=p*q: "<<p*q<<endl;
  cout<<"(p-1)*(q-1)="<<phi<<endl;
  cout<<"Public Key(n ,e):("<<n<<","<<e<<")\n";
  cout<<"Private Key(n,d):("<<n<<","<<d<<")\n";

  for(i=0;i<len;i++)
   cipher[i]=encrypt(text[i],n,e);

   cout<<"Encrypted Message: ";
   for(i=0;i<len;i++)
    cout<<cipher[i];

    for(i=0;i<len;i++)
    text[i]=decrypt(cipher[i],n,d);
    cout<<endl;
    cout<<"Decrypted Message: ";
    for(i=0;i<len;i++)
      cout<<text[i];
    cout<< endl;
    return 0;

}
