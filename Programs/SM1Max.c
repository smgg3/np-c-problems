// Greedy local search algorithm for finding maximum clique 
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define LEN 200
#define ed 0.16*LEN
//#define FILENAME "8.txt"
//#define FILENAME "69.txt"
//#define FILENAME "c-fat200-1.clq.txt"
//#define FILENAME "p_hat500-3.clq.txt"
//#define FILENAME "hamming8-4.clq.txt"
//#define FILENAME "johnson8-4-4.clq.txt"
//#define FILENAME "C125.9.clq.txt"
//#define FILENAME "gen200_p0.9_55.b.txt"
#define FILENAME "san200_0.7_2.clq.txt"
//#define FILENAME "sanr200_0.7.clq.txt"
//#define FILENAME "brock400_2.b.txt"
//#define FILENAME "r500.5.txt"
//#define FILENAME "MANN_a9.clq.b.txt" 
//#define FILENAME "killer4.clq.txt" 
 
int Max=0;
int target=18;
//int * calc_indept(int *,int ,int *);
int m=LEN+1,n=LEN+4;
int Q[LEN];
int Qlen;
int c[LEN];
int matrix[LEN+1][LEN+4];
void mdisplay();
int select_Max_Deg(int (*)[m], int );
int Greedy_Swap(int);
void Update_Deg(int (*)[m],int );
void insert ( int , int (*)[m], int *);
//void display(int *, int (*)[m],int (*)[m], int,int,int );
void residual_graph_Update(int *, int (*)[m],int *, int  ,int *,int );

int main(){
       int i,j,k;
       for(i=0;i<m;i++)for(j=0;j<n;j++){matrix[i][j]=0; }
       for(i=0;i<m;i++){ matrix[i][0]=i;}
       for(j=0;j<n;j++){ matrix[0][j]=j;} 
                                                       
       FILE *f=fopen(FILENAME,"r");
       int integer1,integer2;
       
   while(fscanf(f,"%d",&integer1)>0)
	    {fscanf(f,"%d",&integer2);
	      matrix[integer1][integer2]=1;
	      matrix[integer2][integer1]=1;
	      matrix[integer1][n-1]=matrix[integer1][n-1]+1;
	      matrix[integer2][n-1]=matrix[integer2][n-1]+1;
	     }
//printf("\n.........................\n");



    int r;
  time_t ti;srand((unsigned) time(&ti));
    clock_t start; clock_t end;  clock_t dif;
    start=clock();
  for(i=1;i<LEN;i++)
   { if(Max==target) break;
      int t=i;
       r= Greedy_Swap(t);
        if(r>Max) Max=r; 
     }
    end=clock(); 
    dif=end-start;
       printf("\ntime in seconds is %.5f\t",(float)(dif)/CLOCKS_PER_SEC); 
       printf("Max clique=%d\n",Max);
       getch();
   return 0;
   }
//..................................................................................
int Greedy_Swap(k) {
    int i,j,s,p;
    int c0[2][m],clen,cpos,c0len;
    c0len=clen=0; 
    for(i=0;i<m;i++) //initialization
      {c[i]=-1;c0[0][i]=-1; c0[1][i]=0;matrix[i+1][n-1]=1;}
      
    c[clen++]=k; // take kth vertex in clque list and disable it in matrix to be selected again
     for(i=1;i<m;i++){  if(matrix[i][k]==1){
                         c0[0][c0len++]=i; // populate adj(k) in c0 list
                     }   } 

   Update_Deg( c0,c0len);
    int cflen=c0len;

   while(cflen>0)
   {   //if((clen+cflen)<=Max) return;
       i=select_Max_Deg(c0,c0len);
       cpos=clen; c[clen++]=c0[0][i]; c0[0][i]=-1;c0[1][i]=0;cflen--;
       residual_graph_Update(c,c0,&c0len,cpos,&cflen,clen);
       //Update_Deg( c0,c0len);   
     
   }
  //printf("\n %d th vertex    Clique :%d  \n\n",k,clen);
   return clen;
}
  //...........................................................................

int select_Max_Deg(int (*c0)[m], int c0len)//done//change
    {
      int i,j,c0pos,c0max=0,sum=0,count=0;  
        int flag=0;
        
        for(i=0;i<c0len;i++)if(c0[0][i]>0){flag=1;c0pos=i;c0max=c0[1][i];break;} 
        if(flag==1)
        {   
            for(j=i+1;j<c0len;j++)
            {   if(c0[0][j]>0) {  if(c0max<c0[1][j]){ {c0pos=j;c0max=c0[1][j];} }       }
            }
         
      return c0pos;}
     //printf("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1");
   }
//...................................................................................  
 void residual_graph_Update(int *c, int (*c0)[m],int *c0len, int cpos,int *cflen,int clen)//update c1len, cflen, c0len
  {  int i,j,count=0;
  
    for(i=0;i<*c0len;i++)
        { //printf("\nPAIR:::  ( %d, %d )",i,*c0len);
         if(c0[0][i]>0)
            {  
              if( matrix[c[cpos]][c0[0][i]]==0 )
              {    *cflen=*cflen-1; 
                   c0[0][i]=-1;c0[1][i]=0;
              }
              else {c0[1][i]=c0[1][i]-1;}
            }  
     }   } 
    //................................................................................
 void Update_Deg(int (*c0)[m], int c0len)
  {   
   int i,j,k;
      for(i=0;i<c0len;i++) c0[1][i]=0;  
      for(i=0;i<c0len;i++)//updating c0 list
        {  for(j=i+1;j<c0len;j++)
             if(matrix[c0[0][i]][c0[0][j]]==1)
             { c0[1][i]=c0[1][i]+1;  c0[1][j]=c0[1][j]+1; }   
            
          } }
 //..............................................................................

// The End........................................................................... 

