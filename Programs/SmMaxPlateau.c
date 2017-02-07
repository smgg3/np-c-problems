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

int it[LEN+1], deg[LEN+1],c0[LEN],c1[LEN],c[LEN]; // c0[] stores N(c) & c1[i] contains degree of vetex i in induced subgraph N(c) subtents at vertex i
char matrix[LEN+1][LEN+2];  //c[] is used to store clique vertices 

int select_Max_Deg( int );
int Greedy_Swap(int);
void Update_Deg(int );
void residual_graph_Update( int *, int  ,int * ); // char *, int (*)[m],
void plateau(int *);

int main(){
       int i,j,k,r;
       for(i=1;i<m;i++) {it[i]=0; deg[i]=0; for(j=1;j<n;j++) matrix[i][j]='0'; }	  //initializatin
	        
    FILE *f=fopen(FILENAME,"r");
     
    while(fscanf(f,"%d",&i)>0)
	    { fscanf(f,"%d",&j);
	      matrix[i][j]='1'; matrix[j][i]='1'; //deg[i]=deg[i]+1; deg[j]=deg[j]+1;
	    }
printf("\n.clique is getting computed\n");
  start=clock();
  //for(i=1;i<LEN;i++)
   { //if(Max>=target) break;
     //if(it[i]>1) continue;
      int t=5;
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
       printf("\nvertex , Degree\n");   for(j=1;j<c0len;j++) printf("%d\t%d\n",c0[j],c1[j]);
       cpos=clen; c[clen++]=c0[i]; it[c0[i]]++; c0[i]=-1;c1[i]=0;cflen--;
       residual_graph_Update(&c0len,cpos,&cflen);
       Update_Deg( c0len);   
     
     }
   plateau(&clen); 
    end=clock();   dif=end-start; clen--; for(i=1;i<=clen;i++) printf("%d\t",c[i]);
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
    //................................................................................
  void Update_Deg( int c0len)
  {   
   int i,j,k;
      for(i=1;i<c0len;i++) c1[i]=0;  
      for(i=1;i<c0len-1;i++)//updating c0 list
         { if(c0[i]>0)
		     {for(j=i+1;j<c0len;j++)
                {if(c0[j]>0)
			       {if(matrix[c0[i]][c0[j]]=='1')
                          { c1[i]=c1[i]+1;  c1[j]=c1[j]+1; }   
                }}}
          } }
 //..............................................................................
void plateau(int *clen)
{ int i,j,k,t1,t2,flag,c0len,cc0len,N1[LEN],N11[LEN],N2[LEN], N22[LEN],N222[LEN];
  int index1=1,index2=1;
  char cc[LEN]; c0len=1;cc0len=1;
  printf("\n...plateau starts...\n");
  for(i=1;i<m;i++) 
      { k=0;flag=0;
	    for(j=1;j<*clen;j++)
         {if((i!=c[j])&&(matrix[i][c[j]]=='0')) {flag++; t2=t1; t1=j;}
			 else k++;
			 if(flag>2) break;
			}
         if(k==(*clen-2)) {N1[c0len]=i; N11[c0len++]=t1;}// save t1
         else if(k==(*clen-3)) {N2[cc0len]=i; N22[cc0len]=t1; N222[cc0len++]=t2;} // save t1 & t2
     }
        
    k=((c0len>cc0len)?c0len:cc0len); 
	int N111[k],N1111[k],N2222[k];
	for(i=1;i<k;i++){  N111[i]=0;N1111[i]=0;N2222[i]=0;} //initialization
    
    for(i=1;i<c0len;i++) 
        { for(j=i+1;j<c0len;j++) 
             if((N11[i]==N11[j])&&(matrix[N1[i]][N1[j]]=='1')) {N111[i]++; N111[j]++; }
        
          for(j=1;j<cc0len;j++) 
              if(((N11[i]==N22[j])||(N11[i]==N222[j]))&&(matrix[N1[i]][N2[j]]=='1')) N1111[i]++;
       }
    t1=N111[1]; 
	for(i=1;i<c0len;i++) 
	  { if((N111[i]>t1)||((N111[i]==t1)&&(N1111[i]>N1111[index1]))) {t1=N111[i]; index1=i;} 
        printf("..%d\t%d\t%d\t%d\n",N1[i],c[N11[i]],N111[i],N111[i]);
	  }
    
    for(i=1;i<cc0len-1;i++) 
       { for(j=i+1;j<cc0len;j++) if((N22[i]==N22[j])&&(N222[i]==N222[j])&&(matrix[N2[i]][N2[j]]=='1')){N2222[i]++; N2222[j]++;}}
   
    t2=N2222[1];
	for(i=1;i<cc0len;i++)
	   { if(N2222[i]>t2) {t2=N2222[i];index2=i;} printf("....%d\t%d\t%d\t%d\n",N2[i],c[N22[i]],c[N222[i]],N2222[i]); } 
	if(t1>t2+1) 
	  { c[N11[index1]]=N1[index1];
	     for(j=index1+1;j<c0len;j++) 
             if((N11[index1]==N11[j])&&(matrix[N1[index1]][N1[j]]=='1')) {c[(*clen)++]=N1[j]; N1[j]=0;N111[j]=0;}
	  
	  }  
	 else
	  { c[N22[index2]]=N2[index2]; 
	     for(j=index2+1;j<cc0len;j++) 
            {if((N22[index2]==N22[j])&&(N222[index2]==N222[j])&&(matrix[N2[index2]][N2[j]]=='1'))
			  {c[(*clen)++]=N2[j]; N2[j]=0;N2222[j]=0;}
		    }
	    c[N222[index2]]=c[--(*clen)];
	  }
	// return k;  
}

  

	
	




// The End........................................................................... 

