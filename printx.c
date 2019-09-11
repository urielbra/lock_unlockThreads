#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "check.h"

#define NUM_THREADS 5

int x = 0 ;
int lock = 0;

void *threadBody (void *id)
{
   long tid = (long) id ;
	int i;

	for (i=0;i<10000;i++){
		// printf("Oi Robson");
	   x++ ;

	 }
   pthread_exit (NULL) ;
}

int main (int argc, char *argv[])
{
   pthread_t thread [NUM_THREADS] ;
   long i, status ;
   	// struct rusage ru;
    // getrusage(RUSAGE_SELF, &ru);
    // printf("\nInvoluntarias: %5ld \nVoluntarias: %5ld",ru.ru_nivcsw,ru.ru_nvcsw);
   
   for (i=0; i<NUM_THREADS; i++) {
      status = pthread_create (&thread[i], NULL, threadBody, (void *) i) ;
//		sleep(1);
		CHECK(status==0);
   }
	for (i=0; i<NUM_THREADS; i++){
		   status = pthread_join (thread[i], NULL) ;
			CHECK(status==0);
	}
	printf ("\n\nValor final de x: %02d\n\n", x) ;	
   pthread_exit (NULL) ;
}
