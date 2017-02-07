// Greedy local search algorithm for finding maximum clique 
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define LEN 800
#define target 23
//#define ed 0.16*LEN
//#define FILENAME "txt10.txt"
//#define FILENAME "ll.txt"
//#define FILENAME "c-fat200-1.clq.txt"
//#define FILENAME "p_hat1500-2.clq.txt"
//#define FILENAME "hamming8-2.clq.txt"
//#define FILENAME "johnson8-4-4.clq.txt"
//#define FILENAME "C500.9.clq.txt"
//#define FILENAME "gen400_p0.9_55.b.txt"
//#define FILENAME "san400_0.9_1.clq.txt"
//#define FILENAME "sanr400_0.7.clq.txt"
#define FILENAME "brock800_1.b.txt"
//#define FILENAME "r500.5.txt"
//#define FILENAME "MANN_a45.clq.b.txt" 
//#define FILENAME "keller6.clq.txt" 
 
int Max=1;
int m=LEN+1,n=LEN+2;
int fixed[LEN+1][LEN+2];
int clique[LEN+1][LEN+2];
int c0[4][LEN+1];
int cc0[LEN+1];
int c[target+1];
int arr[LEN+1];
int no=0;
int clen,c0len,cflen,cc0len,ccflen,calls,lit=0;

int select_Max_Var(int,int);
void Update_Deg();
void UpdateClique();
void residual_graph_Update(int *, int);

clock_t start; clock_t end;  clock_t dif;

int main(){
       int i,j,k,r;
    printf("\nCliques getting computed\n");
    for(i=1;i<m;i++) 
      {fixed[i][0]=i; fixed[0][i]=i; arr[i]=i;for(j=1;j<n;j++){ fixed[i][j]=0;clique[i][j]=0; }   }          
    FILE *f=fopen(FILENAME,"r");
    int integer1,integer2; 
    while(fscanf(f,"%d",&integer1)>0)
	    {fscanf(f,"%d",&integer2);
	      fixed[integer1][integer2]=1;
	      fixed[integer2][integer1]=1;
	      fixed[integer1][n-1]=fixed[integer1][n-1]+1;
	      fixed[integer2][n-1]=fixed[integer2][n-1]+1;
	     }
 // printf("\nFixed matrix......\n"); for(i=1;i<m;i++){ for(j=1;j<n;j++)printf("%d\t",fixed[i][j]); printf("\n");}
  int t;
  time_t ti; srand((unsigned) time(&ti));
  start=clock();
 for(i=1;i<LEN/10;i++){
    t=i; lit=0; calls=1;//1+rand()%LEN; //printf("\nt=%d\n",t);
    for(k=0;k<target/2;k++)
       { r= Greedy_Swap(t); calls++;
        if(r>Max) Max=r; 
        if(Max>=target) break;
     }if(Max>=target) break;}
    end=clock(); 
    dif=end-start;
     printf("\ntime in seconds is %.5f\t",(float)(dif)/CLOCKS_PER_SEC); 
     printf("Max clique=%d, # Iterations=%d & repetation ...\n",Max,no);
       
    getch();
   return 0;
   }
//..................................................................................
int Greedy_Swap(int k) {
    int i,j, cpos, it=0, x=1; if((target/10)>2) x=target/10; if(target/10>5) x=target/5;
    clen=1;cflen=0;ccflen=0;
	for(j=1;j<m;j++)
	 {if((fixed[k][j]==1)&&(clique[k][j]==0)) {c0[0][j]=j; ++cflen;} if(clique[k][j]>0){cc0[j]=j;++ccflen;}}
	 
	  for(i=0;i<=target;i++) c[i]=0;
    c[clen]=k; c0len=cflen; cc0len=ccflen;
    Update_Deg();
   //printf("\ncalled vertex k=%d\t\n",k);  for(i=1;i<m;i++) printf("\n%d\t%d\t%d\t%d\t%d\n",cc0[i],c0[0][i],c0[1][i], c0[2][i],c0[3][i]);
   
    while(cflen>0)
     { it++; lit++;//iteration++
       //if((clen+cflen)<=Max) return;
       i=select_Max_Var(it,x);
       if(c0[0][i]<=0) break; 
       c[++clen]=c0[0][i]; 
       if((it<0.25*target)&&(c0[1][i]<0.5*target)) {c0[1][i]=c0[1][i]+x; } //target/5 for MANN_45 
     
	  //if((c0[1][i]<0.25*target)) c0[1][i]=c0[1][i]+x;  else  
	 //if((c0[1][i]<0.8*target)) c0[1][i]=c0[1][i]+1; 
       c0[0][i]=-1;cflen--; cpos=clen; 
       residual_graph_Update(c,cpos);
        Update_Deg();
       no++; //printf("\n...............\n");for(i=1;i<m;i++) printf("\n%d\t%d\t%d\t%d\t%d\n",cc0[i],c0[0][i],c0[1][i], c0[2][i],c0[3][i]);
     }
     if((clen>Max)||(ccflen>0)) UpdateClique();
    end=clock(); 
    dif=end-start; 
  printf("\n vertex k:%d \t  cliques size(clen) :%d: Time %.6f # of iterations %d",k,clen,(float)(dif)/CLOCKS_PER_SEC, no);
// for(i=1;i<clen;i++)printf(" %d\t",c[i]);
   return clen;
  }
//...........................................................................
int select_Max_Var(int it,int x)//done//change
    {  int i,j,k,c0pos=0,c0max=0,flag=0,list[2][cflen], cc0avg=999;  
         
       //for(k=1;k<=c0len;k++){if((c0[0][k]>0)&&(cc0avg>c0[2][k])) cc0avg=c0[2][k]; }
      // printf("\nccflen=%d\n",ccflen);
	   for(k=1;k<m;k++){if(c0[0][k]>0){flag=1;c0pos=k;c0max=c0[2][k];break;}}
       if(flag==1)
         {for(j=k+1;j<m;j++)
           {if(c0[0][j]>0)
		     {if((c0[2][j]>c0max)&&(c0[1][j]<it)&&((c0[2][j]+c0[3][j])>(target-clen-2)))//(c0[2][j]>=ccflen)||(c0[3][j]>=ccflen)))	  
			  //if((c0[2][j]>c0max)&&((c0[1][j]<it)||((it<3)&&(c0[2][j]<lit))))
             //if((c0[2][j]>c0max)&&((c0[1][j]<it)||((it<0.25*target)&&(c0[2][j]<=(cc0avg+x)))))
		      
			 {c0pos=j;c0max=c0[2][j];}      
         }}}
    return c0pos;
    }
//...................................................................................  
 void residual_graph_Update(int *c, int cpos)//update c1len, cflen, m
  {  int i,j;
      for(i=1;i<m;i++)
        { if((c0[0][i]>0)&&( fixed[c[cpos]][c0[0][i]]==0)){ cflen=cflen-1; c0[0][i]=-1;}}
        
      for(i=1;i<m;i++)
        {if((cc0[i]>0)&&( fixed[c[cpos]][cc0[i]]==0)) {cc0[i]=-1;ccflen=ccflen-1;}}
    }     
  //................................................................................
 void Update_Deg( )
  {  int i,j;
     for(i=1;i<m;i++) {c0[2][i]=0; c0[3][i]=1;}
    
	 for(i=1;i<m;i++)
       { if(c0[0][i]>0)
	      {for(j=i+1;j<m;j++)
             { if(c0[0][j]>0)
                {if(fixed[c0[0][i]][c0[0][j]]==1)
                  { c0[2][i]=c0[2][i]+1;  c0[2][j]=c0[2][j]+1;} //degree w r t. c0 in c0
                }
		       if(cc0[j]>0)
                {if(fixed[c0[0][i]][cc0[j]]==1)
                   c0[3][i]=c0[3][i]+1;    //degree w r t. cc0 in c0
				  
			 }}}}
}
//..........................................................
void UpdateClique()
  { int i,j; 
     for(i=1;i<m;i++) {if(cc0[i]>0) c[++clen]=cc0[i];}
    
     //printf("\nCurrent Clique......\n");for(i=1;i<=clen;i++) printf("%d\t",c[i]); printf("\n clen=%d\t",clen);  printf("\n");
     for(i=1;i<=clen;i++)
        {for(j=1;j<n;j++) clique[c[i]][j]=0;}
	   	
	for(i=2;i<=clen;i++)
       { for(j=1;j<i;j++)
           {clique[c[i]][c[j]]=1;clique[c[j]][c[i]]=1; clique[c[i]][n-1]++;clique[c[j]][n-1]++;}      
     } 
	//printf("\nClique......\n"); for(i=1;i<m;i++){ for(j=1;j<n;j++)printf("%d\t",clique[i][j]); printf("\n");}
 }  

// The End........................................................................... 

