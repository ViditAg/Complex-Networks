# include<stdio.h>
# include<stdlib.h>
# include<math.h>
int main(void)
{
int i;
float t,dt;
t = 0.0; dt = 0.1;
float A,B,C,S,ks0,ks1,n,beta,alpha,Se,neta,kappa,dA,dB,dC,dS;
float slopeA,Amax,slopeB,Bmax,slopeC,Cmax,slopeS,Smax;
ks0 = 1;
ks1 = 0.025;
n = 3;
beta = 0.1;
neta = 1.0;
FILE *fp;
fp = fopen("reprissilator.txt","wt");
alpha = 46;
kappa = 14; 
Se = 1.0;
 S = 0.0;
//while(kappa<=60.0)          
while(Se>=0.0)
 {  
 B = 0.0;
 C = 0.0;
 A = 0.0;
 for(i=1;i<=100000;i++)
 {
  slopeA = dA;
  Amax = A;
  slopeB = dB;
  Bmax = B;
  slopeC = dC;
  Cmax = C;
  slopeS = S;
  Smax = S;
  dA = beta*(-A + (alpha/(1+pow(C,n)))) * dt;
  dB = beta*(-B + (alpha/(1+pow(A,n)))) * dt;
  dC = beta*(-C + (alpha/(1+pow(B,n))) + (kappa*S/(1+S))) * dt;
  dS = ((-ks0*S) + (ks1*B) - (neta*(S-Se))) * dt; 
  C +=dC;
  B +=dB;
  A +=dA;
  S +=dS;
 /* if(i>98000)
  {
  if(slopeA>0.0 && Amax>A)                                                   //max condition
  {
  printf("%f %f\n",t,A);
  fprintf(fp,"%f %f\n",t,A);
  }
  if(slopeA<0.0 && Amax<A)                                                     //min condition
  {
  printf("%f %f\n",t,A);
  fprintf(fp,"%f %f\n",t,A);
  }                                                            
  if(dA<0.0000000001 && dA>(-0.0000000001))                                        //stable state condition
  {
   printf("%f %f\n",t,A);
   fprintf(fp,"%f %f\n",t,A);
  }
  }*/
  if(i>90000)                                                                //bifurcation
  {
  /*if(slopeA>0.0000000 && Amax>A)                            // variable - A                     //max condition
  {
  printf("%f %f\n",kappa,A);
  fprintf(fp,"%f %f\n",kappa,A);
  }*/
  /*if(slopeA<0.0 && Amax<A)                                                     //min condition
  {
  printf("%f %f\n",kappa,A);
  fprintf(fp,"%f %f\n",kappa,A);
  }*/                                                       
  //if(dA<0.000001 && dA>(-0.000001) && i>99980)                                        //stable state condition
  /*{
   printf("%f %f\n",kappa,A);
   fprintf(fp,"%f %f\n",kappa,A);
  }*/
  /*if(slopeB>0.0 && Bmax>B)                         //variable - B                         //max condition
  {
  printf("%f %f\n",kappa,B);
  fprintf(fp,"%f %f\n",kappa,B);
  }*/
  /*if(slopeB<0.0 && Bmax<B)                                                     //min condition
  {
  printf("%f %f\n",kappa,B);
  fprintf(fp,"%f %f\n",kappa,B);
  } */                                                         
  /*if(dB<0.00001 && dB>(-0.0001)&& i==99980)                                        //stable state condition
  {
   printf("%f %f\n",kappa,B);
   fprintf(fp,"%f %f\n",kappa,B);
  }*/
  if(slopeC>0.0 && Cmax>C)                          //variable - C                         //max condition
  {
  printf("%f %f\n",Se,C);
  fprintf(fp,"%f %f\n",Se,C);
  }
  /*if(slopeC<0.0 && Cmax<C)                                                     //min condition
  {
  printf("%f %f\n",Se,C);
  fprintf(fp,"%f %f\n",Se,C);
  } */                                                           
  if(dC<0.00001 && dC>(-0.0001)&& i==99980)                                        //stable state condition
  {
   printf("%f %f\n",Se,C);
   fprintf(fp,"%f %f\n",Se,C);
  }
  /*if(slopeS>0.0 && Smax>S)                        //variable - S                           //max condition
  {
  printf("%f %f\n",Se,S);
  fprintf(fp,"%f %f\n",Se,S);
  }*/
  /*if(slopeS<0.0 && Smax<S)                                                     //min condition
  {
  printf("%f %f\n",Se,S);
  fprintf(fp,"%f %f\n",Se,S);
  } */                                                           
  /*if(dS<0.00001 && dS>(-0.0001)&& i==99980)                                        //stable state condition
  {
   printf("%f %f\n",Se,S);
   fprintf(fp,"%f %f\n",Se,S);
  }*/
  }
  t += dt;
}
Se -= 0.001;
//kappa += 0.1; 
//fprintf(fp,"\n");
}
fclose(fp);
getch();
return 0;
}
