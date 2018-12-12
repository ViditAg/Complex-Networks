#include<stdio.h>
#include<stdlib.h>
#include<math.h>
float logis(float x);
int main(void)
{
  int i,j,k,l,n,t;
  n = 100;                                                                              // lattice size
  t= 1000;
  float x[n][2],x_in[n];
  float E;
  float p;
  float prob;
  int epsi,netai,eps[n],neta[n],eps_in[n],neta_in[n];
  srand(time(0)); 
  prob = 1.0;                                                                        // probability of choosing random link
  FILE *fp;  
  fp = fopen("static_random_network.txt","wt");                
for(k=0;k<1;k++)
{  
    for(i=0;i<n;i++)
    {
     x_in[i] = (float)rand()/RAND_MAX;                                         //random initialisation of lattice point values
     p = (float)rand()/RAND_MAX;
        if(p<=prob)                                                                 // initialization of links connectitions  
           {
            eps_in[i] =  rand() % n;         
            neta_in[i] = rand() % n;        
           }
        else
           {
            if(i==0)
            {
             eps_in[i] = i+1;
             neta_in[i] = n-1;
            }
            else if(i==(n-1))
            { 
             eps_in[i] = 0;
             neta_in[i] = i-1;
            }
            else
            {
             eps_in[i] = i+1;
             neta_in[i] = i-1;
            }
           }
     }
E = 0.5;
//while(prob<=1.0)
 while(E<=0.995)
   {               
  for(i=0;i<n;i++)
  {
   x[i][0] = x_in[i];                                                                //random initialisation of lattice point values
   eps[i] =  eps_in[i];         
   neta[i] = neta_in[i];        
  }
   for(j=1;j<t;j++)
     {
      for(i=0;i<n;i++)
         {
          epsi = eps[i];
          netai = neta[i];
          x[i][1] =  (1.0 - E)*logis(x[i][0]) + (E/2)*(x[epsi][0]+x[netai][0]) ;      // coupling condition
          if(j>994)                                                                         //   printing the last 10 iterations
                   {
                  //printf("%f %f\n",E,x[j][i]);    
                  //fprintf(fp,"%f %f\n",E,x[j][i]);
                   // printf("%f %f\n",E,x[i][1]);         
                      fprintf(fp,"%f %f\n",E,x[i][1]); 
                  }         
         } 
     for(i=0;i<n;i++)
         {
           x[i][0] = x[i][1];
         }
     
      }
  E += 0.01;    
//prob += 0.01;
}
}
  printf("done");
  fclose(fp);
  getch();
  return 0;
}

float logis(float x)
{
float fx;
fx = 4.0*x*(1-x);
return fx;
}
