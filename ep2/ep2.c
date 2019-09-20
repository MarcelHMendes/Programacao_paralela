#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int partition(int *A, int p ,int r){
	int x = A[r];
	int i = p-1;
	int j,temp;

	for(j = p; j < r-1;j++){
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
	int num_rand = p + (rand() % r)-1;
	return num_rand;
}

int randomized_partition(int *A, int p,int r){
	int ret, temp;
	int i = generate_random(p,r);

	temp = A[r];
	A[r] = A[i];
	A[i] = temp;

	ret = partition(A,p,r);
	return 0;
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
			randomized_select(A, p, q-1,i);
			}else{
				randomized_select(A, q+1, r, i-k);
			}
	return 0;		
}


int main(int argc, const char * argv[]){
	int *A = (int*) malloc(21*sizeof(int));
	int i, resp;

	for(i=0; i < 10; i++){
		A[i] = i+1;
	}

	resp = randomized_select(A,1,9,6);

	printf("%d\n", resp );

	return 0;
}