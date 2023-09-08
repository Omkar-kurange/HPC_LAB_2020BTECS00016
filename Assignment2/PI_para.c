#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define NUM_SAMPLES 10000000

int main() {
    int num_samples_inside_circle = 0;
    double x, y, distance;

    // Set the number of threads
    omp_set_num_threads(10); // You can change this to the desired number of threads

    // Seed the random number generator with the current time
    srand(time(NULL));

    double start_time = omp_get_wtime(); // Record the start time

    #pragma omp parallel for private(x, y, distance) reduction(+:num_samples_inside_circle)
    for (int i = 0; i < NUM_SAMPLES; i++) {
        // Generate random points in the range [0, 1)
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;

        // Calculate the distance from the origin
        distance = x * x + y * y;

        // Check if the point is inside the unit circle
        if (distance <= 1.0) {
            num_samples_inside_circle++;
        }
    }

    double end_time = omp_get_wtime(); // Record the end time

    // Estimate π using the Monte Carlo method
    double pi_estimate = 4.0 * num_samples_inside_circle / NUM_SAMPLES;

    printf("Estimated π = %f\n", pi_estimate);
    printf("Execution time: %f seconds\n", end_time - start_time); // Print the execution time

    return 0;
}