# include<stdio.h>
# include<stdlib.h>
# include<math.h>
int main(void)
{
int i,j;
float t,dt;
t = 0.0; dt = 0.1;
double A,B,C,S,ks0,ks1,n,beta,alpha,Se,neta,kappa,dA,dB,dC,dS;
double slopeA,Amax,slopeB,Bmax;
int I1,I2,I,J,K,L;
ks0 = 1;
ks1 = 0.025;
n = 3;
beta = 0.1;
neta = 1.0;
FILE *fp;
fp = fopen("reprissilator-time-protein.txt","wt");
alpha = 46;
//srand(time(0));
for(j=1;j<20;j++)
{
I1 = rand()%2;
I2 = rand()%2;
if((I1+I2)==0)                                                                              //theoretical logic gate
{
 I = 9;
 J = 65;
 K = 10;
 L = 75;
} 
else if((I1+I2)==1)
{
 I = 9;
 J = 55;
 K = 11;
 L = 85;
} 
else if((I1+I2)==2)
{
 I = 8;
 J = 65;
 K = 12;
 L = 95;
}
kappa = 14; 
Se = (I1+I2)*0.2;                                                                           // logic input
  A = 0.0;
  B = 0.0;
  C = 0.0;
  S = 0.0;
 for(i=1;i<=12000;i++)
 {
  slopeA = dA;
  Amax = A;
  slopeB = dB;
  Bmax = B;
  dA = beta*(-A + (alpha/(1+pow(C,n)))) * dt;
  dB = beta*(-B + (alpha/(1+pow(A,n)))) * dt;
  dC = beta*(-C + (alpha/(1+pow(B,n))) + (kappa*S/(1+S))) * dt;
  dS = ((-ks0*S) + (ks1*B) - (neta*(S-Se))) * dt; 
  C +=dC;
  B +=dB;
  A +=dA;
  S +=dS; 
  //fprintf(fp,"%f %d %d %d %d %d\n",t,1,I,K,J,L); 
  if(i>1000)
 {
 fprintf(fp,"%f %f %f\n",t,A,B); 
 }
 
  t += dt;
}
}
printf("done");
fclose(fp);
getch();
return 0;
}
