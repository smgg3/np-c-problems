// Greedy local search algorithm for finding maximum clique 
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define LEN 400   
#define ed 0.7
#define target 27 //max clique size

//#define FILENAME "txt10.txt"
//#define FILENAME "ll.txt"
//#define FILENAME "c-fat500-5.clq.txt"
//#define FILENAME "p_hat700-3.clq.txt"
//#define FILENAME "hamming8-2.clq.txt"
//#define FILENAME "johnson32-2-4.clq.txt"
//#define FILENAME "C1000.9.clq.txt"
//#define FILENAME "gen400_p0.9_55.b.txt"
//#define FILENAME "san200_0.7_2.clq.txt"
//#define FILENAME "sanr200_0.9.clq.txt"
#define FILENAME "brock400_1.b.txt"
//#define FILENAME "r400.5.txt"
//#define FILENAME "MANN_a45.clq.b.txt" 
//#define FILENAME "keller6.clq.txt" 

clock_t start; clock_t end;  clock_t dif; clock_t diff;
int Max=1;
int m=LEN+1,n=LEN+2;
int fixed[LEN+1][LEN+2];
int Q[2][LEN];
int independent[LEN];
int list[LEN];
int no=0;
int select_Min_Var(int (*)[m], int,int,int,int );
int Greedy_Swap(int);
void Update_Deg(int (*)[m],int, int,int *);
void residual_graph_Update(int *, int (*)[m],int *, int  ,int *,int );
int mxdeg(int ,int (*)[m],int,int,int,int);
int ind_set(int *,int );
int main(){
       int i,j,k;
printf("\nCliques getting computed\n");
    for(i=1;i<m;i++) {fixed[i][0]=i; fixed[0][i]=i;Q[0][i]=i;Q[1][i]=0; for(j=1;j<n;j++) fixed[i][j]=0; }             
       FILE *f=fopen(FILENAME,"r");
       int integer1,integer2; 
   while(fscanf(f,"%d",&integer1)>0)
	    {fscanf(f,"%d",&integer2);
	      fixed[integer1][integer2]=1;
	      fixed[integer2][integer1]=1;
	      fixed[integer1][n-1]=fixed[integer1][n-1]+1;
	      fixed[integer2][n-1]=fixed[integer2][n-1]+1;
	     }
  //sorting nim deg first
    for(i=1;i<=LEN;i++) list[i-1]=i;
    int big,loc,dum;
   	for(i=1;i<LEN;i++){ 
       big=fixed[list[i]][n-1];loc=i;
       for(j=i+1;j<LEN;j++)
        { if(fixed[list[j]][n-1]<big){big=fixed[list[j]][n-1];loc=j;}}
       dum=list[i]; list[i]=list[loc];list[loc]=dum;
    }
  //............................................... 
    int calls=0,d,max,nno; 
    start=clock(); time_t ti; srand((unsigned) time(&ti));
    for(i=target/2;i<LEN;i++)
	  {  max=0;//1+rand()%LEN;
        for(j=1;j<20;j++)
		  {//if(fixed[independent[i]][n-1]>(target-2)){
            calls++;
            k= Greedy_Swap(i);
            if(k>Max) { diff=end-start;nno=no;Max=k;}
            if(k>max) max=k; 
            if(Max>=target) break;
          }
      end=clock();  dif=end-start;
	 if(max>0) printf("\n %d\t%d\t%d\t%.5f\t%d",i,fixed[i][n-1],max,(float)(dif)/CLOCKS_PER_SEC,no);
	  if(Max>=target) break;
    }
    printf("\nMax Clique: %d\tTime taken%.5f\t Iteration:%d",Max,(float)(dif)/CLOCKS_PER_SEC,nno);
    getch();
    return 0;
   }
//..................................................................................
int Greedy_Swap(k) {
    int i,j,s,p,count=0,it=1;
    int c0[2][m],c[m],clen,cpos,c0len,cflen;
     c0len=clen=0; 
    for(i=0;i<m;i++) //initialization
      {c[i]=-1;c0[0][i]=0; c0[1][i]=0;}
     c[++clen]=k; 
     for(i=1;i<m;i++){ if(fixed[list[i]][k]==1)c0[0][c0len++]=list[i]; } 
     cflen=c0len;
   //printf("\n adjacent vertices of %d are\n",k);
   Update_Deg(c0,c0len,clen,&cflen); 
  //for(i=0;i<c0len;i++)printf("\n%d\t%d\n",c0[0][i],c0[1][i]);
    
  while(cflen>0)
     { if((clen+cflen)<=Max) return; 
       i=select_Min_Var(c0,c0len,cflen,clen,it); //printf("\n returned vertex %d \n",c0[0][i]);
       if (c0[0][i]<=0) break;
       it++;
       c[++clen]=c0[0][i]; Q[1][c0[0][i]]++; c0[0][i]=-1;c0[1][i]=0;cflen--; cpos=clen;
       no++;
       residual_graph_Update(c,c0,&c0len,cpos,&cflen,clen);
        Update_Deg(c0,c0len,clen,&cflen);
     }
 
   return clen;
  }
//...........................................................................
int select_Min_Var(int (*c0)[m], int c0len, int cflen,int clen, int it)//done//change
    { int i,j,k,x,s1,s2,c0pos=0,c0max=0,sum=0,count=0,list[2][cflen];  
        int flag=0; x=0;  
       for(k=0;k<c0len;k++){if(c0[0][k]>0){flag=1;c0pos=k;c0max=c0[1][k];break;}}
      if(flag==1)
         { for(j=k+1;j<c0len;j++)
            { if(c0[0][j]>0) 
               if(c0[1][j]>c0max){c0pos=j;c0max=c0[1][j]; }   
          }}
   // printf("\n c0max=%d\tcflen=%d...\n",c0max,cflen);
   if((c0max>2)&&(cflen>5))
      {for(i=0;i<c0len;i++)if(c0[0][i]>0){count++;sum=sum+c0[1][i];}
        sum=roundf(sum*1.0/count);
       for(i=0;i<c0len;i++)
        {if(c0[0][i]>0)
		if(it<0.4*target) { if(c0[1][i]<=sum){ list[0][x]=c0[0][i]; list[1][x]=i; x++;}}
        else 
		    { if(c0[1][i]>=sum){ list[0][x]=c0[0][i]; list[1][x]=i; x++;}}
		}
      if(x>2)
          { int pos=0,y,mx=0;
            for(i=0;i<3+x/20;i++)
             { j=rand()%x; //printf("\n ....rand() j=%d\t list[0][j]=%d\n",j,list[0][j]);
                 y=mxdeg(list[0][j],list,c0len,c0[1][list[1][j]],x,clen);
                 if((y>mx)){ mx=y; c0pos=list[1][j];pos=j;}          
      }   }}
    return c0pos;
    }
//...................................................................................  
 void residual_graph_Update(int *c, int (*c0)[m],int *c0len, int cpos,int *cflen,int clen)//update c1len, cflen, c0len
  {  int i,j,count=0;
      for(i=0;i<*c0len;i++)
        { if(c0[0][i]>0)
            {if( fixed[c[cpos]][c0[0][i]]==0 )
              {    *cflen=*cflen-1; 
                   c0[0][i]=0;c0[1][i]=0;
              }
      } }}    
  //................................................................................
 void Update_Deg(int (*c0)[m], int c0len,int clen,int *cflen)
  {  int i,j,dist[c0len],nu=0,count1=0,count2=0;

     for(i=0;i<=c0len;i++)c0[1][i]=0;
     for(i=0;i<c0len;i++)
        { if(c0[0][i]>0)
            { nu++;
             for(j=i+1;j<c0len;j++)
              { if(c0[0][j]>0)
               {if(fixed[c0[0][i]][c0[0][j]]==1)
                 { c0[1][i]=c0[1][i]+1;  c0[1][j]=c0[1][j]+1; }   
        }}} }
   }
//................................................................................. 
int mxdeg(int k ,int (*listt)[m],int c0len,int p,int x, int clen)
  {  int i,j=0,sum=0,ind, list[2][p],deg=0, c=0;
     for(i=0;i<p;i++) {list[0][i]=0;list[1][i]=0;}
      //printf("\n. maxdeg../////");
         for(i=0;i<x;i++)
           {if((listt[0][i]>0)&&(fixed[k][listt[0][i]]==1)) list[0][j++]=listt[0][i];}
       //  printf("\n.adjacent of %d\t p=%d\tj=%d\n",k,p,j);
       for(i=0;i<p-1;i++)
          { for(j=i+1;j<p;j++)
              {if(fixed[list[0][i]][list[0][j]]==1)
                {list[1][i]=list[1][i]+1;  list[1][j]=list[1][j]+1;}  
          }}
       for(i=0;i<p;i++) if(list[1][i]>(target-clen-2)) c++;
    return c;
}
//.....................................................................................

// The End........................................................................... 

