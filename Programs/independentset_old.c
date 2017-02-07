// Greedy local search algorithm for finding maximum clique 
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define LEN 171	
#define target 200
//#define ed 0.16*LEN
//#define FILENAME "txt10.txt"
//#define FILENAME "8.txt"
//#define FILENAME "frb40-19-1.clq"
//#define FILENAME "c-fat500-1.clq.txt"
//#define FILENAME "p_hat300-1.clq.txt"
//#define FILENAME "hamming6-2.clq.txt"
//#define FILENAME "johnson16-2-4.clq.txt"
//#define FILENAME "C500.9.clq.txt"
//#define FILENAME "gen200_p0.9_44.b.txt"
//#define FILENAME "san400_0.5_1.clq.txt"
//#define FILENAME "sanr200_0.7.clq.txt"
//#define FILENAME "brock400_1.b.txt"
//#define FILENAME "r100.5.txt"
//#define FILENAME "MANN_a9.clq.b.txt" 
#define FILENAME "keller4.clq.txt" 
 
int Max=1;
int m=LEN+1,n=LEN+2;
int fixed[LEN+1][LEN+2];
int udv[4][LEN+1]; //udv: updatedDegreeVertex
int color[2][LEN+1],clr;
int minOrd[LEN+1];

int main(){
       int i,j,k,temp;
    printf("\nMin ordered vertices\n");
    for(i=1;i<m;i++) 
      {fixed[i][0]=i; fixed[0][i]=i; 
	   for(j=1;j<m;j++) fixed[i][j]=1; fixed[i][i]=0; fixed[i][n-1]=LEN-1; }          
    FILE *f=fopen(FILENAME,"r");
    int integer1,integer2; 
    while(fscanf(f,"%d",&integer1)>0)
	    {fscanf(f,"%d",&integer2);
	      fixed[integer1][integer2]=0; fixed[integer2][integer1]=0;
	      fixed[integer1][n-1]--; fixed[integer2][n-1]--;
	     }
 
    //sorting (insertion sort, according to max degree degree first
    for(i=1;i<m;i++)
        { udv[0][i]=i; udv[1][i]=fixed[i][n-1]; }
    for(i=2;i<=LEN;i++)
		 { temp=udv[1][i]; j=i-1;
           while((j>0)&&(udv[1][j]>temp))
		      { udv[0][j+1]=udv[0][j];udv[1][j+1]=udv[1][j]; j--;}
		   udv[0][j+1]=i;udv[1][j+1]=temp;                     
		}
 
 // min ordering
 for(i=1;i<m;i++) {udv[2][i]=i; udv[3][udv[0][i]]=udv[1][i];}
 k=1; // printf("\n min\tmm\t Deg_mm\t i=\tDeg_i vertices\n");
 int min=1,rv,mm; //rv=removed vertex
 while(k<=LEN)
  { minOrd[k++]=udv[0][min]; rv=udv[0][min]; udv[0][min]=0; udv[1][min]=0;
    j=0; while((udv[0][++j]==0)&&(j<m))continue; mm=j; // printf("\n..%d\t%d\t%d...\n",rv,udv[0][mm],udv[1][mm]);
    for(i=j;i<=LEN;i++) 
	  {if((udv[0][i]>0)&&(fixed[rv][udv[0][i]]==1)) 
	     {  udv[1][i]=udv[1][i]-1; // printf("%d\t%d\n",udv[0][i],udv[1][i]);
	       if((udv[1][i]<udv[1][mm])||(((udv[1][i]==udv[1][mm])&&(udv[3][i]<udv[3][mm])))) mm=i;
	     }
       }
     min=mm;
  }
      printf("\n Min order is : \n"); for(i=1;i<=LEN;i++)	{printf("%d\t%d\t%d\n",minOrd[i],udv[2][i],udv[3][i]);}
 //independent set of vertices 
 int ind[LEN+1],l=1,p=1;
while((p==1)||(udv[3][minOrd[l+1]]==udv[3][minOrd[l]])){
   ind[1]=minOrd[l];
   p=0;k=1;
 for(i=1;i<m;i++)
   { for(j=1;j<=k;j++)
		{if((fixed[ind[j]][minOrd[i]]==1))break;}
		
		if((j==k+1))ind[++k]=minOrd[i];
		
	}
 printf("\n independent set \n");	
   
    printf("%d\t",k);
l++;} 
     
     
       
    getch();
   return 0;
   }
//..................................................................................

// The End........................................................................... 

