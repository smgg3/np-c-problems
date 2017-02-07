#include<stdio.h>
#include<stdlib.h>
#include<sys/times.h>
#define LEN 120
//efine FILENAME "2.txt"
//#define FILENAME "69.txt"
//efine FILENAME "brock200_1.b.txt"  
//#define FILENAME "C125.9.clq.txt"
//#define FILENAME "killer4.clq.txt"
//#define FILENAME "sanr400_0.7.clq.txt"
//#define FILENAME "hamming8-4.clq.txt"
//#define FILENAME "hamming6-2.clq.txt"
//#define FILENAME "johnson8-4-4.clq.txt"
#define FILENAME "johnson16-2-4.clq.txt"
//#define FILENAME "c-fat200-5.clq.txt
//#define FILENAME "MANN_a9.clq.b.txt"
//#define FILENAME "c-fat500-2.clq.txt"
//#define FILENAME "c-fat500-2.clq.txt"
//#define FILENAME "c-fat500-2.clq.txt"
//#define FILENAME "c-fat200-5.clq.txt"
//#define FILENAME "brock400_2.b.txt"
//#define FILENAME "brock200_4.b.txt"
//#define FILENAME "brock200_4.b.txt"
//#define FILENAME "p_hat300_1.clq.txt"
//#define FILENAME "p_hat500-1.clq.txt"
//#define FILENAME "p_hat300-2.clq.txt"
int max(int *,int,int);
int * calc_ind(int *,int ,int *);
int *calc_adjacent_list(int,int *,int,int *);

int m=LEN+1,n=LEN+2;
int fixed[LEN+1][LEN+2];
int n;
int clique[LEN];
int Max=0;


int main(){
     int i,j;
       for(i=0;i<m;i++)
            for(j=0;j<n;j++)
               fixed[i][j]=0; 
       for(i=0;i<m;i++){ fixed[i][0]=i;}
       for(j=0;j<n;j++){ fixed[0][j]=j; } 
       //fixed[0][j-1]=999; 
       FILE *f=fopen(FILENAME,"r");
       int integer1,integer2;
	   while(fscanf(f,"%d",&integer1)>0)
	    {
	      fscanf(f,"%d",&integer2);
	      fixed[integer1][integer2]=1;
	      fixed[integer2][integer1]=1;
	      fixed[integer1][n-1]=fixed[integer1][n-1]+1;
	      fixed[integer2][n-1]=fixed[integer2][n-1]+1;
	    }
    int list[LEN];
    for(i=1;i<=LEN;i++) list[i-1]=i;
    
    int big,loc,dum;//sorting 
   	for(i=0;i<LEN;i++){ 
             big=fixed[list[i]][n-1];loc=i;
             for(j=i+1;j<LEN;j++){
                     if(fixed[list[j]][n-1]>big){big=fixed[list[j]][n-1];loc=j;}
                                 } 
                     dum=list[i];
                     list[i]=list[loc];
                     list[loc]=dum;
             }
    printf("\nmax clique is getting calculated...\n");
  struct timeval earlier, later,diff;
  gettimeofday(&earlier,NULL);
       
       max(list,1,LEN);
                
    gettimeofday(&later,NULL);
   diff.tv_sec=later.tv_sec-earlier.tv_sec;
   diff.tv_usec=later.tv_usec-earlier.tv_usec;
   printf("Clique size:%d\t time elapsed= %lld microseconds\n",Max,1000000LL*diff.tv_sec+diff.tv_usec);
     return 0;
  }
//.............................................................
int max(int *list,int depth,int len){
	       int *independent_list=NULL;
		int ilen=0; 
		int i,j,alen,*adjacent_list=NULL; 

             if(len==1)
	         { if(depth>Max)
	             Max=depth;
		      return;
                 }
         // if((depth+len)<=Max) return;
		int flag=1;
	independent_list=calc_ind(list,len,&ilen);
 
		for(i=0;i<ilen;i++) 
                 {  
		adjacent_list=calc_adjacent_list(independent_list[i],list,len,&alen);
	     if(depth+alen>Max)
                       {
			 max(adjacent_list,depth+1,alen);
		               
			   }
			free(adjacent_list);
		     }
		free(independent_list);
		return ;
	}
	
//...................................................................
int * calc_ind(int *list,int size,int *outsize){

   int i,j;
   int independent[LEN],count=0,incr=0;
   if(size>=1)
   {
      independent[0]=list[0];incr++;
      for(i=1;i<size;i++){
          count=0;
          for(j=0;j<incr;j++)if(fixed[independent[j]][list[i]]!=1    ) count++; 
          if(count==incr)independent[incr++]=list[i];
                      }
  }
       
     // printf("\nThe independent vertices are\n");
     int *ind=(int *)malloc(sizeof(int)*incr);
     for(i=0;i<incr;i++){   ind[i]=independent[i];}
     *outsize=incr;
     return ind;
 }
   
int *calc_adjacent_list(int source,int *list,int curlen,int *len){
	int i;
	int temp[curlen];   //why not to use *temp
	*len=0;
	for(i=0;i<curlen;i++){
		if(fixed[source][list[i]]==1){
			temp[(*len)++]=list[i];
			//*len=(*len)+1;
		}
	}
	int *out=(int *)malloc(*len*sizeof(int));
	for(i=0;i<*len;i++){
		out[i]=temp[i];
	}
	return out;
}
