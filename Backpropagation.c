#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Define Network structure
#define INPUT_NODES 2
#define HIDDEN_NODES 2
#define OUTPUT_NODES 1
#define LEARNING_RATE 0.5
#define EPOCHS 10000

double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

double sigmoid_derivative(double x) {
    return x * (1 - x);
}

int main() {
    double input[4][INPUT_NODES] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
    double output[4][OUTPUT_NODES] = {{0}, {1}, {1}, {0}};
    double weights_input_hidden[INPUT_NODES][HIDDEN_NODES];
    double weights_hidden_output[HIDDEN_NODES][OUTPUT_NODES];
    double bias_hidden[HIDDEN_NODES] = {0.5, 0.5};
    double bias_output[OUTPUT_NODES] = {0.5};
    for (int i = 0; i < INPUT_NODES; i++)
        for (int j = 0; j < HIDDEN_NODES; j++)
            weights_input_hidden[i][j] = (double)rand() / RAND_MAX;
    for (int i = 0; i < HIDDEN_NODES; i++)
        for (int j = 0; j < OUTPUT_NODES; j++)
            weights_hidden_output[i][j] = (double)rand() / RAND_MAX;
    for (int epoch = 0; epoch < EPOCHS; epoch++) {
        double total_error = 0.0;
        for (int i = 0; i < 4; i++) {
            double hidden_layer[HIDDEN_NODES];
            double output_layer[OUTPUT_NODES];
            for (int j = 0; j < HIDDEN_NODES; j++) {
                hidden_layer[j] = bias_hidden[j];
                for (int k = 0; k < INPUT_NODES; k++)
                    hidden_layer[j] += input[i][k] * weights_input_hidden[k][j];
                hidden_layer[j] = sigmoid(hidden_layer[j]);
            }
            for (int j = 0; j < OUTPUT_NODES; j++) {
                output_layer[j] = bias_output[j];
                for (int k = 0; k < HIDDEN_NODES; k++)
                    output_layer[j] += hidden_layer[k] * weights_hidden_output[k][j];
                output_layer[j] = sigmoid(output_layer[j]);
            }
            double error = output[i][0] - output_layer[0];
            total_error += error * error;
            
            // Backpropagation
            double output_gradient = error * sigmoid_derivative(output_layer[0]);
            double hidden_gradient[HIDDEN_NODES];
            for (int j = 0; j < HIDDEN_NODES; j++) {
                hidden_gradient[j] = output_gradient * weights_hidden_output[j][0] * sigmoid_derivative(hidden_layer[j]);
            }
            
            // Gradient Descent
            for (int j = 0; j < HIDDEN_NODES; j++) {
                weights_hidden_output[j][0] += LEARNING_RATE * output_gradient * hidden_layer[j];
            }
            for (int j = 0; j < HIDDEN_NODES; j++) {
                for (int k = 0; k < INPUT_NODES; k++) {
                    weights_input_hidden[k][j] += LEARNING_RATE * hidden_gradient[j] * input[i][k];
                }
            }
            bias_output[0] += LEARNING_RATE * output_gradient;
            for (int j = 0; j < HIDDEN_NODES; j++) {
                bias_hidden[j] += LEARNING_RATE * hidden_gradient[j];
            }
        }
        if (epoch % 1000 == 0)
            printf("Epoch %d, Error: %f\n", epoch, total_error);
    }
    
    printf("Final Predictions:\n");
    for (int i = 0; i < 4; i++) {
        double hidden_layer[HIDDEN_NODES];
        double output_layer[OUTPUT_NODES];
        
        for (int j = 0; j < HIDDEN_NODES; j++) {
            hidden_layer[j] = bias_hidden[j];
            for (int k = 0; k < INPUT_NODES; k++)
                hidden_layer[j] += input[i][k] * weights_input_hidden[k][j];
            hidden_layer[j] = sigmoid(hidden_layer[j]);
        }
        
        for (int j = 0; j < OUTPUT_NODES; j++) {
            output_layer[j] = bias_output[j];
            for (int k = 0; k < HIDDEN_NODES; k++)
                output_layer[j] += hidden_layer[k] * weights_hidden_output[k][j];
            output_layer[j] = sigmoid(output_layer[j]);
        }
        
        printf("Input: %.1f %.1f => Prediction: %.4f\n", input[i][0], input[i][1], output_layer[0]);
    }
    
    return 0;
}
