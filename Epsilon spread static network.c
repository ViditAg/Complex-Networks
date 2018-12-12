#include<stdio.h>
#include<stdlib.h>
#include<math.h>
float logis(float x);
int main(void)
{
  int i,j,k,l,n,t;
  n = 50;                                                                              // lattice size
  t= 1000;
  float x[n][2],x_in[n];
  float E;
  float p;
  float prob;
  int epsi,netai,eps[n],neta[n],eps_in[n],neta_in[n];
  float Echaos;
  int count;
  srand(time(0)); 
  prob = 1.0;                                                                        // probability of choosing random link
  FILE *fp;  
  fp = fopen("epsilon_spread_static.txt","wt");                
for(k=0;k<1000;k++)
{  
E = 0.995;
Echaos = 0.0;
count=0;
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
          epsi = eps[i];
          netai = neta[i];
          x[i][1] =  (1.0 - E)*logis(x[i][0]) + (E/2)*(x[epsi][0]+x[netai][0]) ;      // coupling condition
          if(j>994)                                                                         //   printing the last 10 iterations
                   {  
                    // fprintf(fp,"%f %f ",E,x[i][1]);       
                     if(x[i][1] >= 0.74999 && x[i][1] <= 0.75001 && count==0)   
                     {
                     
                      //fprintf(fp,"%f\n",x[i][1]);    
                     // printf("%f %f\n",E,x[i][1]);
                      Echaos = E; 
                     }
                   else
                   {                    
                    count++;
                    //fprintf(fp,"\n");  
                   } 
                  }         
         } 
     for(i=0;i<n;i++)
         {
           x[i][0] = x[i][1];
         }     
      }
  E -= 0.01;    
//prob += 0.01;
}
fprintf(fp,"%f\n",Echaos); 
printf("%f\n",Echaos);
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
