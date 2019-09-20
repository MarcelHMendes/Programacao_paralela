#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


pthread_t threads[2];
pthread_mutex_t lock;
int soma_total = 0;

struct args {
	int *vector; 
	int inicio;
	int fim;
};

void *thread_func_soma(void *args){
	int ini, fim, i, soma_local = 0 ;
	ini = ((struct args*)(args))->inicio;
	fim = ((struct args*)(args))->fim;
	int *vector = (*(struct args*)(args)).vector;

	for(i=ini;i < fim;i++){
		pthread_mutex_lock(&lock);
		printf("%d ", i);
		pthread_mutex_unlock(&lock);
		soma_local += vector[i]; 
	}
	printf("\n");
	pthread_mutex_lock(&lock);
	soma_total += soma_local;
	pthread_mutex_unlock(&lock);

}


int main(int argc, char **argv){

	int i;
	int *vector = (int*) malloc(20*sizeof(struct args));
	int chunk = 10;//valor de teste

	
	struct args **prologue = (struct args **) malloc(2*sizeof(struct args*));
	for(i = 0; i < 2; i++){
		prologue[i] = (struct args *) malloc(sizeof(struct args));
	}

	
	/*Inicializando vector*/	
	for (i=0;i<20;i++){
		vector[i] = 1;
	}	
		
	
	for(i=0;i < 2;i++){
		/*calculo do escopo da thread*/
		prologue[i]->vector = vector;
		prologue[i]->inicio =  i*chunk;
		prologue[i]->fim = i*chunk + chunk;	
		pthread_create(&(threads[i]), NULL, thread_func_soma, prologue[i]);
	}
	

	for(i=0;i < 2;i++){
		pthread_join(threads[i], (void*) &vector);		
	}
	
	printf("%d\n", soma_total);

	return 0;
}