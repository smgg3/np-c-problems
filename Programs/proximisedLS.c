#include<stdio.h>
#include<math.h>
#define LEN 400
int target=27;
//#define FILENAME "txt10.txt"
//#define FILENAME "c-fat500-5.clq.txt"
//#define FILENAME "p_hat500-3.clq.txt"
//#define FILENAME "hamming8-2.clq.txt"
//#define FILENAME "johnson8-2-4.clq.txt"
//#define FILENAME "C250.9.clq.txt"
//#define FILENAME "gen400_p0.9_55.b.txt"
//#define FILENAME "san400_0.7_1.clq.txt"
//#define FILENAME "sanr400_0.7.clq.txt"
#define FILENAME "brock400_1.b.txt"

int m=LEN+1,n=LEN+2;
int fixed[LEN+1][LEN+2];
int clr[LEN][LEN];
int distance[LEN+1][LEN+3];
void insert(int,int);


//int clique[LEN];
//int Max=0;
int main()
{ int i,j,k;
    printf("\nCliques getting computed\n");
    for(i=1;i<m;i++) {fixed[i][0]=i; fixed[0][i]=i; for(j=1;j<n;j++){ fixed[i][j]=0;distance[i][j]=0;} }             
       FILE *f=fopen(FILENAME,"r");
       int integer1,integer2; 
    while(fscanf(f,"%d",&integer1)>0)
	    {fscanf(f,"%d",&integer2);
	      fixed[integer1][integer2]=1;
	      fixed[integer2][integer1]=1;
	      fixed[integer1][n-1]=fixed[integer1][n-1]+1;
	      fixed[integer2][n-1]=fixed[integer2][n-1]+1;
	     }

//printf("\nAdjacancy Matrix........................................\n");
//for(i=1;i<m;i++){ for(j=1;j<n;j++)  printf("%d \t",fixed[i][j]);  printf("\n");}

//finding distance matrix   
int count=0,count1,count2,x,p,q,t,adj[2][LEN], aadj[LEN]; 
for(i=1;i<LEN;i++)
  {for(j=i+1;j<=LEN;j++)
     {if(fixed[i][j]==1)
        {count1=1; x=0; //printf("i=%d, j=%d\t",i,j);
         for(k=1;k<=LEN;k++)
           {if((fixed[k][i]==1)&&(fixed[k][j]==1)) 
             {adj[0][x]=k;adj[1][x++]=1;count2=0;q=0; 
              for(p=0;p<x;p++)
                { //if(count1<target) t=count1/2; else t=target;
				 if((fixed[adj[0][p]][k]==1)&&(adj[1][p]>count1/3)) {count2++;aadj[q++]=p;}} aadj[q++]=x-1;
			//	printf("k=%d, count2=%d\t",k,count2);
              if(count2>=count1)
			   {count1++;
			    for(p=0;p<q;p++) if(adj[1][aadj[p]]<count1) adj[1][aadj[p]]=count1;
		    	}
        } }   
     // printf("\n count1=%d, count2==%d\n...........................\n",count1,count2);
      distance[i][j]=count1;distance[j][i]=count1; 
      }} if(count1>count)count=count1;}
   //for(i=1;i<m;i++){for(j=1;j<m;j++) printf("%d\t ",distance[i][j]); printf("\n"); }
   printf("\nMax=%d\n",count);
     getch();
}                                                                
