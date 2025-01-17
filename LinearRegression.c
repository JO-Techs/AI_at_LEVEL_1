/*LINEAR REGRESSION IS ONE OF THE MOST BASIC MATHEMATICAL ALGORITHMS WHICH IS USED IN MACHINE LEARNIG MODELS TO CREATE PREDICTIVE SYSTEMS*/



#include <stdio.h>
#include <math.h>

// Calculate mean of an array
double calculate_mean(double data[], int size) {
    double sum = 0.0;
    for (int i = 0; i < size; i++) 
        sum += data[i];
    return sum / size;
}

// Calculate the slope (m) and intercept (b)
void calculate_linear_regression(double x[], double y[], int size, double *slope, double *intercept) {
    double x_mean = calculate_mean(x, size);
    double y_mean = calculate_mean(y, size);

    double numerator = 0.0, denominator = 0.0;
    for (int i = 0; i < size; i++) {
        numerator += (x[i] - x_mean) * (y[i] - y_mean);
        denominator += (x[i] - x_mean) * (x[i] - x_mean);
    }

    *slope = numerator / denominator; // m = S[(x - x¯)(y - ?)] / S[(x - x¯)^2]
    *intercept = y_mean - (*slope * x_mean); // b = ? - m * x¯
}

// Function to predict y for a given x
double predict(double x, double slope, double intercept) {
    return slope * x + intercept; // y = mx + b
}

// Function to calculate Mean Squared Error (MSE)
double calculate_error(double x[], double y[], int size, double slope, double intercept) {
    double error = 0.0;
    for (int i = 0; i < size; i++) {
        double predicted_y = predict(x[i], slope, intercept);
        error += pow((y[i] - predicted_y), 2); // (y_actual - y_predicted)^2
    }
    return error / size; // MSE = S[(y_actual - y_predicted)^2] / n
}

int main() {
    // Example dataset
    double x[] = {1, 2, 3, 4, 5}; // Input features
    double y[] = {2.2, 2.8, 4.5, 3.7, 5.5}; // Target values
    int n = sizeof(x) / sizeof(x[0]); // Number of data points

    double slope, intercept;

    // Calculate slope and intercept
    calculate_linear_regression(x, y, n, &slope, &intercept);

    // Print the linear regression equation
    printf("Linear Regression Equation: y = %.2fx + %.2f\n", slope, intercept);

    // Predict a value
    double new_x = 6.0;
    double predicted_y = predict(new_x, slope, intercept);
    printf("Prediction for x = %.2f: y = %.2f\n", new_x, predicted_y);

    // Calculate and print the Mean Squared Error
    double error = calculate_error(x, y, n, slope, intercept);
    printf("Mean Squared Error: %.2f\n", error);

    return 0;
}
