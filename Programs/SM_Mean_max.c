// Greedy local search algorithm for finding maximum clique 
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define LEN 300
//#define FILENAME "10.txt"
//#define FILENAME "69.txt"
//#define FILENAME "c-fat200-1.clq.txt"
#define FILENAME "p_hat300-2.clq.txt"
//#define FILENAME "hamming6-4.clq.txt"
//#define FILENAME "johnson8-4-4.clq.txt"
//#define FILENAME "C125.9.clq.txt"
//#define FILENAME "gen200_p0.9_44.b.txt"
//#define FILENAME "san200_0.9_1.clq.txt"
//#define FILENAME "sanr400_0.7.clq.txt"
//#define FILENAME "brock200_2.b.txt"
//#define FILENAME "r500.5.txt"
//#define FILENAME "MANN_a9.clq.b.txt" 
//#define FILENAME "killer4.clq.txt" 
 
int Max=1;
int c[LEN];
int clen;
int m=LEN+1,n=LEN+2;
int fixed[LEN+1][LEN+2];
int distance[LEN+1][LEN+3];
int independent[LEN];

int select_Min_Var(int (*)[m], int );
int Greedy_Swap(int);
void Update_Deg(int (*)[m],int,int );
void residual_graph_Update(int *, int (*)[m],int *, int  ,int *,int );

int main(){
       int i,j,k;
   for(i=0;i<m;i++)
    {  for(j=0;j<n;j++)
         {fixed[i][j]=0;distance[i][j]=0;}
         distance[i][++j]=0;
    }  
       for(i=0;i<m;i++){ fixed[i][0]=i;}
       for(j=0;j<n;j++){ fixed[0][j]=j;} 
                                                       
       FILE *f=fopen(FILENAME,"r");
       int integer1,integer2;
       
   while(fscanf(f,"%d",&integer1)>0)
	    {
	      fscanf(f,"%d",&integer2);
	      
	      fixed[integer1][integer2]=1;
	      fixed[integer2][integer1]=1;
	      fixed[integer1][LEN+1]++;
	      fixed[integer2][LEN+1]++;
	     }
//finding distance fixed   
printf("\nCliques getting computed\n");
int J,arr[LEN],count=0; 
for(i=1;i<=LEN;i++)
{     
 for(j=i+1;j<=LEN;j++)
 {  J=j;
    for(k=1;k<=LEN;k++)
    { if(fixed[i][k]!=fixed[j][k])
     count++;  
   }   
 if(fixed[i][J]==1)
 count=count-2;
 distance[i][j]=distance[j][i]=count; 
 distance[i][LEN+1]+=count;
 distance[j][LEN+1]+=count;
 count=0;
} }
//finding mean cost...
   int cost=0; float g;
   for(i=1;i<=LEN;i++) cost=cost+distance[i][LEN+1];
   g=roundf(cost*1.0/LEN);
   for(i=1;i<=LEN;i++)
    distance[i][LEN+2]=fabs(distance[i][LEN+1]-g);
   /*for(i=1;i<=LEN;i++)
    {
                       for(j=1;j<=m+1;j++)
                       {
  printf("%3d",fixed[i][j]);
}printf("\n");} */ 
/*//sorting vertices wrt cost (last column of distance fixed)...\n");
for(i=1;i<m;i++)arr[i]=i;                
int loc,dum,big;
for(i=1;i<m;i++)
   {        big=distance[arr[i]][LEN+2];
            loc=i;
            for(j=i+1;j<m;j++)
               { if(big>distance[arr[j]][LEN+2])
                      {   big=distance[arr[j]][LEN+2];
                           loc=j;              
              }   }   
                 dum=arr[loc];
                 arr[loc]=arr[i];
                 arr[i]=dum;
   }
//printf("\n sorted vertives are ..................\n");
//for(i=1;i<=LEN;i++)
  //                 printf("%3d\t",arr[i]);

//printf("\n independent set ..................\n");
int incr=1;
independent[1]=arr[1];
for(i=2;i<=LEN;i++)
 { for(k=1;k<=incr;k++)
   { if(fixed[arr[i]][independent[k]]==1)
       {         count++;
                 break;                
    }   }
if(count==0)
 independent[++incr]=arr[i]; 
count=0;
}
for(k=1;k<=incr;k++) printf("%d\t", independent[k]);
//printf("\nfixed[76][LEN+1]=%d\n",fixed[76][LEN+1]);
//................................................
 */
  clock_t start; clock_t end;  clock_t dif;
    start=clock();
    time_t ti;srand((unsigned) time(&ti));
  for(i=1;i<25;i++){
    int t=1+rand()%LEN;
    if(fixed[t][LEN+1]<Max) continue;
     k= Greedy_Swap(t);
      if(k>Max) Max=k;
     }
    end=clock(); 
    dif=end-start;
       printf("\ntime in seconds is %.5f\n",(float)(dif)/CLOCKS_PER_SEC); 
       printf("\nMax clique=%d\n",Max);
        for(i=1;i<=clen;i++) //initialization
       printf("%d\t",c[i]);
       getch();
   return 0;
   }
//..................................................................................
int Greedy_Swap(k) {
    int i,j,s,p;
    int c0[3][m],cpos,c0len;
     c0len=clen=0; 
    for(i=0;i<m;i++) //initialization
      {c[i]=-1;c0[0][i]=-1; c0[1][i]=-1;}
     c[++clen]=k; 
// printf("\n adjacent vertices of %d are\n",k);
     for(i=1;i<m;i++){  if(fixed[i][k]==1){
                      //  printf("%d\t", c0[0][c0len++]=i); 
                       c0[0][c0len++]=i;
                    }   } 
  
   // printf("\n........................................................");
   Update_Deg( c0,c0len,k);
   Update_Deg(c0,c0len,0);
   // for(i=0;i<c0len;i++)printf("\n%d\t%d\t%d\n",c0[0][i],c0[1][i],c0[2][i]);
   // printf("\n................");
    int cflen=c0len;
  while(cflen>0)
   {  //if((clen+cflen)<=Max) return;
       i=select_Min_Var(c0,c0len);
       c[++clen]=c0[0][i]; c0[0][i]=-1;c0[1][i]=-1;c0[2][i]=0;cflen--; cpos=clen;
       residual_graph_Update(c,c0,&c0len,cpos,&cflen,clen);
        Update_Deg(c0,c0len,0);
     }
  //printf("\nvertex %d \t  cliques size(clen) :%d \n",k,clen);
//printf("\n list C:\t"); for(i=1;i<=clen;i++) printf("%d\t", c[i]);  printf("\n");
   return clen;
  }
  //...........................................................................
int select_Min_Var(int (*c0)[m], int c0len)//done//change
    { 
       int i,j,c0pos,c0min,s,pos,list[c0len]; 
      for(i=0;i<c0len;i++) list[i]=0; 
      
     // for(i=0;i<c0len;i++) printf("%d\t%d\t%d\n",c0[0][i],c0[1][i],c0[2][i]);
      for(i=0;i<c0len;i++)
       {if(c0[0][i]>0) 
         for(j=1;j<=c0[2][i];j++)
          list[j]++;
       }
     for(i=c0len-1;i>=0;i--)
        if(list[i]>=i)
          {s=i; break;}  
     for(i=0;i<c0len;i++)
        {if(c0[0][i]>0) 
          { c0min=c0[1][i]; c0pos=i;break;
          }}
        for(j=i+1;j<c0len;j++)
          {if(c0[0][j]>0) 
              {  if((c0min>c0[1][j])&&(c0[2][j]>=s))
                  {c0pos=j;c0min=c0[1][j];} 
            } }
      return c0pos;
    }
//...................................................................................  
 void residual_graph_Update(int *c, int (*c0)[m],int *c0len, int cpos,int *cflen,int clen)//update c1len, cflen, c0len
  {  int i,j,count=0;
      for(i=0;i<*c0len;i++)
        { if(c0[0][i]>0)
            {if( fixed[c[cpos]][c0[0][i]]==0 )
              {    *cflen=*cflen-1; 
                   c0[0][i]=-1;c0[1][i]=-1;c0[2][i]=0;
              }
      } }}    
  //................................................................................
 void Update_Deg(int (*c0)[m], int c0len, int p)
  {  int i,j,sum,avg,count=1;
    if(p==0)
       {
       for(i=0;i<=c0len;i++)c0[2][i]=0;
       for(i=0;i<c0len-1;i++)//updating c0[2][i] list
        { if(c0[0][i]>0)
           {for(j=i+1;j<c0len;j++)
             { if(c0[0][j]>0)
                {if(fixed[c0[0][i]][c0[0][j]]==1)
                  { c0[2][i]=c0[2][i]+1;  c0[2][j]=c0[2][j]+1; }   
            
          }}}}} 
      else
      {  sum=distance[p][LEN+1];
          for(i=0;i<=c0len;i++)c0[1][i]=-1;
          for(i=0;i<c0len;i++)
            {  if(c0[0][i]>0)
                count++; sum=sum+distance[c0[0][i]][LEN+1];
             }    
       avg=roundf(sum*1.0/count);
      // printf("\n avg=%d\n",avg);
       for(i=0;i<c0len;i++) c0[1][i]=fabs(distance[c0[0][i]][LEN+1]-avg);
  // for(i=0;i<c0len;i++) printf("\n%d\t%d\n",c0[0][i],c0[1][i]);
  }  }
// The End........................................................................... 

