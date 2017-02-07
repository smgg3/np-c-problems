#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define LEN 10
#define target 400

//#define FILENAME "8.txt"
#define FILENAME "txt10.txt"
//#define FILENAME "DAGS1.txt"
//#define FILENAME "c-fat500-5.clq.txt"
//#define FILENAME "p_hat1500-1.clq.txt"
//#define FILENAME "hamming6-4.clq.txt"
//#define FILENAME "johnson8-4-4.clq.txt"
//#define FILENAME "C125.9.clq.txt"
//#define FILENAME "gen400_p0.9_75.b.txt"
//#define FILENAME "san400_0.9_1.clq.txt"
//#define FILENAME "sanr400_0.7.clq.txt"
//#define FILENAME "brock800_2.b.txt"
//#define FILENAME "r500.5.txt"
//#define FILENAME "MANN_a45.clq.b.txt" 
//#define FILENAME "keller6.clq.txt" 
 

//time_t ti; srand((unsigned) time(&ti));
//clock_t start; clock_t end;  clock_t dif;
int m=LEN+1,n=LEN+2;
int  mxColor;
int matrix[LEN+1][LEN+2];  

int main(){
    int i,j,k,temp, nc,incr,count, countt,deg[m],tempmat[LEN+1][LEN+2], Ind[LEN]; 
    for(i=1;i<m;i++) { deg[i]=0; for(j=1;j<n;j++) {matrix[i][j]=0;tempmat[i][j]=0;} }	 
	        
    FILE *f=fopen(FILENAME,"r");
     
    while(fscanf(f,"%d",&i)>0)
	    { fscanf(f,"%d",&j);
	      matrix[i][j]=1; matrix[j][i]=1; deg[i]=deg[i]+1; deg[j]=deg[j]+1;tempmat[i][j]=1;tempmat[j][i]=1;
	    }
	    printf(" \n DegreeList:"); for(i=1;i<m;i++) printf("\t%d ", deg[i]);
 
	int nodeno=0,maxdeg=0;
	for(i=1;i<=LEN;i++){
		if(maxdeg<deg[i]){nodeno=i;maxdeg=deg[i];		}
	}
	if(maxdeg==0)nodeno=-1;
	while(nodeno>0)
	{mxColor++;
		deg[nodeno]=0;
		for(i=1;i<=LEN;i++)
		{
			if(tempmat[nodeno][i]==0){continue;
			}
			for(j=1;j<=LEN;j++)
			{
				if((tempmat[i][j]==0)||(i==nodeno)||(j==nodeno)||(deg[j]==0)){continue;				}
				if(tempmat[nodeno][j]!=1)
				{
					deg[j]=0;
					for(k=1;k<=LEN;k++)
					{
						if(tempmat[i][k]==1){tempmat[nodeno][k]=1;						}
						tempmat[j][k]=0;
					}
				}
			}
		}
		for(i=1;i<m;i++) {  for(j=1;j<n;j++) tempmat[i][j]=matrix[i][j]; }
		nodeno=0,maxdeg=0;
		for(i=1;i<=LEN;i++){
			if(maxdeg<deg[i]){nodeno=i;maxdeg=deg[i];		}
		}
		if(maxdeg==0)nodeno=-1;
		}
	
		printf("#colors : %d\n",mxColor);
    
    getch();
   return 0;
   }
//..................................................................................
//................................................................
//The End........................................................................... 

