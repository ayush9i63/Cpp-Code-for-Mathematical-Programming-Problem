//FDM for non-linear BVP (using quasilinearization)
#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;
float F(float X[20],float Y[20][20],float Fun[20][20],int r,int n) 
{
for(int i=1;i<=n-1;i++)
Fun[r][i]=((6*Y[r][i]*Y[r][i])-X[i]);
return 0;
}
float DF_Y(float X[20],float Y[20][20],float DFun[20][20],int r,int n) 
{for(int i=1;i<=n-1;i++)
 DFun[r][i]=12*Y[r][i];
 return 0;
}
float DF_Y1(float X[20],float Y[20][20],float DFun1[20][20],int r,int n)
{for(int i=1;i<=n-1;i++)
 DFun1[r][i]=0;
 return 0;
}
int main()
{float h,a,b,u,v;
 int n;
 float X[20],Y[20][20],A[20],B[20],C[20],D[20],M[20],W[20],T[20],Fun[20][20],DFun[20][20],DFun1[20][20];
cout<<"\nEnter the step size h: ";
cin>>h;
cout<<"\nEnter the left and right boundary point: \n";
cin>>a>>b;
n=((b-a)/h);
X[0]=a;
for(int i=1;i<=n;i++)
{X[i]=X[0]+(i*h);
}
cout<<"\nEnter value of y at "<<a<<" and "<<b<<" respectively: \n";
cin>>u>>v;
float m1=(v-u)/(b-a);
float n1=u-a*m1;
for(int i=0;i<=n;i++)
Y[0][i]=(m1*X[i])+n1;
for(int r=0;r<=4;r++)
{ F(X,Y,Fun,r,n);
  DF_Y(X,Y,DFun,r,n);
  DF_Y1(X,Y,DFun1,r,n);
 for(int i=1;i<=n-1;i++)
 {A[i]=(2+h*DFun1[r][i]);
  B[i]=((-4)-(DFun[r][i]*2*h*h));
  C[i]=(2)-(DFun1[r][i]*h);
  D[i]=((Fun[r][i]*2*h*h)-((h*DFun1[r][i])*(Y[r][i+1]-Y[r][i-1]))-(DFun[r][i]*Y[r][i]*(2*h*h)));
 }
 D[1]-=A[1]*u;
 A[1]=0;
 D[n-1]-=C[n-1]*v;
 C[n-1]=0;
 W[0]=0;
 T[0]=0;
 M[0]=0;
 M[n]=0;
 for(int i=1;i<=n-1;i++) 
  {
  W[i]=(-C[i])/(B[i]+(A[i]*W[i-1]));
 T[i]=(D[i]-(A[i]*T[i-1]))/(B[i]+(A[i]*W[i-1]));}
 for(int i=n-1;i>=1;i--)
 M[i]=W[i]*M[i+1]+T[i];
 for(int i=0;i<=n;i++)
 Y[r+1][i]=M[i];
 for(int i=1;i<=n-1;i++)
 {
   cout<<setprecision(6)<<"y["<<i<<"] = "<<Y[r+1][i]<<"\t\t\n";
 }
}}
