
//Program for SIRS cycle on 2-D grid and see the infection propogation


#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int main(void)
{
int i,j,k,m,n;
int t,tim;
int rlzn;
rlzn = 1000;
tim = 200;
m = 40; n = 40;
int tau[m][n];
float initial_frac,i_f;
float total_infect,avg_total_infect;
int inf_nb[m][n];
int tau_O,tau_i;
int site;
tau_O = 13;
tau_i = 4;
initial_frac = 0.5;                                                             // initial fraction of suseptible
int n_rand, m_rand;  
float neta,neta_rand;                                                           
srand(time(0));
FILE *fp;  
fp = fopen("infect_spread.txt","wt");
neta = 0.0;
//while(initial_frac<=1.0)
//{
//avg_total_infect = 0.0;
//for(k=1;k<=rlzn;k++)
//{
//total_infect = 0.0;
for(i=0;i<m;i++)
    {
     for(j=0;j<n;j++)
        {
         //m_rand = rand() % (m+1);
         //n_rand = rand() % (n+1);
         i_f = (float)rand()/RAND_MAX;                                                       
           // if(i== m_rand && j== n_rand)
              if(i== (m/2) && j== (n/2))
              tau[i][j] = 1;
           // else if(i==(m/2) && j==57)
             // tau[i][j] = 1;
            else
              if(i_f<initial_frac)
                 tau[i][j] = 0;
              else   
               {
                //neta_rand = (float)rand()/RAND_MAX;   
                //if(neta_rand<neta)
                 //{
                //  do
                 //  { 
                 //   tau[i][j] = rand() % (tau_O + 1);
                 //  }while(tau[i][j]<=tau_i);
                 //  }
                //else
                 tau[i][j] = tau_i + 1;
               }
        }
    }
for(t=1;t<=tim;t++)
{
 for(i=0;i<m;i++)
    {                                                                                 // loop to check infected neigbors
     for(j=0;j<n;j++)
     {
      inf_nb[i][j] = 0;      
      if(i!=(m-1)) 
        if(tau[i+1][j]>0 && tau[i+1][j]<=tau_i)
               inf_nb[i][j]++;
      if(i!=0)
        if(tau[i-1][j]>0 && tau[i-1][j]<=tau_i)
               inf_nb[i][j]++;       
      if(j!=(n-1))
        if(tau[i][j+1]>0 && tau[i][j+1]<=tau_i)
               inf_nb[i][j]++;
      if(j!=0) 
        if(tau[i][j-1]>0 && tau[i][j-1]<=tau_i) 
               inf_nb[i][j]++;
      }
 } 
for(i=0;i<m;i++)
    {
     for(j=0;j<n;j++)                                                                    // disease cycle    
     {
     // if(i==(m/2) && j==(n/2)/*n/4*/)
       //  tau[i][j] = 1;
      //else if(i==(m/2) && j==(3*n/4))
        // tau[i][j] = 1;
     // else
      // {
        if(tau[i][j]==tau_O)
         tau[i][j] = 0;
        else if(tau[i][j]==0)
         {
          if(inf_nb[i][j]!=0)                                                            // depending on infected neighbors S to R
             tau[i][j] = 1;
         }   
        else
         tau[i][j] = tau[i][j] + 1;
     //   }
     }    
    } 
/*if(t>200)
{
for(i=0;i<m;i++)
    {
     for(j=0;j<n;j++)
        {                                                         
         if(tau[i][j]>0 && tau[i][j]<=tau_i)
         {
          site = 1;
          total_infect++;
         }
        }
    }
}*/
}
for(i=0;i<m;i++)
    {
     for(j=0;j<n;j++)
        {                                                         
         if(tau[i][j]==0)
         site = 0;
         if(tau[i][j]>0 && tau[i][j]<=tau_i)
         {
          site = 1;
          total_infect++;
         }
         if(tau[i][j]>tau_i)
         site = 2;
         printf("%d %d %d\n",i+1,j+1,site);
         fprintf(fp,"%d %d %d\n",i+1,j+1,site);
        }
    fprintf(fp,"\n");
    }
//avg_total_infect += total_infect/(n*m);
//fprintf(fp,"%f\n",total_infect/(n*m));
//printf("%f\n",total_infect/(n*m));
//}    
//avg_total_infect = avg_total_infect/rlzn;
//fprintf(fp,"%f %f\n",initial_frac,avg_total_infect);
//printf("%f %f\n",initial_frac,avg_total_infect);
//initial_frac += 0.01; 
//}
fclose(fp);
printf("done");
getch();
return 0;
}
