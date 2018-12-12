#include<stdio.h>
#include<stdlib.h>
#include<math.h>
float logis(float x);
int main(void)
{
  int i,j,k,kmax,n,t;
  n = 50;                                                                          // lattice size
  t= 3000;        
  kmax = 500;                                                                // total time steps
  float x[n][2],x_in[n];
  float E;
  float p;
  float prob;
  float z;
  int epsi,netai,eps[n],neta[n],eps_in[n],neta_in[n];
  int jsync;
  float jsyncavg,jsyncmax,jsyncmin;
  float pr,prewire;                                                            // initializing network rewiring probability
  FILE *fp;  
  fp = fopen("prob_rewire_synctime-18.txt","wt");
  srand(time(0));                                                                //random seeding to be depended on time
prewire = 0.0;
prob = 0.5;                                                                       // intializing random linking probability         
E = 0.75;                                                                         // initializing coupling strength
while(prewire<=1.0)
// while(prob<=1.0)
  //while(E<=0.99995)
  {                                                                 
   jsyncavg = 0.0;   
   jsyncmax = 0.0;
   jsyncmin = 10000.0;  
    //    {
           for(k=0;k<kmax;k++)
               {
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
         for(i=0;i<n;i++)
         {
         x[i][0] = x_in[i];
         eps[i] = eps_in[i];
         neta[i] = neta_in[i];
         }
         for(j=1;j<t;j++)
            {                                                           
             z = 0.0;
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
                    // printf("%f %f\n",prewire,x[i][1]);    
                      //fprintf(fp,"%d %f\n",j,x[i][1]);
                      //printf("%d %f\n",j,x[i][1]);
                      z += pow((x[i][1]-0.75),2)/n;
                       // fprintf(fp,"%f %f\n",prewire,x[i][1]);
                    //fprintf(fp,"%f %f %f\n",prewire,prob,x[i][1]);    
                   //   fprintf(fp,"%f %f\n",E,x[i][1]);                            
                  }     
       for(i=0;i<n;i++)
     {
     x[i][0]  =  x[i][1];
     } 
    // fprintf(fp,"%d %f\n",j,z);
    // printf("%d %f\n",j,z);
     if(z>0.000001)
     jsync = j; 
      }
//printf("%d\n",jsync);
//fprintf(fp,"%d\n",jsync);
jsyncavg += jsync;
if(jsyncmax<jsync)
jsyncmax = jsync;
if(jsyncmin>jsync)
jsyncmin = jsync;
}

jsyncavg = jsyncavg/kmax;
printf("%f %f %f %f\n",prewire,jsyncavg,jsyncmax,jsyncmin);
fprintf(fp,"%f %f %f %f\n",prewire,jsyncavg,jsyncmax,jsyncmin);
//fprintf(fp,"\n");
prewire += 0.01;
 // E += 0.005; 
//prob += 0.01;
//}
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
