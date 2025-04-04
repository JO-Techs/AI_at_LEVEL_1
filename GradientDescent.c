#include <stdio.h>
#define LEARNING_RATE 0.01
#define MAX_ITERATIONS 1000
#define NUM_SAMPLES 5
double calculate_mse(double x[], double y[], double m, double b, int n) {
    double total_error = 0.0;
    for (int i = 0; i < n; i++) {
        double predicted = m * x[i] + b;
        total_error += (predicted - y[i]) * (predicted - y[i]);
    }
    return total_error / n;
}
void gradient_descent(double x[], double y[], int n) {
    double m = 0.0;  
    double b = 0.0;  
    double m_gradient, b_gradient;
    for (int i = 0; i < MAX_ITERATIONS; i++) {
        m_gradient = 0.0;
        b_gradient = 0.0;
        for (int j = 0; j < n; j++) {
            double predicted = m * x[j] + b;
            m_gradient += -2.0 / n * x[j] * (y[j] - predicted);
            b_gradient += -2.0 / n * (y[j] - predicted);
        }
        m -= LEARNING_RATE * m_gradient;
        b -= LEARNING_RATE * b_gradient;
        if (i % 100 == 0) {
            printf("Iteration %d: MSE = %.6f, m = %.6f, b = %.6f\n", 
                   i, calculate_mse(x, y, m, b, n), m, b);
        }
    }
    printf("Final parameters: m = %.6f, b = %.6f\n", m, b);
}
int main() {
    double x[NUM_SAMPLES] = {1.0, 2.0, 3.0, 4.0, 5.0};
    double y[NUM_SAMPLES] = {2.0, 2.5, 3.0, 3.5, 4.0};
    gradient_descent(x, y, NUM_SAMPLES);
    
    return 0;
}
