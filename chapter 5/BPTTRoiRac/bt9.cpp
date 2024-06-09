#include <iostream>
#include <vector>
#include <numeric> // For accumulate and inner_product
#include <fstream> // For file operations
#include <algorithm> // For min_element and max_element

using namespace std;

// Function to calculate the least squares line
void calculateLeastSquaresLine(const vector<double>& x, const vector<double>& y, double& slope, double& intercept) {
    int n = x.size();
    double sum_x = accumulate(x.begin(), x.end(), 0.0);
    double sum_y = accumulate(y.begin(), y.end(), 0.0);
    double sum_xy = inner_product(x.begin(), x.end(), y.begin(), 0.0);
    double sum_x2 = inner_product(x.begin(), x.end(), x.begin(), 0.0);

    slope = (n * sum_xy - sum_x * sum_y) / (n * sum_x2 - sum_x * sum_x);
    intercept = (sum_y * sum_x2 - sum_x * sum_xy) / (n * sum_x2 - sum_x * sum_x);
}

// Function to generate a data file for plotting
void generatePlotData(const vector<double>& x, const vector<double>& y, double slope, double intercept, const string& filename) {
    ofstream file(filename);
    if (!file) {
        cerr << "Error opening file " << filename << endl;
        return;
    }

    // Write the original data points
    file << "# ACT Score, GPA" << endl;
    for (size_t i = 0; i < x.size(); ++i) {
        file << x[i] << " " << y[i] << endl;
    }

    // Write the least squares line
    file << "# Least squares line" << endl;
    double x_min = *min_element(x.begin(), x.end());
    double x_max = *max_element(x.begin(), x.end());
    file << x_min << " " << slope * x_min + intercept << endl;
    file << x_max << " " << slope * x_max + intercept << endl;

    file.close();
}

int main() {
    vector<double> act_scores = {28, 25, 28, 27, 28, 33, 28, 29, 23, 27, 29, 28, 27, 29, 21, 28, 28, 26, 30, 24};
    vector<double> gpas = {3.84, 3.21, 3.23, 3.63, 3.75, 3.20, 3.41, 3.38, 3.53, 2.03, 3.75, 3.65, 3.87, 3.75, 1.66, 3.12, 2.96, 2.92, 3.10, 2.81};

    double slope, intercept;
    calculateLeastSquaresLine(act_scores, gpas, slope, intercept);

    cout << "Equation of the least squares line: y = " << slope << "x + " << intercept << endl;

    // Generate plot data
    generatePlotData(act_scores, gpas, slope, intercept, "plot_data.txt");

    return 0;
}
