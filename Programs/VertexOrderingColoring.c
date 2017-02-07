// Greedy local search algorithm for finding maximum clique 
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define LEN 11
#define target 15
//#define ed 0.16*LEN
//#define FILENAME "txt10.txt"
#define FILENAME "11.txt"
//#define FILENAME "frb40-19-1.clq"
//#define FILENAME "c-fat200-2.clq.txt"
//#define FILENAME "p_hat300-2.clq.txt"
//#define FILENAME "hamming8-2.clq.txt"
//#define FILENAME "johnson8-4-4.clq.txt"
//#define FILENAME "C500.9.clq.txt"
//#define FILENAME "gen200_p0.9_55.b.txt"
//#define FILENAME "san400_0.7_1.clq.txt"
//#define FILENAME "sanr200_0.9.clq.txt"
//#define FILENAME "brock200_3.b.txt"
//#define FILENAME "r100.5.txt"
//#define FILENAME "MANN_a27.clq.b.txt" 
//#define FILENAME "keller4.clq.txt" 
 
int Max=1;
int m=LEN+1,n=LEN+2;
int fixed[LEN+1][LEN+2];
int udv[4][LEN+1]; //udv: updatedDegreeVertex
int color[2][LEN+1],clr;
int minOrd[LEN+1];
int c0[LEN+1], list[LEN];
int c1[LEN+1];
int co[LEN], cl; //# of colors//color
int select_Max_Var(int *,int ,int,int);
int FindMaxClique(int);
void Update_Deg(int, int);
void residual_graph_Update(int *, int  ,int *,int );
float mxdeg(int ,int (*)[m],int ,int );
clock_t start; clock_t end;  clock_t dif;
//............................................................................................
int main(){
       int i,j,k,temp,r;
    printf("\n Min ordered vertices\n");
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
 k=1; // printf("\n min\tmm\t Deg_mm\t i=\tDeg_i vertices\n");
 int min=1,rv,mm; //rv=removed vertex
 while(k<=LEN)
  { minOrd[k++]=udv[0][min]; rv=udv[0][min]; udv[0][min]=0; udv[1][min]=0;
    j=0; while((udv[0][++j]==0)&&(j<m))continue; mm=j; // printf("\n..%d\t%d\t%d...\n",rv,udv[0][mm],udv[1][mm]);
    for(i=j;i<=LEN;i++) 
	  {if((udv[0][i]>0)&&(fixed[rv][udv[0][i]]==1)) 
	     { udv[1][i]=udv[1][i]-1; // printf("%d\t%d\n",udv[0][i],udv[1][i]);
	       if((udv[1][i]<udv[1][mm])||(((udv[1][i]==udv[1][mm])&&(udv[3][i]<udv[3][mm])))) mm=i;
	     }
       }
     min=mm;
  }
     // printf("\n Min order is : \n"); for(i=1;i<=LEN;i++)	{printf("%d\t",minOrd[i]);}
 //coloring of vertices 
 int nc=3*target,c[nc];color[1][minOrd[LEN]]=1;
 for(i=LEN-1;i>0;i--)
   { for(j=1;j<nc;j++)c[j]=0;
     j=i+1;
     while(j<=LEN) 
       { if(fixed[minOrd[i]][minOrd[j]]==1)
                c[color[1][minOrd[j]]]=color[1][minOrd[j]]; printf("%d\t",c[color[1][minOrd[j]]]);
         j++; 
       }
     k=1; while((c[k]>0)&&(k<nc)) k++; 
     color[1][minOrd[i]]=k;
   }
  k=1; j=1;
 
  for(i=1;i<=LEN;i++) 
   { if(color[1][i]>k) k=color[1][i];  
	 if((color[1][i]>=target)) list[j++]=color[0][i];
  }
		 printf("\n Max color=%d \n",k);
  /*cl=k; //# of colors
 
  start=clock();
  for(i=1;i<j;i++)
   { if(Max>=target) break;
      int t=list[i];  if(t==0) continue;
      for(j=1;j<m;j++) {c0[j]=0;c1[j]=0;  if(fixed[t][j]==1) c0[j]=j; } //c0: adjacent vertices & c1: its degree
      
        r= FindMaxClique(t);
        if(r>Max) Max=r;     
	  }
      end=clock();  dif=end-start; 
	  printf("\n Max clique %d\t%.5f",Max, (float)(dif)/CLOCKS_PER_SEC);  
    */   
    getch();
   return 0;
   }
//..................................................................................
//..................................................................................
int FindMaxClique(int k) {
    int i,j,clen=1,it=0,c0len,cpos,mi=0,ma=0; 
    int cflen=fixed[k][n-1],c[cflen+1],ccolor[cflen+1]; for(i=0;i<=cflen;i++) {c[i]=0; ccolor[i]=0;}
    c[clen]=k; ccolor[clen]=color[1][k]; c0len=cflen; 
    Update_Deg(clen, cflen);
  // printf("\ncalled vertex k=%d\n",k);
   //for(i=1;i<m;i++) printf("\n%d\t%f\t%f\n",c0[i],cc0[0][i],cc0[1][i]);
   
  while(cflen>0)
     { if((clen+cflen)<=Max) return;
        i=select_Max_Var(ccolor, cflen,c0len,clen);
       if(c0[i]<=0) break; it++;
       c[++clen]=c0[i]; ccolor[clen]=color[1][c0[i]]; c0[i]=-1;cflen--; cpos=clen; 
         
       residual_graph_Update(c,cpos,&cflen,clen);
        Update_Deg(clen, cflen);
       
     }
     end=clock();   dif=end-start; for(i=1;i<=clen;i++) printf("\n%d\t%d\n",c[i],ccolor[i]);
  printf("\n vertex k:%d \t clen :%d  Time %.6f\n",k,clen,(float)(dif)/CLOCKS_PER_SEC);

   return clen;
  }
//...........................................................................
int select_Max_Var(int *ccolor, int cflen,int c0len, int clen)//done//change
    { int i,j,k,c0pos=0,c0max=0,flag=0;  
     
      for(k=0;k<m;k++){if(c0[k]>0){flag=1;c0pos=k;c0max=c1[k];break;}}
      if(flag==1)
         { for(j=k+1;j<m;j++)
            { if((c0[j]>0)) //if((c0[j]>0) &&(ccolor[c0[j]]==0))
               if(c1[j]>c0max){c0pos=j;c0max=c1[j]; }   
          }}
    return c0pos;
    }
//...................................................................................  
 void residual_graph_Update(int *c, int cpos,int *cflen,int clen)//update c1len, cflen, m
  {  int i,j,count=0;
      for(i=1;i<m;i++)
        { if(c0[i]>0)
            {if( fixed[c[cpos]][c0[i]]==0 )
              {    *cflen=*cflen-1; 
                   c0[i]=0;
              }
      } }}    
  //................................................................................
 void Update_Deg(int clen, int cflen )
  {  int i,j,k,d=0; //*mi=0;*ma=0;
     for(i=1;i<m;i++) c1[i]=0;
     for(i=1;i<m-1;i++)
        { if(c0[i]>0)
           { for(k=1;k<=cl;k++) co[k]=0; //make empty list to collect distinct colors
		    for(j=1;j<m;j++)
             { if(c0[j]>0)
                {if(fixed[c0[i]][c0[j]]==1)
                  { if(co[color[1][c0[j]]]==0) {d++; co[color[1][c0[j]]]=1;}} 
        } }c1[i]=d-1; }}  
}
// The End...........................................................................
// The End........................................................................... 

