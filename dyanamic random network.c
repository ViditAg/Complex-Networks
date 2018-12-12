#include<stdio.h>
#include<stdlib.h>
#include<math.h>
float logis(float x);
int main(void)
{
  int i,j,n,t;
  n = 50;
  t= 1000;
  float x[n][2];
  float E;
  float p;
  float prob;
  int epsi,netai,eps[n],neta[n];
  prob = 1.0;  
  E = 0.5;
  FILE *fp;  
  fp = fopen("dynamic_random_network.txt","wt");
  srand(time(0));
//while(prob<=1.0)
//{
 while(E<=0.995)
   {            
   for(i=0;i<n;i++)
    {
     x[i][0] = (float)rand()/RAND_MAX;
    }
   for(j=1;j<t;j++)
     {
      for(i=0;i<n;i++)
         {
           p = (float)rand()/RAND_MAX;
          if(p<=prob)
           {
            eps[i] = rand() % n;
            neta[i] = rand() % n;
           }
        else
           {
            if(i==0)
            {
            eps[i] = i+1;
            neta[i] = n-1;
            }
            else if (i==(n-1))
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
        epsi = eps[i];
        netai = neta[i];
          x[i][1] =  (1.0 - E)*logis(x[i][0]) + (E/2)*(x[epsi][0]+x[netai][0]) ;   
          if(j>995)       
                   {
                  //printf("%f %f\n",E,x[j][i]);    
                  //fprintf(fp,"%f %f\n",E,x[j][i]);
                    //printf("%f %f\n",E,x[i][1]);    
                    fprintf(fp,"%f %f\n",E,x[i][1]);       
                   }
         } 
     for(i=0;i<n;i++)
        {
         x[i][0] = x[i][1];
        }
      }
  E += 0.01;
 // }    
//prob += 0.01;
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
