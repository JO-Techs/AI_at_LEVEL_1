#include <stdio.h>
#include <math.h>
#define MAX_SAMPLES 100
#define MAX_FEATURES 2
#define LEARNING_RATE 0.01
#define EPOCHS 1000
#define LAMBDA 0.01 // Regularization parameter

// Data structure for dataset
typedef struct {
    double features[MAX_FEATURES];
    int label;
} Sample;

// Dot product function
double dot_product(double *a, double *b, int size) {
    double result = 0.0;
    for (int i = 0; i < size; i++) {
        result += a[i] * b[i];
    }
    return result;
}

// SVM training function
void train_svm(Sample *data, int num_samples, double *weights, double *bias) {
    for (int epoch = 0; epoch < EPOCHS; epoch++) {
        for (int i = 0; i < num_samples; i++) {
            double dot = dot_product(weights, data[i].features, MAX_FEATURES);
            double y_pred = dot + *bias;
            if (data[i].label * y_pred < 1) {
                // Update weights and bias for misclassified points
                for (int j = 0; j < MAX_FEATURES; j++) {
                    weights[j] -= LEARNING_RATE * (2 * LAMBDA * weights[j] - data[i].label * data[i].features[j]);
                }
                *bias += LEARNING_RATE * data[i].label;
            } else {
                // Update weights for correctly classified points
                for (int j = 0; j < MAX_FEATURES; j++) {
                    weights[j] -= LEARNING_RATE * (2 * LAMBDA * weights[j]);
                }
            }
        }
    }
}

// Prediction function
int predict(double *features, double *weights, double bias) {
    double result = dot_product(weights, features, MAX_FEATURES) + bias;
    return result >= 0 ? 1 : -1;
}

int main() {
    // Example dataset: 2D points for binary classification
    Sample data[MAX_SAMPLES] = {
        {{2.0, 3.0}, 1},
        {{1.0, 1.0}, -1},
        {{2.0, 1.0}, 1},
        {{0.0, 1.0}, -1}
    };
    int num_samples = 4;

    // Initialize weights and bias
    double weights[MAX_FEATURES] = {0.0, 0.0};
    double bias = 0.0;

    // Train the SVM
    train_svm(data, num_samples, weights, &bias);

    // Print the trained weights and bias
    printf("Trained weights: [%.4f, %.4f]\n", weights[0], weights[1]);
    printf("Trained bias: %.4f\n", bias);

    // Test prediction
    double test_point[MAX_FEATURES] = {1.5, 2.0};
    int label = predict(test_point, weights, bias);
    printf("Prediction for point [1.5, 2.0]: %d\n", label);

    return 0;
}
