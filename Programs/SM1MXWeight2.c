// Greedy local search algorithm for finding maximum clique 
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define LEN 200
//#define ed 0.16*LEN
//#define FILENAME "txt10.txt"
//#define FILENAME "ll.txt"
//#define FILENAME "c-fat200-1.clq.txt"
//#define FILENAME "p_hat300-1.clq.txt"
//#define FILENAME "hamming8-2.clq.txt"
//#define FILENAME "johnson8-4-4.clq.txt"
//#define FILENAME "C250.9.clq.txt"
#define FILENAME "gen200_p0.9_55.b.txt"
//#define FILENAME "san400_0.9_1.clq.txt"
//#define FILENAME "sanr200_0.9.clq.txt"
//#define FILENAME "brock400_4.b.txt"
//#define FILENAME "r500.5.txt"
//#define FILENAME "MANN_a45.clq.b.txt" 
//#define FILENAME "keller6.clq.txt" 
 
int Max=1;                       // max clique size
int target=55;                  //Max clique size given
int m=LEN+1,n=LEN+2;
int fixed[LEN+1][LEN+2];        // Adjacancy matrix of the graph
int c0[LEN+1];                 // store currently found max clique
int cc0[3][LEN+1];             // store residual graph

int no=0;     // number of iterations collectively
int lit=0;    // number of iterations for current (single ) iteration
int select_Max_Var(int ,int,int,int);

void Update_Deg(int, int);
void residual_graph_Update(int *, int  ,int *,int);
float mxdeg(int ,int (*)[m],int ,int );
clock_t start; clock_t end;  clock_t dif;
int main(){
       int i,j,k,r;
    printf("\nCliques getting computed\n");
    for(i=1;i<m;i++) 
      {fixed[i][0]=i; fixed[0][i]=i; for(j=1;j<n;j++) fixed[i][j]=0; }     //initialization         
    FILE *f=fopen(FILENAME,"r");
    int integer1,integer2; 
    while(fscanf(f,"%d",&integer1)>0)   
	    {fscanf(f,"%d",&integer2);
	      fixed[integer1][integer2]=1;
	      fixed[integer2][integer1]=1;
	      fixed[integer1][n-1]=fixed[integer1][n-1]+1;
	      fixed[integer2][n-1]=fixed[integer2][n-1]+1;
	     }

  int t,calls=0,countt=0, increment;
  time_t ti; srand((unsigned) time(&ti));
  start=clock();
  for(i=target/2;i<LEN;i++)
   { if(Max>=target) break;
       t=i; lit=0; increment=0; int restart=0.1*target;//1+rand()%LEN; //printf("\nt=%d\n",t);
      for(j=1;j<m;j++)
        {cc0[0][j]=0;cc0[1][j]=0;cc0[2][j]=0;if(fixed[t][j]==1) c0[j]=j; else c0[j]=0;}
      for(k=0;k<restart;k++)
       {r= Greedy_Swap(t);
        if(r>Max) {Max=r; increment=0;} else increment++;
       if((target>40)&&(increment>restart/2)) break;
	   else if(increment>target/2) break;  //pruning 38target/4 for brock400_3
        if(Max>=target) break;
        for(j=1;j<m;j++) if(c0[j]==-1)c0[j]=j;
     }if(Max>=target) break;}
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
    int i,j,clen=1,c0len,cpos,it=0,x=2; if((target/10)>2) x=target/10; if(target/10>5) x=target/5;
    int cflen=fixed[k][n-1],c[cflen+1]; for(i=0;i<=cflen;i++) c[i]=0;
    c[clen]=k; c0len=cflen; 
    Update_Deg(clen, cflen);
  //printf("\ncalled vertex k=%d\t\n",k);  for(i=1;i<m;i++) printf("\n%d\t%d\t%d\n",c0[i],cc0[0][i],cc0[1][i]);
   
  while(cflen>0)
     { it++; lit++;//iteration++
       if((clen+cflen)<=Max)return;
        i=select_Max_Var(cflen,c0len,clen,it);
       if(c0[i]<=0) break; 
       c[++clen]=c0[i]; 
   if((it<0.25*target)&&(cc0[1][i]<0.25*target)) {cc0[1][i]=cc0[1][i]+x; } //target/5 for MANN_45 
     
//	if((cc0[1][i]<0.25*target)) cc0[1][i]=cc0[1][i]+x;  else  
	// if((cc0[1][i]<0.8*target)) cc0[1][i]=cc0[1][i]+1; 
       c0[i]=-1;cflen--; cpos=clen; 
       residual_graph_Update(c,cpos,&cflen,clen);
        Update_Deg(clen, cflen);
       no++;// for(i=1;i<m;i++) printf("\n%d\t%d\t%d\n",c0[i],cc0[0][i],cc0[1][i]);
     }
  clen++; end=clock(); 
    dif=end-start; 
  printf("\n vertex k:%d \t  cliques size(clen) :%d: Time %.6f # of iterations %d",k,clen-1,(float)(dif)/CLOCKS_PER_SEC, no);
// for(i=1;i<clen;i++)printf(" %d\t",c[i]);
   return clen-1;
  }
//...........................................................................
int select_Max_Var(int cflen,int c0len, int clen, int it)//done//change
    { int i,j,k,c0pos=0,c0max=0,flag=0,list[2][cflen], cc0avg=0,x=2; //if((target/10)>2) x=target/10; if(target/10>5) x=target/5;
         
      for(k=1;k<m;k++){if(c0[k]>0) cc0avg=cc0avg+cc0[0][k]; }
		for(k=0;k<m;k++){if(c0[k]>0){flag=1;c0pos=k;c0max=cc0[0][k];break;}}
      if(flag==1)
         {for(j=k+1;j<m;j++)
           {if(c0[j]>0)
		     {if((cc0[0][j]>c0max)&&(cc0[1][j]<it))
		     //if((cc0[0][j]>c0max)&&((cc0[1][j]<it)||((it<5)&&(cc0[0][j]<5*it))))
            //if((cc0[0][j]>c0max)&&((cc0[1][j]<it)||((it<0.4*target)&&(cc0[0][j]>cc0avg/cflen))))
		     {c0pos=j;c0max=cc0[0][j];}      
         }}}
    return c0pos;
    }
//...................................................................................  
 void residual_graph_Update(int *c, int cpos,int *cflen,int clen)//update c1len, cflen, m
  {  int i,j,count=0;
      for(i=1;i<m;i++)
        { if(c0[i]>0)
             {if( fixed[c[cpos]][c0[i]]==0){ *cflen=*cflen-1; c0[i]=-1;cc0[0][i]=0;}}
        } 
    }     
  //................................................................................
 void Update_Deg(int clen, int cflen )
  {  int i,j,nu=0,count1=0,k=5,count2=0; //*mi=0;*ma=0;
     for(i=1;i<m;i++)cc0[0][i]=0;
     if(target/3>10) k=10; float p=0.4; //(p~[0.1,0.2,0.3,0.4]
     
	 for(i=1;i<m;i++)
       { if(c0[i]>0) if(((lit-cc0[2][i])>k)&&(cc0[1][i]>p*target))cc0[1][i]=cc0[1][i]-1;//to avaid stagnation	
		    for(j=i+1;j<m;j++)
             { if(c0[j]>0)
                {if(fixed[c0[i]][c0[j]]==1)
                  { cc0[0][i]=cc0[0][i]+1;  cc0[0][j]=cc0[0][j]+1;} 
        } }}
	
//for(i=1;i<m;i++) if(cc0[0][i]>target-clen-2) (*d)++;
}
// The End........................................................................... 

