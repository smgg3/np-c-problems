#include<stdio.h>
#include<string.h>
#include<stdlib.h>
main()
{
	char a[3000];
	
	printf("Enter new file name: ");
	scanf("%s",a);
	FILE *fp=fopen(a,"r");
	char *p="SRE";
	char *d;
	d=(char *)malloc(100000);
	char ch=getc(fp);
	int i=0;
	int v=1;
	printf("space%c\n",v);
	while(1)
	{
		if(ch>0 && ch<120)
		{
		
			d[i]=ch;
			i++;
	    }
		if(ch==EOF)
		   break;
		ch=getc(fp);
	}
	d[i]=0;
	
	char ans[10]="abcdefgh";
	int ra=0;
	int j;
	for(j=0;j<i;j++)
	{
           
            if(*d==1)
            {
                     int rambu=0;
                     char so;
                if(*(d+1)>47 && *(d+1)<55)
                {
                             rambu=1;
                             so=ans[(*(d+1))-48];  //s0 means student_option
                }
                
                while(rambu==1)
                {
                      if(*d=='S' && *(d+1)=='R' && *(d+2)=='E')
                      {
                          printf("%c",*(d+3));
                          if(*(d+4)!='t')
                            printf("%c-%2c\n",*(d+4),so);
                          else
                            printf("-%2c\n",so);
                          break;      
                      }
                      d++;
                              
                }
                
                
                        
            }
            d++;
            
    }
	
	
	
	getchar();
	getchar();
	
}
