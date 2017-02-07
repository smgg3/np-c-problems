#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

long long timeval_diff(struct timeval *difference,
             struct timeval *end_time,
             struct timeval *start_time
            )
   {
    struct timeval temp_diff;

	  if(difference==NULL)
	  {
	    difference=&temp_diff;
	  }
    difference->tv_sec =end_time->tv_sec -start_time->tv_sec ;
    difference->tv_usec=end_time->tv_usec-start_time->tv_usec;
 
   return 1000000LL*difference->tv_sec+
                   difference->tv_usec;
   } /* timeval_diff() */

int
main(void)
{
  struct timeval earlier;
  struct timeval later;
  struct timeval interval;
  
  if(gettimeofday(&earlier,NULL))
  {
    perror("first gettimeofday()");

    exit(1);
  }

  sleep(3);

  if(gettimeofday(&later,NULL))
  {
    perror("second gettimeofday()");

    exit(1);
  }

  printf("difference is %lld microseconds\n",timeval_diff(NULL,&later,&earlier));

  return 0;

} /* main() */
