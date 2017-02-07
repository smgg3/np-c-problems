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

int c0[LEN],c1[LEN],c[LEN],deg[LEN+1]; // c0[] stores N(c) & c1[i] contains degree of vetex i in induced subgraph N(c) subtents at vertex i
char matrix[LEN+1][LEN+2];  //c[] is used to store clique vertices 
int MOV[LEN+1],Ind[LEN],Id,it[LEN]; // //MOV in MinOrdVertex,  it[] is to store # iteration/inclusion of a vertex in clique

int select_Max_Deg( int );    //I # vertices in independent set
int Max_Clique(int ,int);
void Update_Deg(int );
void residual_graph_Update( int *, int  ,int * ); // char *, int (*)[m],
void MinOrdVertex();
 

int main(){
    int i,j,k,r,t,nv=0;
    for(i=1;i<m;i++) {it[i]=0;  for(j=1;j<n;j++) matrix[i][j]='0'; }	 //initializatin
	        
    FILE *f=fopen(FILENAME,"r");
     
    while(fscanf(f,"%d",&i)>0)
	    { fscanf(f,"%d",&j);
	      matrix[i][j]='1'; matrix[j][i]='1'; deg[i]=deg[i]+1; deg[j]=deg[j]+1;
	    }
  printf("\n.clique is getting computed\n");
  MinOrdVertex();
  
  start=clock();
  for(i=1;i<m;i++)
   {   if(Max>=target) break;
       t=MOV[i];
	   if((MOV[i]==0)||(it[t]>0)) continue;
       r= Max_Clique(t,i);
        if(r>Max) Max=r; 
        nv++;
     }
    end=clock(); 
    dif=end-start;
       printf("\n# vertices explored=%d\ttime spent %.5f\t",nv,(float)(dif)/CLOCKS_PER_SEC); 
       printf("Max clique=%d\n",Max);
       getch();
   return 0;
   }
//..................................................................................
int Max_Clique( k, loc) {
    int i,j,flag=0;  //rec is iteration of while loop
    int clen,cpos,c0len,cflen;
    c0len=1;clen=1; 
    for(i=1;i<m;i++){ c[i]=0; c0[i]=0; c1[i]=0; if((MOV[i]>0)&&(matrix[k][MOV[i]]=='1')){c0[c0len++]=MOV[i]; } } 
    
    c[clen++]=k; it[k]=it[k]+1; 
    Update_Deg(c0len);
    
	cflen=c0len;
    while(cflen>0)
     { if((clen+cflen)<=Max) return;
       i=select_Max_Deg(c0len);
       if(c0[i]<=0) break;
       //printf("\nvertex:%d , Degree...\n",k);   for(j=1;j<c0len;j++) printf("%d\t%d\n",c0[j],c1[j]);
       cpos=clen; c[clen++]=c0[i]; it[c0[i]]=it[c0[i]]+1; c0[i]=-1;c1[i]=0;cflen--; 
      
       residual_graph_Update(&c0len,cpos,&cflen);
       Update_Deg(c0len);   
     } 
     // check independent set to include an additional vertex in c[]
    //printf(" \n Ind set : "); for(i=1;i<Id;i++) printf("\t%d ", Ind[i]);
    for(i=1;i<Id;i++)
      { for(j=1;j<clen;j++)
	     {if(matrix[Ind[i]][c[j]]=='0') break;}
	   if(j==clen) {c[clen++]=Ind[i]; break;} 
      }
      
   end=clock();   dif=end-start; clen; //for(i=1;i<clen;i++) printf("\n%d",c[i]);
   printf("\n vertex k:%d \t clen :%d  Time %.6f\n",k,clen-1,(float)(dif)/CLOCKS_PER_SEC);
   return clen-1;
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
  }    }   }
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
 void MinOrdVertex()
 { int i,j,k,min,p, temp, T1[m],T2[m]; // contains Vertex, degree, color  & L[] vertex index in c0[] in min deg ordered
   temp=LEN; j=1; k=1;
   for(i=1;i<m;i++){ T1[i]=i;T2[i]=deg[i]; if(T2[i]<temp) {min=i; temp=T2[i];}}// find first min deg vertex
   
   while(j<m)
    { MOV[j]=min; T1[min]=0;  //MOV in MinOrdVertex
      temp=LEN;
      for(i=1;i<m;i++)
          { if(T1[i]>0)
		      {if(matrix[MOV[j]][i]=='1')  T2[i]=T2[i]-1;
		       //if(T2[i]<temp) {min=i; temp=T2[i];}
		       if((T2[i]<temp)||((T2[i]==temp)&&(deg[i]>temp))) {min=i; temp=T2[i];}
		   }  }   
      j++; 
   } 
//remove Ind set vertices from MOV.........................................................

    k=1;Ind[k++]=MOV[1]; MOV[1]=0;
	for(i=2;i<m;i++)
      { for(j=1;j<k;j++) 
	     {if(matrix[MOV[i]][Ind[j]]=='1')  break;}
       if(j==k) { Ind[k++]=MOV[i]; MOV[i]=0;}
      }  
     Id=k; 
//printf(" \n min ordered list: "); for(i=1;i<m;i++) printf("\t%d ", MOV[i]);
}
//........................................................................................
   
// ............................................................................
/* void updatec0(int *c, int clen,int loc,int *c0len,int *cflen)
  { int i,j,k=1;
     for(i=1;i<loc;i++)
       { for(j=1;j<clen;j++) {if(matrix[MOV[i]][c[j]]=='0') break;}
             
			if(j==clen)    
			  {while(k<*c0len) 
				  { if(c0[k]==0) break; k++;}
               c0[k++]=MOV[i]; *cflen=*cflen+1;	
              }
	    }
       *c0len=k;      
  }  */

//The End........................................................................... 

