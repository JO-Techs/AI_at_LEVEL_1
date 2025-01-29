#include <stdio.h>
#include <math.h>
double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}
double sigmoid_derivative(double x) {
    return x * (1.0 - x); 
}
int main() {
    double inputs[] = {-2.0, -1.0, 0.0, 1.0, 2.0};
    int num_inputs = sizeof(inputs) / sizeof(inputs[0]);
    printf("Input\tSigmoid Output\n");
    printf("------------------------\n");
    for (int i = 0; i < num_inputs; i++) {
        double output = sigmoid(inputs[i]);
        printf("%.2f\t%.6f\n", inputs[i], output);
    }
    return 0;
}
