#include<stdio.h>
#include<math.h>
#define LEN 10
#define FILENAME "txt10.txt"

int m=LEN+1,n=LEN+2;
int fixed[LEN+1][LEN+2];
int clr[LEN][LEN/2];
int distance[LEN+1][LEN+2];
void insert(int,int);
int group(int,int);
//int clique[LEN];
//int Max=0;
//......................................................................
int main()
{
int arr[LEN],independent[LEN/2],nonindependent[LEN],p=0;
int i,j,count=0;
int incr=1,k,z;

      for(i=1;i<m;i++) 
      {fixed[i][0]=i; fixed[0][i]=i; arr[i]=i;for(j=1;j<n;j++) fixed[i][j]=0; }
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
printf("\nAdjacancy Matrix........................................\n");
for(i=1;i<m;i++)
{ for(j=1;j<n;j++)
   printf("%d \t",fixed[i][j]);                 
  printf("\n");
} 
printf("\nDistance Matrix........................................\n");
//finding distance matrix   
int J; 
for(i=1;i<=LEN;i++)
{     
 for(j=i+1;j<=LEN;j++)
 {  J=j;
    for(k=1;k<=LEN;k++)
    { if(fixed[i][k]!=fixed[j][k])
     count++;  
   }   
 if(fixed[i][J]==1)
count=count-2;
 distance[i][j]=distance[j][i]=count; 
 count=0;
} }
 
int cost=0;   
   for(i=1;i<=LEN;i++)
   {
     for (j=1;j<=LEN;j++)
     {
         cost=cost+distance[i][j];
         
     }                  
         distance[i][LEN+1]=cost;
         cost=0;
                      
   }
   for(i=1;i<=LEN;i++)
   { for(j=1;j<=LEN+1;j++)
       printf("%d\t ",distance[i][j]);
  printf("\n"); 
   }

//independent set...........................................................................
incr==1;count=0;
independent[1]=arr[1];
for(i=2;i<m;i++)
 {for(k=1;k<=incr;k++)
   { if(fixed[arr[i]][independent[k]]==1)
         {   count++; break; }
    }
  if(count==0)
    independent[++incr]=arr[i]; 
  else
    nonindependent[++p]=arr[i];
  count=0;
}

printf("\nIndependent Set is: ");
for(i=1;i<=incr;i++)
{  
clr[1][i]=independent[i];
printf("%d\t",independent[i]);

}

//finding cluster.............................................................
int sum=0,m,sum1=0,pos=0,pos1=0,eq=0;
for(i=1;i<=p;i++)
   {  j=1; pos=pos1=j; 
      sum=group(j,nonindependent[i]);    
      for(j=2;j<=incr;j++)
             { sum1=group(j,nonindependent[i]);  
                if(sum1<sum) { sum=sum1;pos=j; }
		    } 
       insert(nonindependent[i],pos);
       for(m=pos+1;m<=incr;m++)
         { sum1=group(m,nonindependent[i]);
              if(sum==sum1)  insert(nonindependent[i],m); 
         } 
	printf("\n .............................................\n");   
   } 
  
printf("\n clusters are....\n");
for(i=1;i<=LEN;i++)
{      for(j=1;j<=LEN/2;j++)
        {  
            printf("%d\t",clr[i][j]);
         }
       printf("\n");     
}
getch(); 
}
//..............................   ..................................................
void insert(int x,int y)
 { //y is cluster no & x is vertex to be inserted in that cluster
     int i=1,j=1;
     while(clr[i][y]>0)
       i++;                  
      clr[i][y]=x;                
 }
//.....................................................................
int group(int k,int y)
{    int i=1,j=1,d=0,d1,m,n,c=0,flag=0;
     printf("\ncluster=%d\t vertex(y)=%d\n",k,y);
     while(clr[i][k]>0)
      {if(fixed[clr[i][k]][y]==1)
        { flag=1;
          d=d+distance[clr[i][k]][y];
        }
      else c++;
      i++;
      }  
	  d1=d;   
    if((i-c)>0)
	 { i=i-c;
       d1=roundf(d*1.0/i);
     }
    if(d==0&&flag==1) d1=1;
    printf("Distance=%d,i=%d,Avg_distance(d)=%d\n",d,i,d1);
    return d1; 
   }
//.......................................................................
