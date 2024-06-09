#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

// Define the function f and its partial derivative with respect to t
double f(double t, double y) {
    return (2/t) * y + t * t * exp(t);
}

double f_t(double t, double y) {
    return -2 * y / (t * t) + (2 * t + t * t) * exp(t);
}

double exact_solution(double t) {
    return t * t * (exp(t) - exp(1));
}

int main() {
    double h = 0.1;
    double t = 1.0;
    double y = 0.0;
    int steps = (2.0 - 1.0) / h;

    std::vector<double> t_values, y_values, exact_y_values;

    // Initial values
    t_values.push_back(t);
    y_values.push_back(y);
    exact_y_values.push_back(exact_solution(t));

    // Taylor's method of order two
    for (int i = 0; i < steps; ++i) {
        double y_t = f(t, y);
        double y_tt = f_t(t, y);
        y = y + h * y_t + (h * h / 2) * y_tt;
        t += h;
        t_values.push_back(t);
        y_values.push_back(y);
        exact_y_values.push_back(exact_solution(t));
    }

    // Print results
    std::cout << std::fixed << std::setprecision(5);
    std::cout << "Taylor's Method of Order Two:" << std::endl;
    for (size_t i = 0; i < t_values.size(); ++i) {
        std::cout << "t = " << t_values[i] << ", Approx y = " << y_values[i] << ", Exact y = " << exact_y_values[i] << ", Error = " << fabs(exact_y_values[i] - y_values[i]) << std::endl;
    }

    return 0;
}
