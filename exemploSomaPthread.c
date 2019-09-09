#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


pthread_t threads[2];

struct args {
	int *vector; 
	int inicio;
	int fim;
} ;

void *thread_func_soma(void *args){
	int value;
	value = (*(struct args*)(args)).inicio;

	printf("%d\n", value);
}


int main(int argc, char **argv){

	int i;
	int *vector = (int*) malloc(20*sizeof(struct args));
	int chunk = 10;//valor de teste


	struct args *prologue = (struct args *) malloc(sizeof(struct args));
		
	/*Inicializando vector*/	
	for (i=0;i<20;i++){
		vector[i] = i;
	}	
		
	
	for(i=0;i < 2;i++){
		/*calculo do escopo da thread*/
		prologue->vector = vector;
		prologue->inicio =  i*chunk;
		prologue->fim = i*chunk + chunk;	
		pthread_create(&(threads[i]), NULL, thread_func_soma, prologue);
	}
	
	

	for(i=0;i < 2;i++){
		pthread_join(threads[i], (void*) &vector);		
	}
	
	
	return 0;
}