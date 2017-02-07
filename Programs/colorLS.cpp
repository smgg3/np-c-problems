// Greedy local search algorithm for finding maximum clique 
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define LEN 14
#define target 6
//#define ed 0.16*LEN
//#define FILENAME "txt10.txt"
#define FILENAME "DAGS.txt"
//#define FILENAME "frb40-19-1.clq"
//#define FILENAME "c-fat500-1.clq.txt"
//#define FILENAME "p_hat300-2.clq.txt"
//#define FILENAME "hamming8-2.clq.txt"
//#define FILENAME "johnson8-4-4.clq.txt"
//#define FILENAME "C1000.9.clq.txt"
//#define FILENAME "gen200_p0.9_44.b.txt"
//#define FILENAME "san200_0.9_2.clq.txt"
//#define FILENAME "sanr200_0.7.clq.txt"
//#define FILENAME "brock400_2.b.txt"
//#define FILENAME "r100.5.txt"
//#define FILENAME "MANN_a45.clq.b.txt" 
//#define FILENAME "keller4.clq.txt" 
 
int Max=1;
int m=LEN+1,n=LEN+2, Rv[LEN+1]; //Rv is # of repeatition of a vertex in forming clique
char fixed[LEN+1][LEN+2];
int c0[LEN],c1[LEN],c2[LEN]; //vertex list, its degree, & color

int select_Max_wt_vertex(int, int);
int FindMaxClique(int, int);
void Update_Deg(int);
void residual_graph_Update(int *, int  ,int *,int );
void colorvertex(int);
int Update_Deg_color(int, int, int *);
clock_t start; clock_t end;  clock_t dif;
//............................................................................................
int main(){
       int i,j,k;
    printf("\n Min ordered vertices\n");
    for(i=1;i<m;i++) {Rv[i]=0; for(j=1;j<n;j++) fixed[i][j]='0'; }	//fixed[i][0]=i;   fixed[0][i]=i;  }  //initializatin
	        
    FILE *f=fopen(FILENAME,"r");
    int integer1,integer2; 
    while(fscanf(f,"%d",&integer1)>0)
	    { fscanf(f,"%d",&integer2);
	      fixed[integer1][integer2]='1'; fixed[integer2][integer1]='1';
	      //fixed[integer1][n-1]=fixed[integer1][n-1]+1; fixed[integer2][n-1]=fixed[integer2][n-1]+1;
	     }
 
  int t, N,r;
  start=clock();
  
  for(i=1;i<LEN/2;i++)
   { if(Max>=target) break;
     if(Rv[i]>3) continue; 
	  t=i; N=1;
      for(j=1;j<m;j++) { if(fixed[t][j]=='1') {c0[N]=j; c1[N]=0; c2[N++]=0;} }//c0: adjacent vertices & c1: its degree
      
        r= FindMaxClique(t,N);
        if(r>Max) Max=r;     
	}
    end=clock();  dif=end-start; 
	printf("\n Max clique %d\t%.5f",Max, (float)(dif)/CLOCKS_PER_SEC);  
       
   // getch();
    return 0;
   }
//..................................................................................

int FindMaxClique(int k, int N) {
    int i,j,clen=1,it=0,c0len,cpos,mi=0,ma=0, maxColor; //maxColor is max # of different color on N(v)
    int cflen=N-1,c[N]; //for(i=0;i<=cflen;i++) c[i]=0; 
    c[clen]=k;  c0len=cflen; Rv[k]=Rv[k]+1;
    //printf("\ncalled vertex: %d\t",k); 
    colorvertex( N);
    maxColor=Update_Deg_color(clen, N,&cflen);
    
    //printf("\nvertex , Degree, Color\n");   for(i=1;i<N;i++) printf("%d\t%d\t%d\n",c0[i],c1[i],c2[i]);
   
    while(cflen>0)
     { //if((clen+cflen)<=Max) return 0;
       //if((clen+1+maxColor)<=Max) return 0;
        i=select_Max_wt_vertex(N, clen);
       if(c0[i]<=0) break; it++;
       c[++clen]=c0[i]; Rv[c0[i]]=Rv[c0[i]]+1; c0[i]=-1;cflen--; cpos=clen; c1[i]=-1;
         
        residual_graph_Update(c,cpos,&cflen,N);
        maxColor=Update_Deg_color(clen,N,&cflen);
       
     }
     end=clock();   dif=end-start; //for(i=1;i<=clen;i++) printf("\n%d\t%d\n",c[i],color[i]);
     printf("\n vertex k:%d \t clen :%d  Time %.6f\n",k,clen,(float)(dif)/CLOCKS_PER_SEC);

     return clen;
  }
//...........................................................................
int select_Max_wt_vertex(int N, int clen)//done//change
    { int i,j,k,c0pos=0,c0max=0,flag=0,temp,c1max;  
     
      for(k=0;k<N;k++){if(c0[k]>0){flag=1;c0pos=k;c0max=c1[k];break;}}
      c1max=Max-(clen+1+c1[k]);
      if(flag==1)
         { for(j=k+1;j<N;j++)
            { if((c0[j]>0)) 
               { //temp=Max-(clen+1+c1[j]); if((clen<target/5)&&(temp<=c1max)){c0pos=j;c1max=temp; }
			  //else 
			      if(c1[j]>c0max){c0pos=j;c0max=c1[j]; }   
          }}}
    return c0pos;
    }
//...................................................................................  
 void residual_graph_Update(int *c, int cpos,int *cflen,int N)//update c1len, cflen, m
  {  int i,j;
      for(i=1;i<N;i++)
        { if(c0[i]>0)
            {if( fixed[c[cpos]][c0[i]]=='0' )
              {    *cflen=*cflen-1; 
                   c0[i]=0; c1[i]=-1;
              }
      } }
	} 
     
  //................................................................................
 void Update_Deg(int N) 
  {  int i,j,k;
     for(i=1;i<N-1;i++)
        { if(c0[i]>0)
		   {for(j=i+1;j<N;j++)
		     if(c0[j]>0)
              {if(fixed[c0[i]][c0[j]]=='1') { c1[i]=c1[i]+1;  c1[j]=c1[j]+1;}} 
        }  } 
  
  }
// ...........................................................................
int Update_Deg_color(int clen, int N, int *cflen)
 {int i,j,k,p, co[N], maxColor=0;
      
     for(i=1;i<N;i++)
        { if(c0[i]>0)
		   {c1[i]=0;
		    for(p=1;p<N;p++) co[p]=0; //initialize color list to store all different colors
		    for(j=1;j<N;j++)
		     {if(c0[j]>0)
                {if((co[c2[j]]==0)&&(fixed[c0[i]][c0[j]]=='1')) {co[c2[j]]=1; c1[i]=c1[i]+1;}} 
             } 
           // if((clen+1+c1[i])<Max) {c0[i]=0; *cflen=*cflen-1; } 
            if(c1[i]>maxColor) maxColor=c1[i]; 
		   }
	    }
    // printf("\n updated vertex , Degree, Color...\n");  for(i=1;i<N;i++) printf("%d\t%d\t%d\n",c0[i],c1[i],c2[i]); 
     return maxColor;
  }


//...............................................................................
 void colorvertex( int N)
 { int i,j,k,min,p, temp, T1[N],T2[N], co[N],L[N]; // contains Vertex, degree, color  & L[] vertex index in c0[] in min deg ordered
   
    Update_Deg(N);
  
    for(i=1;i<N;i++){ T1[i]=c0[i];T2[i]=c1[i]; }// initialization
  //min ordering.
  j=1;
  temp=9999;  for(i=1;i<N;i++) {if((T1[i]>0)&&(T2[i]<temp)) {min=i; temp=T2[i];}}
  
  while(j<N)
   {  L[j]=min; T1[min]=0; temp=9999;
      for(i=1;i<N;i++)
          { if(T1[i]>0)
		      {if(fixed[T1[L[j]]][T1[i]]=='1')  T2[i]=T2[i]-1;
		       if(T2[i]<temp) {min=i; temp=T2[i];}
		   }  }   
      j++; 
   } //printf(" \n min ordered list: "); for(i=1;i<N;i++) printf("\t%d ", c0[L[i]]);
  //Coloring vertices in c2[],  
  c2[L[N-1]]=1; 
  for(i=N-2;i>0;i--)      
      { j=i+1;  for(p=1;p<N;p++) co[p]=0;
       while(j<N) 
         { if(fixed[c0[L[i]]][c0[L[j]]]=='1')
                co[c2[L[j]]]=1; //printf("%d\t",c[T1lor[1][minOrd[j]]]);
         j++; 
         }
     k=1;
	 while((co[k]>0)&&(k<N)) k++; 
     c2[L[i]]=k;
      }
}

// The End........................................................................... 

