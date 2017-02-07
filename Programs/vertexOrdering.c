// Greedy local search algorithm for finding maximum clique 
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define LEN 11
#define target 40
//#define ed 0.16*LEN
//#define FILENAME "txt10.txt"
#define FILENAME "11.txt"
//#define FILENAME "frb40-19-1.clq"
//#define FILENAME "c-fat200-5.clq.txt"
//#define FILENAME "p_hat500-3.clq.txt"
//#define FILENAME "hamming8-2.clq.txt"
//#define FILENAME "johnson8-4-4.clq.txt"
//#define FILENAME "C500.9.clq.txt"
//#define FILENAME "gen200_p0.9_55.b.txt"
//#define FILENAME "san400_0.5_1.clq.txt"
//#define FILENAME "sanr200_0.9.clq.txt"
//#define FILENAME "brock400_4.b.txt"
//#define FILENAME "r100.5.txt"
//#define FILENAME "MANN_a27.clq.b.txt" 
//#define FILENAME "keller4.clq.txt" 
 
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
      {fixed[i][0]=i; fixed[0][i]=i;color[0][i]=i;color[1][i]=0;
       for(j=1;j<n;j++) fixed[i][j]=0;   }          
    FILE *f=fopen(FILENAME,"r");
    int integer1,integer2; 
    while(fscanf(f,"%d",&integer1)>0)
	    {fscanf(f,"%d",&integer2);
	      fixed[integer1][integer2]=1; fixed[integer2][integer1]=1;
	      fixed[integer1][n-1]=fixed[integer1][n-1]+1; fixed[integer2][n-1]=fixed[integer2][n-1]+1;
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
 
   printf("\nvertices after doing sorting are \n");
   for(i=1;i<=LEN;i++){udv[2][i]=udv[0][i];udv[3][i]=udv[1][i]; printf("%d\t%d\n",udv[0][i], udv[1][i]);}
    
 // min ordering
 k=1;  printf("\n min\tmm\t Deg_mm\t i=\tDeg_i vertices\n");
 int min=1,rv,mm; //rv=removed vertex
 while(k<=LEN)
  { minOrd[k++]=udv[0][min]; rv=udv[0][min]; udv[0][min]=0; udv[1][min]=0;
    j=0; while((udv[0][++j]==0)&&(j<m))continue; mm=j;  printf("\n..%d\t%d\t%d...\n",rv,udv[0][mm],udv[1][mm]);
    for(i=j;i<=LEN;i++) 
	  {if((udv[0][i]>0)&&(fixed[rv][udv[0][i]]==1)) 
	     { udv[1][i]=udv[1][i]-1; // printf("%d\t%d\n",udv[0][i],udv[1][i]);
	       if((udv[1][i]<udv[1][mm])||(((udv[1][i]==udv[1][mm])&&(udv[3][i]<udv[3][mm])))) mm=i;
	     }
       }
     min=mm;
  }
      printf("\n Min order is : \n"); for(i=1;i<=LEN;i++)	{printf("%d\t",minOrd[i]);}
 //coloring of vertices 
 int c[2*target];color[1][minOrd[LEN]]=1;
 for(i=LEN-1;i>0;i--)
   { for(j=1;j<2*target;j++)c[j]=0;
     j=i+1;
     while(j<=LEN) 
       { if(fixed[minOrd[i]][minOrd[j]]==1)
                c[color[1][minOrd[j]]]=color[1][minOrd[j]];// printf("%d\t",c[color[1][minOrd[j]]]);
         j++; 
       }
       printf("\n");
     k=1; while((c[k]>0)&&(k<2*target)) k++; 
     color[1][minOrd[i]]=k;
   }
  k=1;
 
  for(i=1;i<=LEN;i++) 
    if( color[1][i]>k)k=color[1][i];
 printf("\n Max color=%d \n",k);
   
     
     
       
    getch();
   return 0;
   }
//..................................................................................

// The End........................................................................... 

