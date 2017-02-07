#include<stdio.h>
#include<stdlib.h>
#include<sys/times.h>
#define LEN 300
//#define FILENAME "C125.9.clq.txt"
#define FILENAME "p_hat300_1.clq.txt"
//#define FILENAME "c-fat500-10.clq.txt"
//#define FILENAME "c-fat200-5.clq.txt"
//#define FILENAME "c-fat500-2.clq.txt"
//#define FILENAME "hamming6-2.clq.txt"
//#define FILENAME "hamming8-4.clq.txt"
//#define FILENAME "MANN_a9.clq.b.txt"
//#define FILENAME "johnson8-4-4.clq.txt"
//#define FILENAME "johnson16-2-4.clq.txt"
//#define FILENAME "sanr400_0.7.clq.txt"
//#define FILENAME "killer4.clq.txt"
//#define FILENAME "brock200_4.b.txt"
int max(int *,int,int);
int *calc_adjacent_list(int,int,int *,int,int *);

int m=LEN,n=LEN;
int fixed[LEN][LEN];
//int clique[LEN];
int Max=0;
 int temp=0;
//..................................................................
int main()
  {
     int i,j;
       for(i=0;i<m;i++)
            for(j=0;j<n;j++)
               fixed[i][j]=0; 
      FILE *f=fopen(FILENAME,"r");
       int integer1,integer2;
	   while(fscanf(f,"%d",&integer1)>0)
	    {
	      fscanf(f,"%d",&integer2);
	      fixed[integer1-1][integer2-1]=1;
	      fixed[integer2-1][integer1-1]=1;
	     }
    int list[LEN];int v[LEN];
    for(i=1;i<=LEN;i++){list[i-1]=i;v[i-1]=i;}
      
    struct timeval earlier, later,diff;
    gettimeofday(&earlier,NULL);
   printf("Clique getting calculated");
    max(v,0,LEN);
      
  gettimeofday(&later,NULL);
  diff.tv_sec=later.tv_sec-earlier.tv_sec;
  diff.tv_usec=later.tv_usec-earlier.tv_usec;
  printf("Clique size:%d\t Time is %lld microseconds\n",Max,1000000LL*diff.tv_sec+diff.tv_usec);
  
    return 0;
  }
//.............................................................
int max(int *list,int depth,int len){
     
        if(len==0)
		{if(depth>Max)
                Max=depth;
		temp++;
             return;
             }   int *adjacent_list;
		int ilen=0;
		int i=0;
		while(len>0)
                 { 
			
			int alen;
			if((depth+len-i)<=Max)
			  { if(depth==1) break; //stop recursion
			  return;
                          }
         
		 adjacent_list=calc_adjacent_list(list[i],i,list,len,&alen);
			i++;
                max(adjacent_list,depth+1,alen);
			  
    	      free(adjacent_list);
		       }
		
		return Max;
	}
	
//...................................................................

    
int *calc_adjacent_list(int source,int i,int *list,int curlen,int *len){
	int j;
	int temp[curlen];   //why not to use *temp
	*len=0;
	
	for(j=i+1;j<curlen;j++)
        {
		  if(fixed[source][list[j]]==1)
			temp[(*len)++]=list[j];
		}
	
	int *out=(int *)malloc(*len*sizeof(int));
	for(j=0;j<*len;j++){
		out[j]=temp[j];
	}
	return out;
}
