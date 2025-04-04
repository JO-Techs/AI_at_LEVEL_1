#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define DATASET_SIZE 6
double X[DATASET_SIZE] = {1, 2, 3, 4, 5, 6};
double Y[DATASET_SIZE] = {3, 5, 7, 9, 11, 13};
double stochastic_gradient_descent(double learning_rate, int max_iters) {
    double theta0 = 0.0; // Bias term
    double theta1 = 0.0; // Slope term

    srand(time(0)); // Seed for randomness

    for (int iter = 0; iter < max_iters; iter++) {
        int i = rand() % DATASET_SIZE; // Randomly pick a data point
        double prediction = theta0 + theta1 * X[i];
        double error = prediction - Y[i];
        
        // Update parameters
        theta0 -= learning_rate * error;
        theta1 -= learning_rate * error * X[i];

        printf("Iteration %d: theta0 = %.6f, theta1 = %.6f\n", iter + 1, theta0, theta1);
    }
    return theta1; // Final slope (just for demonstration)
}

int main() {
    double learning_rate = 0.01;
    int max_iters = 100;
    double result = stochastic_gradient_descent(learning_rate, max_iters);
    printf("Final slope (theta1): %.6f\n", result);
    return 0;
}
