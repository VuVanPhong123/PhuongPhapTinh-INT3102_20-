#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

double f(double t, double y) {
    return (2 / t) * y + t * t * std::exp(t);
}

double exact_solution(double t) {
    return t * t * (std::exp(t) - std::exp(1));
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

    // Euler's method
    for (int i = 0; i < steps; ++i) {
        y = y + h * f(t, y);
        t += h;
        t_values.push_back(t);
        y_values.push_back(y);
        exact_y_values.push_back(exact_solution(t));
    }

    // Print results
    std::cout << std::fixed << std::setprecision(5);
    std::cout << "Euler's Method:" << std::endl;
    for (size_t i = 0; i < t_values.size(); ++i) {
        std::cout << "t = " << t_values[i] << ", Approx y = " << y_values[i] << ", Exact y = " << exact_y_values[i] << ", Error = " << std::abs(exact_y_values[i] - y_values[i]) << std::endl;
    }

    return 0;
}
