#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define LEN 200 	
#define target 200

//#define FILENAME "8.txt"
//#define FILENAME "txt10.txt"
//#define FILENAME "dom.txt"
//#define FILENAME "DAGS1.txt"
//#define FILENAME "c-fat500-5.clq.txt"
//#define FILENAME "p_hat1500-1.clq.txt"
//#define FILENAME "hamming8-4.clq.txt"
//#define FILENAME "johnson8-4-4.clq.txt"
//#define FILENAME "C1000.9.clq.txt"
//#define FILENAME "gen400_p0.9_75.b.txt"
//#define FILENAME "san400_0.9_1.clq.txt"
//#define FILENAME "sanr400_0.7.clq.txt"
//#define FILENAME "brock800_4.b.txt"
#define FILENAME "r200.5.txt"
//#define FILENAME "MANN_a45.clq.b.txt" 
//#define FILENAME "keller6.clq.txt" 

//#define FILENAME "abb313GPIA.col.txt"
//#define FILENAME "anna.col.txt" 
//#define FILENAME "ash331GPIA.txt"
//#define FILENAME "david.txt"
//#define FILENAME "DSJC500.9.txt"
//#define FILENAME "DSJC500.5.clq.txt"
//#define FILENAME "DSJR500.5.txt"
//#define FILENAME "fpsol2.i.2.txt"
//#define FILENAME "games120.txt"
//#define FILENAME "homer.txt"
//#define FILENAME "huck.txt"
//#define FILENAME "inithx.i.3.col.txt"
//#define FILENAME "jean.col.txt"
//#define FILENAME "latin_square_10.col.txt"
//#define FILENAME "le450_5d.txt"
//#define FILENAME "miles750.txt"
//#define FILENAME "mug88_25.txt"
//#define FILENAME "mulsol.i.1.txt"
//#define FILENAME "le450_15a.txt"

 

//time_t ti; srand((unsigned) time(&ti));
//clock_t start; clock_t end;  clock_t dif;
int m=LEN+1,n=LEN+2;
int  mxColor;
int tempmat[LEN+1][LEN+2],matrix[LEN+1][LEN+2],bu[LEN+1][LEN+1];
int  c2[LEN+1], deg[LEN+1];  
 void colorvertex( int );

int main(){
    int i,j,k,co[m],ran[m]; //degree list,temporary degree matrix,color identification matrix,matrix to store covered vertices,randomly removed nodes list
    ran[0]=1;
	for(i=1;i<m;i++) { deg[i]=0;co[i]=0; for(j=1;j<n;j++) {matrix[i][j]=0;tempmat[i][j]=0;} }	 
	        
    FILE *f=fopen(FILENAME,"r");
     
    while(fscanf(f,"%d",&i)>0)
	    { fscanf(f,"%d",&j);
	      matrix[i][j]=1; matrix[j][i]=1;matrix[i][m]++;matrix[j][m]++; deg[i]=deg[i]+1; deg[j]=deg[j]+1;tempmat[i][j]=1;tempmat[j][i]=1;
	    }
//	printf(" \n DegreeList:"); for(i=1;i<m;i++) printf("\t%d ", deg[i]);
	int c=0,count=0;int a,b;//identifier to find a node
	for(i=1;i<m;i++) { bu[i][0]=0; }
	for(i=1;i<m&&count<(m);i++)
	{ if(co[i]==0)
		{ for(j=1;(j<m&&c==0);j++)
			{
				if(co[j]==0&&tempmat[i][j]==0&&i!=j)
				{
					if(deg[i]>=deg[j])
					{
						for(k=1;k<m;k++)
						{
							if(tempmat[j][k]==1)
							{
								if(tempmat[i][k]!=1)break;
								else{a=i;b=j;}
							}
						}
				       if(k==m){c=1;break;}
					}
					else
					{
						for(k=1;k<m;k++)
						{
							if(tempmat[i][k]==1)
							{
								if(tempmat[j][k]!=1){k=m+1;}
								else{	a=j;b=i;}
							}
						}
						if(k==m){c=1;j=m;}	
					}
				}
			}
			
		}	
		
		printf("\n%d\n\n",c);
		/*for(j=1;j<m;j++){for(k=1;k<m;k++){
			printf("%d\t",tempmat[j][k]);
	   }printf("\n");}*/
	  if(c==1)
	    { bu[a][++bu[a][0]]=b; c=0;
	     printf("a  %d b %d\n",a,b);
		
		co[b]=1;deg[b]=0;
		 for(k=1;k<m;k++){if(tempmat[b][k]==1){tempmat[b][k]=0; tempmat[k][b]=0; if(b!=k)deg[k]--;}
		}}
	  else
	    {b=1;
		while(co[b]){b=1+rand()%LEN;};
	     printf("a  %d b %d\n",a,b);
		  ran[ran[0]++]=b;
	    		 co[b]=1;deg[b]=0;
		 for(k=1;k<m;k++){if(tempmat[b][k]==1){tempmat[b][k]=0; tempmat[k][b]=0; if(b!=k)deg[k]--; }}}
		 printf("\n"); count++;
	}i=1;
	for(i=1;i<m;i++){
		for(j=1;j<m;j++){
			tempmat[i][j]=matrix[i][j];if(tempmat[i][j]==1)deg[i]++;
		}
	}
	for(i=1;i<m;i++){
		printf("\n%d\t\t",i);
		for(j=1;j<bu[i][0]+1;j++){
			printf("%d\t",bu[i][j]);
		}
	}
	for(i=1;i<m;i++){deg[i]=0;
		for(j=1;j<bu[i][0]+1;j++){for(k=1;k<m;k++){tempmat[bu[i][j]][k]=0;tempmat[k][bu[i][j]]=0;		}
			
		}
	}
	for(j=1;j<m;j++){for(k=1;k<m;k++){
			if(tempmat[j][k]==1)deg[j]++;
	   }};
	//for(k=1;k<m;k++){printf("%d\t ",deg[k]);}
	colorvertex(m); printf("\n MxColor=%d\n",mxColor);
	
}
void colorvertex( int N)
 { int i,j,k,mx,p, temp=0, T1[N],T2[N], T3[N],co[N],L[N]; // t1[] contains Vertex,T2[] degree,T3[] max chosen vertex, color  & L[] vertex index in max deg ordered
   
    for(i=1;i<N;i++){ T1[i]=i;T2[i]=deg[i]; T3[i]=0; if(T2[i]>temp) {mx=i; temp=T2[i];}}// initialization &finding max deg vertex
  //max ordering.
  j=1; //printf("\nMaxDeg ordered vertex:");//printf("\n max deg vertex= %d\tN=%d\ttemp=%d\n \n", mx,N, temp);
 
  while(N>1)
   {  L[j]=T1[mx]; T1[mx]=T1[N-1]; T2[mx]=T2[N-1];T3[mx]=T3[--N]; temp=0; //printf("\t%d ", L[j]);
      for(i=1;i<N;i++)
          {if(tempmat[L[j]][T1[i]]==1)  {T2[i]=T2[i]-1; T3[i]++;}   
		  if((T3[i]>temp)||((T3[i]==temp)&&(T2[i]>T2[mx]))) {mx=i; temp=T3[i];}  //1. max saturated vertex first && them maxdegree
		  //	if((T2[i]>temp)||((T2[i]==temp)&&(T3[i]>T3[mx]))) {mx=i; temp=T2[i];}   //.2. Max degree vertex && then Max saturation vertex
		   }  
      j++; 
   } //printf(" \n mxn ordered list: "); for(i=1;i<m;i++) printf("\t%d ", L[i]);
  //Coloring vertices in c2[],  
  c2[L[1]]=1; k=3*target; //probable # colors
  for(i=2;i<m;i++)      
      { j=1;  for(p=1;p<k;p++) co[p]=0;
       while(j<i) 
         { if(tempmat[L[i]][L[j]]==1)
                co[c2[L[j]]]=1; //store existing colors on neighbors, printf("%d\t",c[T1lor[1][minOrd[j]]]);
         j++; 
         }
        
       p=1;
       
	   while((co[p]>0)&&(p<k)) p++;  // find min availabe color
       c2[L[i]]=p;  /*printf("%d\n",mxColor);*/if(p>mxColor) mxColor=p;
       
      }
      for(i=1;i<m;i++){
		for(j=1;j<bu[i][0]+1;j++){
			c2[bu[i][j]]=c2[i];
		}
	}
	printf("\n& corresponding color:::"); for(i=1;i<m;i++) printf("%d\t ", c2[L[i]]);  
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	    


