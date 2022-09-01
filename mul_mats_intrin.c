#include<stdio.h>
#include<time.h>
#include <wasm_simd128.h>

void multiply_mats(int* out, int* in_a, int* in_b, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			out[i*n+j] = 0;
      int sum_arr[] = {0, 0, 0, 0};
      v128_t sum = wasm_v128_load(sum_arr);
			for (int k = 0; k < n; k+=4) {
				v128_t a = wasm_v128_load(&in_a[i*n+k]);
				v128_t b = wasm_v128_load(&in_b[j*n+k]);
				v128_t prod = wasm_i32x4_mul(a, b);
        sum = wasm_i32x4_add(sum, prod);
			}
      v128_t sum_duo = wasm_i32x4_add(sum, wasm_i32x4_shuffle(sum, sum, 2, 3, 0, 0));
      v128_t sum_one = wasm_i32x4_add(sum_duo, wasm_i32x4_shuffle(sum_duo, sum_duo, 1, 0, 0, 0));
      out[i*n+j] += wasm_i32x4_extract_lane(sum_one, 0);
		}
	}
}

int main() {
	const int N = 64;
	const int SIZE = N*N;
	const int IT = 10000;
	int out[SIZE];
	int in_a[SIZE];
	int in_b[SIZE];

	for (int i = 0; i < SIZE; i++) {
		in_a[i] = 1;
		in_b[i] = 1;
	}
	
	// transpose
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < i; j++) {
			int aux = in_b[i*N+j];
			in_b[i*N+j] = in_b[j*N+i];
			in_b[j*N+i] = aux;
		}
	}

	clock_t start = clock();
	for (int i = 0; i < IT; i++) {
		multiply_mats(out, in_a, in_b, N);
	}
	printf("multiply matrixs: %.3fs\n", ((double)(clock() - start))/CLOCKS_PER_SEC);

	// a dummy operation to avoid -O3
	// removing the multiply_mats loop.
	long long sum = 0;
	for (int i = 0; i < SIZE; i++) {
		sum += out[i];
	}
	if (sum != 64*64*64) {
		printf("incorrect sum: %lld\n", sum);
	}

	return 0;
}
