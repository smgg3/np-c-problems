// Greedy local search algorithm for finding maximum clique 
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define LEN 10
#define target 5
//#define ed 0.16*LEN
#define FILENAME "txt10.txt"
//#define FILENAME "ll.txt"
//#define FILENAME "c-fat500-5.clq.txt"
//#define FILENAME "p_hat1000-3.clq.txt"
//#define FILENAME "hamming8-2.clq.txt"
//#define FILENAME "johnson8-4-4.clq.txt"
//#define FILENAME "C500.9.clq.txt"
//#define FILENAME "gen400_p0.9_55.b.txt"
//#define FILENAME "san400_0.9_1.clq.txt"
//#define FILENAME "sanr400_0.7.clq.txt"
//#define FILENAME "brock200_3.b.txt"
//#define FILENAME "r500.5.txt"
//#define FILENAME "MANN_a45.clq.b.txt" 
//#define FILENAME "keller6.clq.txt" 
 
int Max=1;
int m=LEN+1,n=LEN+2;
int fixed[LEN+1][LEN+2];
int c0[2][LEN+1];
int cflen;
int arr[LEN+1];
int no=0,lit=0;
int c[2][target+1];
int select_Max_Var(int,int,int);
int Greedy_Swap(int);
void Update_Deg( int);
void residual_graph_Update( int,  int);
float mxdeg(int ,int (*)[m],int ,int );
clock_t start; clock_t end;  clock_t dif;
int main(){
       int i,j,k,r;
    printf("\nCliques getting computed\n");
    for(i=1;i<m;i++) 
      {fixed[i][0]=i; fixed[0][i]=i; arr[i]=i;for(j=1;j<n;j++) fixed[i][j]=0; }             
    FILE *f=fopen(FILENAME,"r");
    int integer1,integer2; 
    while(fscanf(f,"%d",&integer1)>0)
	    {fscanf(f,"%d",&integer2);
	      fixed[integer1][integer2]=1;
	      fixed[integer2][integer1]=1;
	      fixed[integer1][n-1]=fixed[integer1][n-1]+1;
	      fixed[integer2][n-1]=fixed[integer2][n-1]+1;
	     }
  /*/.sort min deg vertex first
    int big,loc,dum;
   	for(i=1;i<LEN;i++){ 
       big=fixed[arr[i]][n-1];loc=i;
       for(j=i+1;j<=LEN;j++)
        { if(fixed[arr[j]][n-1]<big){big=fixed[arr[j]][n-1];loc=j;}}
       dum=arr[i]; arr[i]=arr[loc];arr[loc]=dum;
    }  
   //  printf("\nsorted array\n"); for(j=1;j<m;j++)  printf("%d\t",arr[j]);
  ///*///SM1Weight......................
  int t,calls=0,countt=0, increment;
  time_t ti; srand((unsigned) time(&ti));
  start=clock();
 // for(i=1;i<LEN/2;i++){
    i=3;// if(Max>=target) break;
        lit=0; increment=0; int restart=0.2*target;cflen=fixed[i][n-1];//1+rand()%LEN; //printf("\nt=%d\n",t);
       for(j=1;j<=target;j++) c[1][j]=0;
      for(j=1;j<m;j++)
        {if(fixed[i][j]==1) c0[0][j]=j; else c0[0][j]=0;}
      for(k=0;k<3;k++)
       {r= Greedy_Swap(i);
        if(r>Max) Max=r; 
        for(j=1;j<m;j++) if(c0[0][j]==-1){c0[0][j]=j; cflen++;}
        if((Max>=target)||(cflen<target)) break; 
       }//if(Max>=target) break;}
    end=clock(); 
    dif=end-start;
     printf("\ntime in seconds is %.5f\t",(float)(dif)/CLOCKS_PER_SEC); 
     printf("Max clique=%d, # Iterations=%d & repetation ...\n",Max,no);
       //for(i=1;i<m;i++) printf("%d\t",arr[i]);
       getch();
   return 0;
   }
//..................................................................................
int Greedy_Swap(int k) {
    int i,j,clen=1,c0len,cpos,it=0;
     for(i=0;i<=cflen;i++) c[0][i]=0;
    c[0][clen]=k; c0len=cflen; 
    Update_Deg(clen);
  printf("\ncalled vertex k=%d\t\n",k);  for(i=1;i<m;i++) printf("\n%d\t%d\n",c0[0][i],c0[1][i]);printf("\n................\n");
   
  while(cflen>0)
     { it++; lit++;//iteration++
       //if((clen+cflen)<=Max) return;
        i=select_Max_Var(c0len,clen,it);
       if(c0[0][i]<=0) break; 
       c[0][++clen]=c0[0][i]; 
  
       c0[0][i]=0;cflen--; cpos=clen;  printf("returned vertex:%d", c[0][cpos]);
       residual_graph_Update(cpos,clen);
        Update_Deg(clen);
       no++; for(i=1;i<m;i++) printf("\n%d\t%d\n",c0[0][i],c0[1][i]); printf("------------------------n");
     }
  clen++; end=clock(); 
    dif=end-start; 
  printf("\n vertex k:%d \t  cliques size(clen) :%d: Time %.6f # of iterations %d",k,clen-1,(float)(dif)/CLOCKS_PER_SEC, no);
// for(i=1;i<clen;i++)printf(" %d\t",c[i]);
  if((clen-1)>Max) for(i=1;i<clen;i++) c[1][i]=c[0][i];
   return clen-1;
  }
//...........................................................................
int select_Max_Var(int c0len, int clen, int it)//done//change
    { int i,j,k,c0pos=0,c0max=0,flag=0;  
         
      for(k=0;k<m;k++){if(c0[0][k]>0){flag=1;c0pos=k;c0max=c0[1][k];break;}}
      if(flag==1)
         {for(j=k+1;j<m;j++)
           {if(c0[0][j]>0)
		     {if(c0[1][j]>c0max) {c0pos=j;c0max=c0[1][j];}      
         } } }
    return c0pos;
    }
//...................................................................................  
 void residual_graph_Update( int cpos,int clen)//update c1len, cflen, m
  {  int i,j,count=0;
      for(i=1;i<m;i++)
        { if(c0[0][i]>0)
             {if(fixed[c[0][cpos]][c0[0][i]]==0){ cflen=cflen-1; c0[0][i]=-1;c0[0][i]=0;}}
        } 
    }     
  //................................................................................
 void Update_Deg(int clen)
  {  int i,j; 
     for(i=1;i<m;i++) c0[1][i]=0;
    
	 for(i=1;i<m;i++)
       { if(c0[0][i]>0) 	
		    for(j=i+1;j<m;j++)
             { if(c0[0][j]>0)
                {if(fixed[c0[0][i]][c0[0][j]]==1)
                  { c0[1][i]=c0[1][i]+1;  c0[1][j]=c0[1][j]+1;} 
        } }}
	
//for(i=1;i<m;i++) if(cc0[0][i]>target-clen-2) (*d)++;
}
// The End........................................................................... 

