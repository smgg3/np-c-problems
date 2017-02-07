#include<stdio.h>
#include<math.h>
#define LEN 8

#define FILENAME "8.txt"

int m=LEN+1,n=LEN+2;
int fixed[LEN+1][LEN+2];
int clr[LEN][LEN];
int distance[LEN+1][LEN+3];
void insert(int,int);
int group(int,int);

//int clique[LEN];
//int Max=0;
int main()
{
int arr[LEN],nonindependent[LEN],p=0;
int i,j,count=0;
int incr,k,z;
int independent[LEN];

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
{for(j=i+1;j<=LEN;j++)
  { J=j;
    for(k=1;k<=LEN;k++)
     {if(fixed[i][k]!=fixed[j][k])
      count++;  
   }   
if(fixed[i][J]==1)
count=count-2;
 distance[i][j]=distance[j][i]=count; 
 distance[i][LEN+1]+=count;
 distance[j][LEN+1]+=count;
 count=0;
} }
   int cost=0; float g;
   for(i=1;i<=LEN;i++) cost=cost+distance[i][LEN+1];
   g=roundf(cost*1.0/LEN);
   for(i=1;i<=LEN;i++)
   { distance[i][LEN+2]=fabs(distance[i][LEN+1]-g); 
     for(j=1;j<=LEN+2;j++)
       printf("%d\t ",distance[i][j]);
     printf("\n"); 
   }
//sorting
printf("\n\n.....sorting vertices wrt cost (last column of distance matrix)...\n");

for(i=1;i<m;i++)
arr[i]=i;                
int loc,dum,big;
for(i=1;i<m;i++)
{
                  big=distance[arr[i]][n];
                  loc=i;
                  for(j=i+1;j<m;j++)
                  {
                      if(big>distance[arr[j]][n])
                      {
                           big=distance[arr[j]][n];
                           loc=j;              
                   }   }   
                 dum=arr[loc];
                 arr[loc]=arr[i];
                 arr[i]=dum;
}
printf("Sorted array according to degree:{");
for(i=1;i<m;i++)
  printf("%3d",arr[i]);                  
printf("}");
printf("\n.....independent set...........................................................................\n");

//finding independent set
incr=1;
independent[1]=arr[1];
for(i=2;i<=LEN;i++)
 { for(k=1;k<=incr;k++)
   { if(fixed[arr[i]][independent[k]]==1)
       {
                count++;
                 break;                
    }   }
if(count==0)
  independent[++incr]=arr[i]; 
else
    nonindependent[++p]=arr[i];
count=0;
}
printf("\n");
printf("Independent Set is: {");
for(i=1;i<=incr;i++)
   printf("%3d",independent[i]);
printf("}");
printf("\nfinding cluster//////////////////////////////////////////////////\n");
int sum=0;
for(i=1;i<=incr;i++)
   sum=sum+fixed[independent[i]][LEN+1];
 sum=sum+incr;  
int local[3][sum];
for(i=1;i<=sum;i++)
{
local[1][i]=-1; local[2][i]=0;                  
}
int l=0;
for(i=1;i<=incr;i++)
{
  for(j=1;j<=LEN;j++)
   {
      if(fixed[independent[i]][j]==1)
            {
              local[1][++l]=j;
             }
    }
++l;
}
int q,w=0,d=0, t;
float ed;

//label:
//for(q=1;q<=incr;q++){
/* for(i=1;i<sum;i++)
  { d++;  
  if(local[1][i+1]==-1){w=(w+d);t=(d*(d+1))/2;ed=(w*1.0)/t;d=(d+1)*ed;
  printf("\nw=%d\tt=%d\ted=%f\td=%d\n",w,t,ed,d);
  local[2][i+1]=d; i=i+2; d=1;w=0;}
  for(k=i+1;k<=sum;k++)
    {   if(local[1][k]==-1)break; 

           if(fixed[local[1][i]][local[1][k]]==1)
              {
                  local[2][i]=local[2][i]+1;
                  local[2][k]=local[2][k]+1; 
                  w=w+1;                                     
              }                                
}}  */
int v;
for(i=1;i<=sum;i++)
{                v=local[1][i];
                 if(v!=-1)
                 local[2][i]=distance[v][n];
                 else
                 local[2][i]=-1;
}
                                                   
for(j=1;j<=2;j++)
{
for(i=1;i<=sum;i++)
     {
                   printf("%5d",local[j][i]);
     }
     printf("\n");
}

     getch();
}                                                                
