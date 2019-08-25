#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <math.h>
#include <string.h>

int crivo_erastotenes(int nums,int *list_nums, int p_max){
	time_t init_time,end_time;		//shared
	int i;							//shared
	int num_threads_max = p_max;	//shared	

	init_time = time(NULL);	
	for(i = 2; i < nums; i++){
		#pragma omp parallel num_threads(num_threads_max) //Inicio do processamento paralelo
		{

			int chunk = ceil((float)(nums-i)/num_threads_max);			//private 
			int ID = omp_get_thread_num();								//private			
			int i2;														//private
			int begin = (i+1) + (chunk * ID);							//private
			int end = (begin + chunk) > nums ? nums : (begin + chunk); 	//private
			
			for(i2 = begin;i2 < end; i2++){
				if(list_nums[i2] % i == 0){
					#pragma omp critical
					list_nums[i2] = -1;
				}
			}
		}
	}
	end_time = time(NULL);

	return (end_time - init_time);
}

void imprime(int nums, int *list_nums){ //imprime lista de primos
	int i;
	for(i=0;i < nums;i++){	
		if(list_nums[i] != -1) printf("%d ",list_nums[i]);
	}
	printf("\n");
}

int main(int argc, char *argv[]){
	if(argc != 4){
		printf("Usage: ./ep1 n X p (X= l -list,t -time,a -all)\n" );
		return 0;
	} 

	int nums = atoi(argv[1]); //Parametro (n)
	int *list_nums = malloc(nums*sizeof(int)); 
	int i, tempo;
	int p_max = atoi(argv[3]);	//Numero de processadores (p)


	for(i = 1;i <= nums;i++){ //Inicializando lista
		list_nums[i-1] = i; 
	}
	
	tempo = crivo_erastotenes(nums, list_nums, p_max); //execução do procedimento em paralelo

	if(strcmp(argv[2],"l") == 0){
		imprime(nums,list_nums);
	}

	if(strcmp(argv[2],"t") == 0){
		printf("%f\n", (float)tempo/1000);
	}

	if(strcmp(argv[2],"a") == 0){
		imprime(nums,list_nums);
		printf("%f\n", (float)tempo/1000);
	}



	return 0;
}