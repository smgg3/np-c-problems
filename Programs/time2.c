#include <sys/time.h>
#include <stdio.h>
//#include <stdlib.h>
//#include <unistd.h>

int main(void)
{
  struct timeval earlier;
  struct timeval later;
   struct timeval diff;
  long long t;

  gettimeofday(&earlier,NULL);
  
  sleep(3);

  gettimeofday(&later,NULL);
  diff.tv_sec=later.tv_sec-earlier.tv_sec;
  diff.tv_usec=later.tv_usec-earlier.tv_usec;
  t=1000000LL*diff.tv_sec+diff.tv_usec;
  printf("difference is %lld microseconds\n",t);

  return 0;
} /* main() */
