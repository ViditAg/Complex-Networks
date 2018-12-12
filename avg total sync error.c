#include<stdio.h>
#include<stdlib.h>
#include<math.h>
float logis(float x);
int main(void)
{
  int i,j,k,n,m,t;
  n = 100;
  m = 100;                                                                         
  t= 1100;                                                                       
  float x[n][2];
  float E;
  float p;
  float prob;
  int epsi,netai,eps[n],neta[n];
  float pr,prewire;   
  float z,z_avg,z_max,z_min;                                                                      
  float x_mean;
  FILE *fp;  
  fp = fopen("avg sync error x_mean pt=0.95.txt","wt");
  srand(time(0));                                                                                                                                                                                                                      
   prob = 0.8;                                                                    
  E = 0.3;   
  prewire = 0.95;
  //while(prewire<=1.0)
  //{ 
   while(E<=0.99995)
        {
     z_avg = 0.0;
     z_max = 0.0;
     z_min = 100000;            
     for(k=0;k<m;k++)
     {    
         for(i=0;i<n;i++)               
            {
             x[i][0] = (float)rand()/RAND_MAX;                                             //random initialization of lattice point values                                              
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
         z = 0.0;      
         for(j=1;j<t;j++)
            {                                                           
             x_mean = 0.0;
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
                   /*if(j>9990)
                   {
                    printf("%f %f\n",E,x[i][1]);
                    fprintf(fp,"%f %f\n",E,x[i][1]);
                   }*/
                 x_mean += x[i][1]/n;
                 } 
       if(j>1000)
       {
        for(i=0;i<n;i++)
         {
          z += pow((x[i][1]- x_mean),2)/(n*(t-1000));
         }
       }
       for(i=0;i<n;i++)
     {
     x[i][0]  =  x[i][1];
     }
    }
z_avg +=z/m;
if(z>z_max)
{
 z_max = z;
}
if(z<z_min)
{
 z_min = z;
}
}
fprintf(fp,"%f %f %f %f\n",E,z_avg,z_max,z_min);
printf("%f %f %f %f\n",E,z_avg,z_max,z_min);
E += 0.005; 
//prewire += 0.01;
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
