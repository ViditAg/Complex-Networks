#include<stdio.h>
#include<stdlib.h>
#include<math.h>
float logis(float x);
int main(void)
{
  int i,j,k,n,t;
  n = 100;                                                                          // lattice size
  t= 1000;                                                                        // total time steps
  float x[n][2],x_in[n];
  float E;
  float p;
  float prob;
  int epsi,netai,eps[n],neta[n],eps_in[n],neta_in[n];
  float pr,prewire;       
  int count;
  float Echaos;                                                     // initializing network rewiring probability
  FILE *fp;  
  fp = fopen("epsilon_spread_paper-001.txt","wt");
  srand(time(0));                                                                //random seeding to be depended on time
for(k=0;k<1000;k++)                                                               // no. of re-runs of the system
{
prewire = 0.01;
//while(prewire<=1.0)
//{                                                                  // intializing random linking probability
   E = 0.995;                                                                      // initializing coupling strength
   Echaos = 0.0;
   prob = 0.8;    
   count = 0;
 for(i=0;i<n;i++)               
            {
             x_in[i] = (float)rand()/RAND_MAX;                                             //random initialization of lattice point values                                              
             p = (float)rand()/RAND_MAX;
                     if(p<=prob)                                                      //random linking
                       {
                        eps_in[i] = rand() % n;
                        neta_in[i] = rand() % n;     
                       } 
                     else                                                              //nearest neighbor linking
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
 //while(prob<=1.0)
   while(E>=0.5)
        {
        for(i=0;i<n;i++)
        {
        x[i][0] = x_in[i];
        eps[i] = eps_in[i];
        neta[i] = neta_in[i];
        }
         for(j=1;j<t;j++)
            {                                                           
             for(i=0;i<n;i++)
                {
                  pr = (float)rand()/RAND_MAX;                                          // network rewiring variable
                  if(pr<=prewire)                                                         // network rewiring condition
                    {
                     p = (float)rand()/RAND_MAX;
                     if(p<=prob)                                                      //random linking
                       {
                        eps[i] = rand() % n;
                        neta[i] = rand() % n;     
                       } 
                     else                                                              //nearest neighbor linking
                       {
                        if(i==0)
                          {
                           eps[i] = i+1;
                           neta[i] = n-1;
                          }
                        else if(i==(n-1))
                          {
                           eps[i] = 0;
                           neta[i] = i-1;
                          }
                        else
                          {
                           eps[i] = i+1;
                           neta[i] = i-1;
                          }
                       }             
                    }
                 
                  epsi = eps[i];
                  netai = neta[i];
                  x[i][1] =  (1.0 - E)*logis(x[i][0]) + (E/2)*(x[epsi][0]+x[netai][0]) ;    // coupled map equation
                  if(j>994)                                                              // values taken towards the end of iterations
                     {
                       //fprintf(fp,"%f %f ",E,x[i][1]);       
                     if(x[i][1] >= 0.74999 && x[i][1] <= 0.75001 && count==0)   
                     {
                     //fprintf(fp,"%f\n",x[i][1]);    
                     //printf("%f %f\n",E,x[i][1]);
                     Echaos = E; 
                     }
                   else
                   {
                    //fprintf(fp,"\n");  
                    count++;
                   }  
                     }
                  } 
       for(i=0;i<n;i++)
     {
     x[i][0]  =  x[i][1];
     }
      }
  E -= 0.005; 
//prob += 0.01;
}
//prewire += 0.0125;
//fprintf(fp,"\n");
//} 
fprintf(fp,"%f\n",Echaos);
printf("%f\n",Echaos);
}
  fclose(fp);
  printf("done");
  getch();
  return 0;
}

float logis(float x)
{
float fx;
fx = 4.0*x*(1-x);
return fx;
}
