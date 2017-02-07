#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#define LEN 10
#define FILENAME "txt10.txt"

void remove_vertex(int);
void computing_deg();
void printing();
int list[LEN];
int m=LEN+1,n=LEN+3;
int fixed[LEN+1][LEN+3];

int main(){
	int i,j;
	for(i=0;i<LEN;i++)list[i]=0;
	
       for(i=0;i<m;i++)
            for(j=0;j<n;j++)
               fixed[i][j]=0; 
       for(i=0;i<m;i++){ fixed[i][0]=i;}
       for(j=0;j<n;j++){ fixed[0][j]=j;} 
		
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
	    
	    printing();
	     for(i=1;i<m;i++)
		{
	    	for(j=1;j<n-2;j++)
			{
	    	   if( fixed[i][j]==1 ) fixed[i][j]=0;
	    	   else {
	    	   	
				  if(i==j) fixed[i][j]=0;
				  else fixed[i][j]=1;
	    	   }
	    	}
	    }
	    
	    for(i=1;i<m;i++)
		{   fixed[i][n-1]=0;
	    	for(j=1;j<n-2;j++)
			{
	    	   if( fixed[i][j]==1 ) fixed[i][n-1]=fixed[i][n-1]+1;
	    	   
	    	}
	    }
	    
		printing();
	    
	   computing_deg();
	   int ind[LEN],size=0,vertex_no;
	    
	    while(1)
		{  vertex_no=0;
		   for(i=1;i<m;i++)
		   {  if(fixed[i][n-1]==0)
				{   
					vertex_no=i;
					break;
				}
		   }
		   
		   if(vertex_no==0)
		    {  for(i=1;i<m;i++)
				{  if(fixed[i][n-1]>0)
					{ 
                            vertex_no=i;
                            break;
                    }
                    else continue;
                }
			}
		    
			if(vertex_no==0)
			{
				break;
			} 
            else 
			{ for(i=vertex_no;i<m-1;i++)
				{
					if(  (fixed[vertex_no][n-1]>fixed[i+1][n-1])&&(fixed[i+1][n-1]>=1)  ) 
					{ 
						vertex_no=i+1; 						
					} 
                    else
					{
                    	if(  (fixed[vertex_no][n-1]==fixed[i+1][n-1])&&(fixed[i+1][n-1]>=1) )
				        {   
							if( fixed[vertex_no][n-2]<fixed[i+1][n-2] ) 
							{ 
								vertex_no=i+1; 								
							}
					   } 
                    }
                }		 
			}
			
			ind[size++]=vertex_no;
			remove_vertex(vertex_no);
			computing_deg();
		}   
		
		printf("\n####### Independent Vertices are :%d   #######\n\n",size);
		for(i=0;i<size;i++)
		{
			printf("%d\t",ind[i]);
		}
		
		  
getch();
}


void remove_vertex(int vertex)
{
	int i,j,k;
	for(j=1;j<n-2;j++)
	{   
		if(fixed[vertex][j]==1 && fixed[j][n-1]>=0)
		{ 
		   for(k=1;k<n-2;k++)
			{ if(fixed[j][k]==1 && k!=vertex)
			    {    
					 fixed[k][j]=0;
		             fixed[j][k]=0;
			         fixed[k][n-1]=fixed[k][n-1]-1;			         
				}
			}		
			fixed[j][n-1]=-1;
			fixed[vertex][j]=0; fixed[j][vertex]=0;
		}
	}
	fixed[vertex][n-1]=-1;
}

//........................................................
void computing_deg(){
	int i,j,k,p,q; int idx;
    
	for(i=1;i<m;i++)fixed[i][n-2]=0;
	for(i=1;i<m;i++)
	{  if(fixed[i][n-1]>=1)
	   {    
	        idx=0;
			for(j=1;j<n-2;j++)
			{  if(fixed[i][j]==1 && fixed[j][n-1]>=1)
			   {
					fixed[i][n-2]=fixed[i][n-2]+( fixed[j][n-1]-1 );
					list[idx]=j;
					idx++;
			   }
			}	
					
			for(p=0;p<idx;p++)
			{ for(q=p+1;q<idx;q++)
			   { if(fixed[list[p]][list[q]]==1)
				  {
					fixed[i][n-2]=fixed[i][n-2]-1;
				  }
			   }			
			}		    
	    }
	}	
}


//..............................................................
void printing()
{
	 printf("\n\n.........................The Matrix is printing..........................\n\n");
	 int i,j;
	 for(i=0;i<m;i++)
	 {  for(j=0;j<n;j++)
			    printf("%d\t",fixed[i][j]);		               
		printf("\n\n");
	 } 
}
