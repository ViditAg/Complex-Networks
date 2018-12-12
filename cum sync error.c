#include<stdio.h>
#include<stdlib.h>
#include<math.h>
float logis(float x);
int main(void)
{
  int i,j,k,n,m,t;
  n = 50;
  m = 1;                                                                          // lattice size
  t= 10100;                                                                        // total time steps
  float x[n][2],x_in[n];
  float E;
  float p;
  float prob;
  int epsi,netai,eps[n],neta[n],eps_in[n],neta_in[n];
  float pr,prewire;   
  float z;                                                                      // initializing network rewiring probability
  FILE *fp;  
  fp = fopen("cum sync error.txt","wt");
  srand(time(0));                                                                //random seeding to be depended on time                                                                               
  
                                                                        
   prob = 0.65;                                                                    // intializing random linking probability
 //while(prob<=1.0)
for(k=0;k<m;k++)
{
  E = 0.6;   
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
prewire = 0. 1;
  //while(prewire<=1.0)
  //{ 
  // while(E<=0.995)
       // {
         z = 0.0;
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
                  if(j>100)                                                                 // excluding first 100 iterations
                  {
                   /*if(j>9990)
                   {
                    printf("%f %f\n",E,x[i][1]);
                    fprintf(fp,"%f %f\n",E,x[i][1]);
                   }*/
                   z += pow((x[i][1]- 0.75),2)/(n*(t-100));
                  } 
                  } 
       for(i=0;i<n;i++)
     {
     x[i][0]  =  x[i][1];
     }
    }
fprintf(fp,"%f\n",z);
printf("%f\n",z);
//E += 0.01; 
//prob += 0.01;
//}
//prewire += 0.01;
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
