#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int partition(int *A, int p ,int r){
	int x = A[r];
	int i = p-1;
	int j,temp;

	for(j = p; j <= r-1;j++){ //verificar
		if(A[j] <= x){
			i = i + 1;
			temp = A[i];
			A[i] = A[j];
			A[j] = temp;
		}	
	}
	temp = A[i+1];
	A[i+1] = A[j];
	A[j] = temp;

	return (i+1);
}

int generate_random(int p,int r){
	int num_rand = p + (rand() % (r-p));
	return num_rand;
}

int randomized_partition(int *A, int p,int r){
	int ret, temp;
	int i = generate_random(p,r);

	temp = A[r];
	A[r] = A[i];
	A[i] = temp;

	ret = partition(A,p,r);
	return ret;
}

int randomized_select(int *A, int p, int  r, int  i){
	int q, k;
	if(p == r){
		return A[p];
	}

	q = randomized_partition(A, p, r);
	k = q - p + 1;
	if(i == k){
		return A[q];
	}else	if(i < k){
			return randomized_select(A, p, q-1,i);
			}else{
				return randomized_select(A, q+1, r, i-k);
			}
}


int main(int argc, const char * argv[]){
	srand( (unsigned)time(NULL) );
	int *A = (int*) malloc(21*sizeof(int));
	int i, resp;

	for(i=0; i < 10; i++){
		A[i] = rand() % 30;
	}

	resp = randomized_select(A,0,9,3);

	for(i = 0; i < 9;i++){
		printf("%d ", A[i]);
	}

	printf("\n%d\n", resp);

	return 0;
}