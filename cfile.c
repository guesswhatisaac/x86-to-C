#include <stdio.h>
#include <stdlib.h>

void clear_input_buffer() {
    while (getchar() != '\n'); 
}

extern double dpasm(double *A, double *B, size_t n);

int main() {
    size_t n;
    
    printf("\nEnter the size of the vectors: ");
    if (scanf("%zu", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid vector size.\n");
        return EXIT_FAILURE;
    }

    // Allocate memory for vectors
    double *A = (double *)malloc(n * sizeof(double));
    double *B = (double *)malloc(n * sizeof(double));

    if (A == NULL || B == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }
    
    // Get input for vector B
    printf("\nEnter %zu elements for vector A:\n", n);
    size_t i;
    for (i = 0; i < n; i++) {
        while (scanf("%lf", &A[i]) != 1) {
            fprintf(stderr, "Invalid input for vector A. Please enter a valid number: ");
            clear_input_buffer(); 
        }
    }

    // Get input for vector B
    printf("\nEnter %zu elements for vector B:\n", n);
    for (i = 0; i < n; i++) {
        while (scanf("%lf", &B[i]) != 1) {
            fprintf(stderr, "Invalid input for vector B. Please enter a valid number\n");
            clear_input_buffer(); 
        }
    }
    
    printf("\n");
    
    printf("Vector A: ");
    for (i = 0; i < n; i++) {
        printf("%.2f ", A[i]);
    }
    printf("\n");

    printf("Vector B: ");
    for (i = 0; i < n; i++) {
        printf("%.2f ", B[i]);
    }
    printf("\n");

    // Call assembly function for dot product
    double result = dpasm(A, B, n);

    printf("Dot product: %.6f\n", result);

    free(A);
    free(B);

    return 0;
}


