#include "linear_regression.h"


// Function to calculate the mean of an array
double _calculate_mean(double arr[], int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum / n;
}

// Function to calculate the slope (m) of the regression line
double _calculate_slope(double x[], double y[], int n) {
    double sum_xy = 0, sum_x = 0, sum_y = 0, sum_x_squared = 0;

    for (int i = 0; i < n; i++) {
        sum_xy += x[i] * y[i];
        sum_x += x[i];
        sum_y += y[i];
        sum_x_squared += x[i] * x[i];
    }

    return (n * sum_xy - sum_x * sum_y) / (n * sum_x_squared - sum_x * sum_x);
}

// Function to calculate the y-intercept (c) of the regression line
double _calculate_intercept(double x[], double y[], int n, double slope) {
    double mean_x = _calculate_mean(x, n);
    double mean_y = _calculate_mean(y, n);

    return mean_y - slope * mean_x;
}

// Function to predict the next value based on linear regression
double predict_next_value(double x[], double y[], int n, double next_x) {
    double slope = _calculate_slope(x, y, n);
    double intercept = _calculate_intercept(x, y, n, slope);

    return slope * next_x + intercept;
}