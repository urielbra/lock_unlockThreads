#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "check.h"

#define NUM_THREADS 2

int x = 0 ;
int waiting[NUM_THREADS];
volatile int lock = 0;


void *threadBody (void *id)
{

   long tid = (long) id ;
	int index,j;
	int i = (int) id;
	int key;

	
		 waiting[i] = 1; //Indica que o processo i está esperando
		 key = 1; //Indica se o recurso está ocupado ou não
		 while (waiting[i] && key)
		 key = __sync_lock_test_and_set(&lock, 1); //Sai do “while” quando recurso livre
		 waiting[i] = 0;
		
		/*SEÇÃO CRITICA*/
		for (index=0;index<100;index++){
		   x++ ;
		} 
		/*SEÇÃO CRITICA*/

		/*Procura na lista pelo o próximo processo que está esperando*/
		j = (i + 1) % NUM_THREADS; //Inicia a busca no próximo
		while ((j != i) && !waiting[j]) //Enquanto não encontrar
		 j = (j + 1) % NUM_THREADS; //Passa para o próximo
		if (j == i) //Se não há processos esperando
		 __sync_lock_release(&lock); //Libera o recurso
		else
		 waiting[j] = 0; //Libera o processo “j” do “while” nalinha 4.
		 /*executa o restante da seção */


		pthread_exit (NULL) ;
}

int main (int argc, char *argv[])
{


   pthread_t thread [NUM_THREADS] ;
   long i, status ;
   
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
