#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define LEN 10
#define target 10

//#define FILENAME "8.txt"
#define FILENAME "txt10.txt"
//#define FILENAME "DAGS1.txt"
//#define FILENAME "c-fat200-2.clq.txt"
//#define FILENAME "p_hat500-3.clq.txt"
//#define FILENAME "hamming8-4.clq.txt"
//#define FILENAME "johnson8-4-4.clq.txt"
//#define FILENAME "C125.9.clq.txt"
//#define FILENAME "gen200_p0.9_55.b.txt"
//#define FILENAME "san200_0.7_2.clq.txt"
//#define FILENAME "sanr200_0.7.clq.txt"
//#define FILENAME "brock200_1.b.txt"
//#define FILENAME "r500.5.txt"
//#define FILENAME "MANN_a9.clq.b.txt" 
//#define FILENAME "killer4.clq.txt" 
 

//time_t ti; srand((unsigned) time(&ti));
//clock_t start; clock_t end;  clock_t dif;
int m=LEN+1,n=LEN+2;
int  c2[LEN+1],co[LEN+1],mxColor;
int matrix[LEN+1][LEN+2];  //c[] is used to store clique vertices 
int is[LEN+1],size,M,eis[LEN*5],ts;
int newmat[LEN+1][LEN+2];

int main(){
    int i,j,k,temp, nc,incr,count, countt,deg[m], T1[m],T2[m], Ind[LEN]; // MOV : min ordered vertices
    for(i=1;i<m;i++) { T1[i]=i; deg[i]=0; for(j=1;j<n;j++) {newmat[i][j]=0;matrix[i][j]=0;} }	 //initializatin
	        
    FILE *f=fopen(FILENAME,"r");
     
    while(fscanf(f,"%d",&i)>0)
	    { fscanf(f,"%d",&j);
	      matrix[i][j]=1; matrix[j][i]=1; deg[i]=deg[i]+1; deg[j]=deg[j]+1;
	    }
	printf(" \n degreelist:"); for(i=1;i<m;i++) printf("\t%d ", deg[i]);
	
	
	int q=80,n=LEN,IM,iter=10,zmax,I,p;
	while(n>q)
	{
		IM=ATS(0,iter);
		zmax=size;
		int reapt=0,pmax=10,mmax=1,count=0;
		
		while(reapt<=pmax&&M<=mmax)
		{
			I=ATS(zmax,iter);k=1;
			for(i=1;i<=M;i++)
			{count=0;
				for(j=1;j<=size;j++)
				{int flag=0;
					for(p=k;p<=k+size;p++)
					{
						if((is[j]==eis[p])&&(eis[p]!=0))
						{	p=k+size;	flag=1;					}
						
						}
						if(!flag){j=size+1;for(p=1;p<=M;p++){if(eis[k]!=0)k++;else p=M+1;						}						}
						else
						count++;
					}
				}
				if(count==size)
				{ reapt=reapt+1;}
				else{
					eis[ts+1]=0;ts++;
				for(p=1;p<=size;p++)
				{
					eis[ts+p++]=is[p];
					}
					ts=ts+size;reapt=0;}
					
					}
					k=1;
		for(i=1;i<M;i++)
		{
			for(j=1;j<ts;j++)
			{
				for
				}
			}
		
		}
  
 
    getch();
   return 0;
   }
   int ATS(int z,int L)
   {
		int Ni=0;
		int S=
		}

