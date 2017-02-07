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
int arr[LEN],nonindependent[LEN],p=0;
int i,j,count=0;
int incr=1,k,z;
int independent[LEN/2];
      for(i=0;i<m;i++)
         for(j=0;j<=n;j++)
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
//sorting..min degree first.................................;
for(i=1;i<m;i++)
arr[i]=i;                
int loc,dum,big;
for(i=1;i<m;i++)
{     big=fixed[arr[i]][n-1];
            loc=i;
      for(j=i+1;j<m;j++)
         { if(big>fixed[arr[j]][n-1])
             { big=fixed[arr[j]][n-1]; loc=j;}         
          }
                 dum=arr[loc];
                 arr[loc]=arr[i];
                 arr[i]=dum;
 }
//independent set...........................................................................
incr==1;count=0;
independent[1]=arr[1];
for(i=2;i<m;i++)
 {for(k=1;k<=incr;k++)
   { if(fixed[arr[i][independent[k]]==1)
         {   count++; break; }
    }
  if(count==0)
    independent[++incr]=arr[i]; 
  else
    nonindependent[++p]=arr[i];
  count=0;
}
printf("Sorted array according to degree:{");
for(i=1;i<m;i++)
  printf("%3d",arr[i]);                  
printf("}");
printf("\nIndependent Set is: ");
for(i=1;i<=incr;i++)
{  
clr[1][i]=independent[i];
printf("%d\t",independent[i]);

}
for(i=1;i<=p;i++)
printf("%d",nonindependent[i]);

//finding cluster.............................................................
int sum=0,m,sum1=0,pos=0,pos1=0,eq=0;
z=0;
  for(i=1;i<=p;i++)
   { 
                   j=1; pos=pos1=j; 
                   sum=group(j,nonindependent[i]);
                   if(sum==0)
                   sum=999;
                   
                   
        for(j=2;j<=incr;j++)
             {  
                            sum1=group(j,nonindependent[i]);  
                           if(sum1!=0)  { 
                           if(sum>sum1)
                           { 
                           sum=sum1;pos=j;
                           }
                           }                       
            }
            
            
             insert(nonindependent[i],pos);
        for(m=pos+1;m<=incr;m++)
         {
                                sum1=group(m,nonindependent[i]);
                                if(sum==sum1)  
                                { 
                                eq=1; 
                                 insert(nonindependent[i],m); 
                                }
           }
           printf("sum=%d\n",sum);
         
       
   }  
 printf("\n clusters are....\n");
for(i=1;i<=LEN;i++)
{      for(j=1;j<=LEN/2;j++)
                 {  //if(clr[i][j]>0)
                     printf("%d\t",clr[i][j]);
                 }
                 printf("\n");     
}
getch(); 
}
//..............................   ..................................................
void insert(int x,int y)
{
     int i=1,j=1;
     while(clr[i][y]>0)
       i++;                  
      clr[i][y]=x;                
      }
//.....................................................................
int group(int k,int y)
{
     int i=1,j=1,d=0,m,n,c=0,flag=0;
    
      printf("\nk=%d\t y=%d\n",k,y);
     
     while(clr[i][k]>0)
     {    //m=clr[i][k];
    // printf("m=%d",m);
       if(fixed[clr[i][k]][y]==1)
        {     
              flag=1;
      d=d+distance[clr[i++][k]][y];
      printf("d=%d\t",d);
      }
      else{
      i++;
      c++;  }
      }
    
      
    if(i>c)i=i-c;
    
    c=0;
    if(i>1)i=i-1;  
    printf("i=%d\td=%d\n",i,d);
        d=roundf(d*1.0/i);
        if(d==0&&flag==1)
           d=1;
        
    printf("d=%d\t",d);
       return d; 
   }
//.......................................................................
