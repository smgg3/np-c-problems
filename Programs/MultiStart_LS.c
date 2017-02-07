// Greedy local search algorithm for finding maximum clique 
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define LEN 400

//#define FILENAME "8.txt"
//#define FILENAME "txt10.txt"
//#define FILENAME "DAGS.txt"
//#define FILENAME "c-fat200-2.clq.txt"
//#define FILENAME "p_hat500-3.clq.txt"
//#define FILENAME "hamming8-4.clq.txt"
//#define FILENAME "johnson8-4-4.clq.txt"
//#define FILENAME "C125.9.clq.txt"
//#define FILENAME "gen200_p0.9_55.b.txt"
//#define FILENAME "san200_0.7_2.clq.txt"
//#define FILENAME "sanr200_0.7.clq.txt"
#define FILENAME "brock400_2.b.txt"
//#define FILENAME "r500.5.txt"
//#define FILENAME "MANN_a9.clq.b.txt" 
//#define FILENAME "killer4.clq.txt" 
 
int Max=0;
int target=29;
//time_t ti; srand((unsigned) time(&ti));
clock_t start; clock_t end;  clock_t dif;
int m=LEN+1,n=LEN+2;

int c0[LEN],c1[LEN],c[LEN]; // c0[] stores N(c) & c1[i] contains degree of vetex i in induced subgraph N(c) subtents at vertex i
char matrix[LEN+1][LEN+2];  //c[] is used to store clique vertices 
int  it[LEN]; // //MOV in MinOrdVertex,  it[] is to store # iteration/inclusion of a vertex in clique

int select_Max_Deg( int );
int Greedy_Swap(int);
void Update_Deg(int );
void residual_graph_Update( int *, int  ,int * ); // char *, int (*)[m],


int main(){
    int i,j,k,r,t,nv=0;
    for(i=1;i<m;i++) {it[i]=0;  for(j=1;j<n;j++) matrix[i][j]='0'; }	 //initializatin
	        
    FILE *f=fopen(FILENAME,"r");
     
    while(fscanf(f,"%d",&i)>0)
	    { fscanf(f,"%d",&j);
	      matrix[i][j]='1'; matrix[j][i]='1'; 
	    }
  printf("\n.clique is getting computed\n");
  start=clock();
  for(i=1;i<m;i++)
   {   if(Max>=target) break;
       t=i;
	   if(it[t]>0) continue;
       r= Greedy_Swap(t);
       if(r>Max) Max=r; 
        nv++;
     }
    end=clock(); 
    dif=end-start;
       printf("\n# vertices explored:%d \ttime spent %.5f\t",nv,(float)(dif)/CLOCKS_PER_SEC); 
       printf("Max clique=%d\n",Max);
       getch();
   return 0;
   }
//..................................................................................
int Greedy_Swap(k) {
    int i,j;
    int clen,cpos,c0len,cflen;
    c0len=1;clen=1; 
    for(i=1;i<m;i++){ c[i]=0; c0[i]=0; c1[i]=0; if(matrix[k][i]=='1'){c0[c0len++]=i; } } 
    
    c[clen++]=k; it[k]++; 
    Update_Deg(c0len);
    
	cflen=c0len;
    while(cflen>0)
     { if((clen+cflen)<=Max) return;
       i=select_Max_Deg(c0len);
       if(c0[i]<=0) break;
      // printf("\nvertex , Degree\n");   for(j=1;j<c0len;j++) printf("%d\t%d\n",c0[j],c1[j]);
       cpos=clen; c[clen++]=c0[i]; it[c0[i]]++; c0[i]=-1;c1[i]=0;cflen--;
       residual_graph_Update(&c0len,cpos,&cflen);
       Update_Deg(c0len);   
      
     } 
   end=clock();   dif=end-start; clen--; //for(i=1;i<clen+2;i++) printf("%d\t",c[i]);
   printf("\n vertex k:%d \t clen :%d  Time %.6f\n",k,clen,(float)(dif)/CLOCKS_PER_SEC);
   return clen;
}
  //...........................................................................

int select_Max_Deg(int c0len)//done//change
    {
      int i,j,c0pos,c0max=0,sum=0,count=0;  
        int flag=0;
        
        for(i=1;i<c0len;i++)if(c0[i]>0){flag=1;c0pos=i;c0max=c1[i];break;} 
        if(flag==1)
        {   
            for(j=i+1;j<c0len;j++)
            {   if(c0[j]>0) {  if(c0max<c1[j]){ {c0pos=j;c0max=c1[j];} } }
            }
         
      return c0pos;}
     //printf("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1");
   }
//...................................................................................  
 void residual_graph_Update(int *c0len, int cpos,int *cflen)//update c1len, cflen, c0len
  {  int i,j,count=0;
  
    for(i=1;i<*c0len;i++)
        { //printf("\nPAIR:::  ( %d, %d )",i,*c0len);
         if(c0[i]>0)
            {  
              if( matrix[c[cpos]][c0[i]]=='0' )
              {    *cflen=*cflen-1; 
                   c0[i]=0;c1[i]=0;
              }
             
            }  
     }   } 

 //..............................................................................
 void Update_Deg( int c0len) //
  {   
   int i,j,k,N[2][c0len];
      for(i=1;i<c0len;i++) {c1[i]=0; N[0][i]=0;N[1][i]=0;}
      for(i=1;i<c0len-1;i++)//updating c0 list
         { if(c0[i]>0)
		     {for(j=i+1;j<c0len;j++)
                {if(c0[j]>0)
			       {if(matrix[c0[i]][c0[j]]=='1')
                          { c1[i]=c1[i]+1;  c1[j]=c1[j]+1; }   
                }}}
          } }
 //...............................................................................

// The End........................................................................... 

