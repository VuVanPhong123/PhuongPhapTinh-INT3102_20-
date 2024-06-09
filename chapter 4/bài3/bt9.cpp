#include <iostream>
#include <vector>
#include <iomanip> // for std::setprecision

using namespace std;

// Function to create divided difference table
vector<vector<double>> dividedDifferenceTable(vector<double> x, vector<double> y) {
    int n = x.size();
    vector<vector<double>> F(n, vector<double>(n, 0.0));

    // Initialize the first column with y values
    for (int i = 0; i < n; i++) {
        F[i][0] = y[i];
    }

    // Compute the divided differences
    for (int j = 1; j < n; j++) {
        for (int i = 0; i < n - j; i++) {
            F[i][j] = (F[i + 1][j - 1] - F[i][j - 1]) / (x[i + j] - x[i]);
        }
    }

    return F;
}

// Function to evaluate Newton's polynomial using divided differences
double newtonPolynomial(vector<double> x, vector<vector<double>> F, double value) {
    double result = F[0][0];
    double product;

    for (int i = 1; i < x.size(); i++) {
        product = 1.0;
        for (int j = 0; j < i; j++) {
            product *= (value - x[j]);
        }
        result += F[0][i] * product;
    }

    return result;
}

// Function to approximate f(0.05) using Newton forward-difference formula
double newtonForwardApproximation(vector<double> x, vector<double> y, double value) {
    vector<vector<double>> F = dividedDifferenceTable(x, y);
    return newtonPolynomial(x, F, value);
}

// Function to approximate f(0.65) using Newton backward-difference formula
double newtonBackwardApproximation(vector<double> x, vector<double> y, double value) {
    int n = x.size();
    vector<vector<double>> F = dividedDifferenceTable(x, y);

    double result = F[n-1][0];
    double product;

    for (int i = 1; i < n; i++) {
        product = 1.0;
        for (int j = 0; j < i; j++) {
            product *= (value - x[n-1-j]);
        }
        result += F[n-1-i][i] * product;
    }

    return result;
}

// Main function to execute the tasks
int main() {
    vector<double> x = {0.0, 0.2, 0.4, 0.6, 0.8};
    vector<double> y = {1.00000, 1.22140, 1.49182, 1.82212, 2.22554};

    double value_forward = 0.05;
    double value_backward = 0.65;

    double approx_forward = newtonForwardApproximation(x, y, value_forward);
    double approx_backward = newtonBackwardApproximation(x, y, value_backward);

    cout << fixed << setprecision(5);
    cout << "Approximate value of f(0.05) using Newton forward-difference formula: " << approx_forward << endl;
    cout << "Approximate value of f(0.65) using Newton backward-difference formula: " << approx_backward << endl;

    return 0;
}
