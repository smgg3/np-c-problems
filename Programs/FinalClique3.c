#include<stdio.h>
#include<stdlib.h>
#include<sys/times.h>
#define LEN 200
//#define FILENAME "m2.txt"
//#define FILENAME "2.txt"
//#define FILENAME "69.txt"
//#define FILENAME "class.txt"
//#define FILENAME "C125.9.clq.txt"
//#define FILENAME "sanr400_0.7.clq.txt"
//#define FILENAME "hamming8-4.clq.txt"
//#define FILENAME "hamming6-2.clq.txt"
//#define FILENAME "johnson8-4-4.clq.txt"
//#define FILENAME "johnson16-2-4.clq.txt"
//#define FILENAME "johnson32-2-4.clq"
//#define FILENAME "johnson8-2-4.clq"
//#define FILENAME "MANN_a9.clq.b.txt"
//#define FILENAME "c-fat500-2.clq.txt"
//#define FILENAME "c-fat500-2.clq.txt"
//#define FILENAME "c-fat500-5.clq.txt"
//#define FILENAME "c-fat500-10.clq.txt"
//#define FILENAME "c-fat200-1.clq.txt"
//#define FILENAME "c-fat200-2.clq.txt"
//#define FILENAME "c-fat200-2.clq.txt"
//#define FILENAME "brock200_1.b.txt"
#define FILENAME "brock200_2.b.txt"
//#define FILENAME "brock200_4.b.txt"
//#define FILENAME "brock400_1.b.txt"
//#define FILENAME "30.txt"

//#define FILENAME "p_hat300_1.clq.txt"
//#define FILENAME "rand100_6.txt"//ACT=8 cm=7
//#define FILENAME "hamming6-2.clq.txt"//ACT=32 but Coming=31

int ccheck[21];
int no_classes;
int Max=1;
int cc[2][LEN];
int arrange[2][LEN+1];
int fixed[LEN][LEN];
int indexx[LEN];
int b[LEN];int p=1;int oldval;
void MaxcliqueSize(int *, int, int,int,int,int);
int *calc_adjacent_list(int *,int *,int ,int *);
int *colorClass(int *, int *);
int check(int,int);
int total_degree(int *,int, int *);
int temp=0;
//..................................................................................

int main(){
	int i,j,k,v[LEN],*c,len=0;
       
       for(i=0;i<LEN;i++)
          {  for(j=0;j<LEN;j++)
               fixed[i][j]=0;
          v[i]=i;b[i]=-1;
          }
          
       FILE *f=fopen(FILENAME,"r");
       int m,n;
	   while(fscanf(f,"%d",&m)>0)
	    {
	      fscanf(f,"%d",&n);
	      fixed[m-1][n-1]=1;
	      fixed[n-1][m-1]=1;
	     }
  

  struct timeval earlier, later,diff;
   gettimeofday(&earlier,NULL);

   c=colorClass(v, &len);
  for(i=0;i<LEN;i++){arrange[0][i]=i;arrange[1][cc[0][i]]=cc[1][i];}
  printf("\n..........................................................\n");

i=0;
 while(indexx[i]>=0) 
     { 
       	len=LEN-indexx[i];
   	i++;
  	MaxcliqueSize(c,i,indexx[i-1],1,len,i);
    }
  
   printf("\n.............. Clique size= %d...........\n",Max);
   
   gettimeofday(&later,NULL);
  diff.tv_sec=later.tv_sec-earlier.tv_sec;
  diff.tv_usec=later.tv_usec-earlier.tv_usec;
  printf("\ndifference is %lld microseconds\n",1000000LL*diff.tv_sec+diff.tv_usec);
printf("# temp=%d\n",temp);     
return 0;
  }
  //..................................................................................

void MaxcliqueSize(int *c, int degree,int ind,int depth,int len,int i)
{   
    int k,k1,temp=0,alen;int s,r, deg;
    int *adjacent_list;
    int preadj[len];
    for(k=ind,s=0;s<len;k++,s++){
                preadj[s]=c[k];
                temp++;
                          }
 //printf("\nlist:");for(k=0;k<len;k++)printf(" %d \t",preadj[k]); 
 //printf("\n degree=%d\t max=%d \tdepth=%d\n",degree, Max,depth);
     if(len>1)
      { k1=arrange[1][preadj[1]];
      k=arrange[1][preadj[0]];
       if (((depth-1+degree)<=Max)||((k<i)&&((depth-1+b[k])<=Max) )) 
         { 
            if(depth-1==0){ b[i]=Max;return;}
            else {  
		    if(k==k1)degree=degree;
                    else degree=degree-1;
		    MaxcliqueSize(preadj,degree,1,depth,len-1,i);
  	           
		    return;
		 }  
            }
       }
  if(len==0){
	  if((depth)>Max )Max=depth-1;
		    b[i]=Max;
		    return;
	        }
   if(len==1){
		MaxcliqueSize(preadj,0,0,depth+1,0,i);
	      return;}
       ind=0;
    adjacent_list=calc_adjacent_list(preadj,&alen,len,&deg);  
     if(alen==0){
              
		if(k==k1) degree=degree;
		else degree=degree-1;
		 MaxcliqueSize(preadj,degree,1,depth,len-1,i);
	        return;
 		} 
       
   MaxcliqueSize(adjacent_list,deg,ind,depth+1,alen,i);
	free(adjacent_list);
	
  }
//...................................................................
int *calc_adjacent_list(int *list,int *len,int prlen,int *deg){
	int j,s,temp[LEN];
	*len=0;
	
      for(j=1,s=0;s<prlen-1;j++,s++){ 
               if(fixed[list[0]][list[j]]==1){ 
                              temp[(*len)]=list[j]; (*len)++;
                             // printf("\t%d",list[j]);
                                            }
    		}
     
	int *out=(int *)malloc(*len*sizeof(int));

	for(j=0;j<*len;j++){
       		out[j]=temp[j];
	}
    total_degree(out,j,deg); 
	*len=j;
	return out;
}
     

//..........................................................................................................

int *colorClass(int *v, int *len )
{
  int i=0,j=1,l,flag=0,cStart=0,count=0,m=0;
  int c[2*LEN];
  for(i=0;i<LEN;i++)indexx[i]=-1;
  c[0]=v[0];
  while(count<LEN)
   { 
        for(i=0;i<LEN;i++){
                         if(v[i]==-1)continue;
                         for(l=cStart;l<j;l++){ 
                                       if(fixed[v[i]][c[l]]==1){ flag=1; break;   }
                                             }
                         if(flag==1) {flag=0;continue;}
                         c[j++]=v[i]; v[i]=-1; count++;
                       }
          indexx[m]=j-2;
          cStart=j; m++;
   } 
  // printf("\n######################### number of classes=%d",m);
     no_classes=m;
     int var;
     for(i=0;i<LEN;i++){
                        var=c[i+1];
                        c[i]=var;
                        }
                        c[i]=-1;
                        
   int *out=(int *)malloc(j*sizeof(int));
  	for(i=LEN-1,l=0;i>=0;i--,l++){
               out[l]=c[i],cc[0][l]=c[i];
                                 } 
   *len=l;
   int temp=1, incr=0;
   for(i=LEN-1;i>=0;)
   {
           while(cc[0][i]!=c[indexx[incr]]){ 
                      cc[1][i]=temp;     
                      i--;                    
                                            }  
               cc[1][i]=temp;           
               temp++;
               incr++;
               i--;
   }
  // printf("\n");
   for(i=0;i<m;i++){
           indexx[i]=(LEN-1)-indexx[i];           
                       }
     
   	return out;                                       
      
    }
//..........................................................................

//--------------------------------------------------------------------------
int total_degree(int *list, int lnt,int *deg){
	
	int i, color1,color2,count=0;
  	   if(lnt>=1)
                 {
                 count=1;
                  color1=arrange[1][list[0]];
	         for(i=1;i<lnt;i++)
		  {
		color2=arrange[1][list[i]];
		if(color1==color2)continue;
		else {color1=color2; count++;}
		}
             }
	*deg=count;
	//printf("\nlnt=%d\n",count);
	}

