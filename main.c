#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdint.h>
#include <malloc.h>

extern void dot_product_asm(int n, double* A, double* B, double* sdot);

// helper function to initialize vectors with random values
/*
void initialize_vectors(double* A, double* B, int n) {
    srand((unsigned)time(NULL)); // seed the random number generator
    for (int i = 0; i < n; i++) {
        A[i] = (double)rand() / (RAND_MAX + 1.0); // random double in [0.0, 1.0)
        B[i] = (double)rand() / (RAND_MAX + 1.0); // random double in [0.0, 1.0)
    }
}
*/

// helper function to initialize vectors with an alternating pattern of 1 and 2
void initialize_vectors(double* A, double* B, int n) {
    for (int i = 0; i < n; i++) {
        A[i] = (i % 2 == 0) ? 1.0 : 2.0; // Alternates 1.0 and 2.0
        B[i] = (i % 2 == 0) ? 2.0 : 1.0; // Alternates 2.0 and 1.0
    }
}

// c implementation of the dot product
void dot_product_c(int n, double* A, double* B, double* sdot) {
    *sdot = 0.0;
    for (int i = 0; i < n; i++) {
        *sdot += A[i] * B[i];
    }
}

// measure execution time of a dot product function
double measure_execution_time(void (*func)(int, double*, double*, double*), int n, double* A, double* B, double* result) {
    double total_time = 0.0;
    for (int i = 0; i < 20; i++) {
        clock_t start = clock();
        func(n, A, B, result);
        clock_t end = clock();
        total_time += (double)(end - start) / CLOCKS_PER_SEC;
    }
    return total_time / 20.0;
}

// test to verify that dot product works properly (n = 5, 10)
void mini_test() {
    int sample_sizes[] = {5, 10};
    for (int i = 0; i < sizeof(sample_sizes) / sizeof(sample_sizes[0]); i++) {
        int n = sample_sizes[i];

        // memory allocation
        double *A = (double*)_aligned_malloc(n * sizeof(double), 16);
        double *B = (double*)_aligned_malloc(n * sizeof(double), 16);
        double sdot_c, sdot_asm;
        if (!A || !B) {
            fprintf(stderr, "memory allocation failed.\n");
            return;
        }

        initialize_vectors(A, B, n);

        // print the vectors and dot product results
        printf("\n==== dot product verification (n = %d) ====\n", n);
        printf("a: ");
        for (int j = 0; j < n; j++) printf("%.6f ", A[j]);
        printf("\nb: ");
        for (int j = 0; j < n; j++) printf("%.6f ", B[j]);
        printf("\n");

        dot_product_c(n, A, B, &sdot_c);
        dot_product_asm(n, A, B, &sdot_asm);
        printf("c kernel: %.6f | assembly kernel: %.6f\n", sdot_c, sdot_asm);

        // result validation
        printf(">>> validation: ");
        if (fabs(sdot_c - sdot_asm) < 1e-6) {
            printf("[pass] values match.\n");
        } else {
            printf("[fail] values differ.\n");
        }

        // free allocated memory
        _aligned_free(A);
        _aligned_free(B);
    }
}

// Compare the average times of the two kernels
void analyze_results(double avg_time_c, double avg_time_asm) {
    printf("\n===== Time Analysis =====\n");
    printf("C kernel average time: %.6f seconds\n", avg_time_c);
    printf("Assembly kernel average time: %.6f seconds\n", avg_time_asm);

    if (avg_time_c < avg_time_asm) {
        printf("[C Kernel] runs faster than [Assembly Kernel].\n");
    } else if (avg_time_asm < avg_time_c) {
        printf("[Assembly Kernel] runs faster than [C Kernel].\n");
    } else {
        printf("Both kernels run at the same speed.\n");
    }
}

int main() {
    // run mini test for n = 5 and n = 10
    mini_test();

    int sizes[] = {1 << 20, 1 << 24, 1 << 28}; // {2^20, 2^24, 2^28}, listed in instructions
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int i = 0; i < num_sizes; i++) {
        int n = sizes[i];

        // memory allocation
        double *A = (double*)_aligned_malloc(n * sizeof(double), 16);
        double *B = (double*)_aligned_malloc(n * sizeof(double), 16);
        double sdot_c, sdot_asm;
        if (!A || !B) {
            fprintf(stderr, "memory allocation failed.\n");
            return EXIT_FAILURE;
        }

        initialize_vectors(A, B, n);

        printf("\n===== dot product computation (n = %d) =====\n", n);
        printf(">>> c kernel\n");
        double avg_time_c = measure_execution_time(dot_product_c, n, A, B, &sdot_c);
        printf("time: %.6f seconds | dot product: %.6f\n", avg_time_c, sdot_c);

        printf(">>> assembly kernel\n");
        double avg_time_asm = measure_execution_time((void (*)(int, double*, double*, double*))dot_product_asm, n, A, B, &sdot_asm);
        printf("time: %.6f seconds | dot product: %.6f\n", avg_time_asm, sdot_asm);

        // result validation
        printf(">>> validation: ");
        if (fabs(sdot_c - sdot_asm) < 1e-6) {
            printf("[pass] results match!\n");
        } else {
            printf("[fail] results differ!\n");
            printf("c kernel: %.6f | assembly kernel: %.6f\n", sdot_c, sdot_asm);
        }

        // Compare the average times of both kernels
        analyze_results(avg_time_c, avg_time_asm);

        // free allocated memory
        _aligned_free(A);
        _aligned_free(B);
    }

    printf("\n===== end of computation =====\n");

    return 0;
}
