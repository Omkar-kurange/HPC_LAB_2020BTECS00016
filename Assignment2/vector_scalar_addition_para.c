#include <omp.h>
#include <pthread.h>
#include <stdio.h>

int main() {
    int N = 1000;
    int A[1000];
    for (int i = 0; i < N; i++)
        A[i] = 10;

    int B[1000];
    for (int i = 0; i < N; i++)
        B[i] = 20;

    int C[1000] = {0};
    double stime = omp_get_wtime();
#pragma omp parallel for reduction(+ \
                                   : C)
    for (int i = 0; i < N; i++) {
        C[i] = A[i] + B[i];
        printf("Index: %d Thread: %d\n", i, omp_get_thread_num());
    }

    for (int i = 0; i < N; i++) {
        printf("%d ", C[i]);
    }

    double etime = omp_get_wtime();
    double time = etime - stime;
    printf("\nTime taken is %f\n", time);
    printf("\n");
    return 0;
}