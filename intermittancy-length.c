#include<stdio.h>
#include<stdlib.h>
#include<math.h>
float logis(float x);
int main(void)
{
  int i,j,k,kmax,n,t;
  n = 100;                                                                          // lattice size
  t= 5000;
  kmax = 100;                                                                        // total time steps
  float x[n][2];
  float E;
  float p;
  float prob;
  int epsi,netai,eps[n],neta[n];
  float pr,prewire;   
  float z;                                                                       // initializing network rewiring probability
  FILE *fp;  
  fp = fopen("intermittancy-length-01-extreme.txt","wt");
  srand(time(0));
  int count,start,end,length;                                                                //random seeding to be depended on time
  float avglength;
prewire = 0.01;
//while(prewire<=1.0)
//{                                                                                // intializing random linking probability
   E = 0.73;                                                                      // initializing coupling strength
   prob = 0.8;    
// while(prob<=1.0)
   while(E<=0.78)
        {
   avglength = 0.0;
   for(k=0;k<kmax;k++)
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
         start = t;
         count = 0;
         end = 0;
         length = 0;
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
  //                fprintf(fp,"%d %f\n",j,x[i][1]);
                 // printf("%d %f\n",j,x[i][1]);
                  z += pow((x[i][1]- 0.75),2)/n;
                  } 
      // fprintf(fp,"%d %f\n",j,z);
      // printf("%d %f\n",j,z);
       for(i=0;i<n;i++)
     {
     x[i][0]  =  x[i][1];
     }  
    if(z<0.00001 && count == 0)
    {
     start = j;
     count++;
    }
    if(z>0.00001)
    {
    end = j;
    }   
}
//printf("%d\n%d\n",start,end);
if(start<end)
length = end - start; 
//printf("%f %d\n",E,length);
//fprintf(fp,"%d\n",length);
avglength += length/kmax; 
}
printf("%f %f\n",E,avglength);
fprintf(fp,"%f %f\n",E,avglength);
// fprintf(fp,"%f\n",avglength);
  E += 0.0001; 
//prob += 0.01;
}
//prewire += 0.002;
//fprintf(fp,"\n");
//}
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
