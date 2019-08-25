#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int crivo_erastotenes(int nums, int *list_nums){ 
	int i, i2;
	time_t begin, end;

	begin = time(NULL);
	for(i = 2; i < nums; i++){
		for(i2 = i+1;i2 < nums; i2++){
			if(list_nums[i2] % i == 0){
				list_nums[i2] = -1;
			}
		}
	}
	end = time(NULL);

	return (begin - end);
}

void imprime(int nums, int *list_nums){ //imprime lista primos
	int i;
	for(i=0;i < nums;i++){	
		if(list_nums[i] != -1) printf("%d ",list_nums[i]);
	}
}

int main(int argc, char *argv[]){
	if(argc < 1){ //Verifica se a entrada está correta
		printf("Usage: ./ep1 n X p (X= l -list,t -time,a -all)\n" );
	} 

	int nums = atoi(argv[1]); //Quantidade de números
	int *list_nums = malloc(nums*sizeof(int)); //lista dos números
	int i;
	int tempo; //Tempo do procedimento
	
	for(i = 1;i <= nums;i++){ //Inicializando lista
		list_nums[i-1] = i; 
	}

	tempo = crivo_erastotenes(nums,list_nums);

	imprime(nums,list_nums);
	
	printf("\n");	

	return 0;
}