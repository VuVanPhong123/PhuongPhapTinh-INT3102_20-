#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

// Define the functions for each problem
double f_a(double t, double y) {
    return t * std::exp(3 * t) - 2 * y;
}

double f_b(double t, double y) {
    return 1 + std::pow(t - y, 2);
}

double f_c(double t, double y) {
    return 1 + y / t;
}

double f_d(double t, double y) {
    return std::cos(2 * t) + std::sin(3 * t);
}

double exact_solution_a(double t) {
    return (1.0 / 5) * t * std::exp(3 * t) - (1.0 / 25) * std::exp(3 * t) + (1.0 / 25) * std::exp(-2 * t);
}

double exact_solution_b(double t) {
    return t + 1.0 / (1 - t);
}

double exact_solution_c(double t) {
    return t * std::log(t) + 2 * t;
}

double exact_solution_d(double t) {
    return (1.0 / 2) * std::sin(2 * t) - (1.0 / 3) * std::cos(3 * t) + (4.0 / 3);
}

// Heun's method implementation
void heuns_method(double (*f)(double, double), double y0, double t0, double h, int steps, std::vector<double>& t_values, std::vector<double>& y_values) {
    double t = t0;
    double y = y0;
    t_values.push_back(t);
    y_values.push_back(y);

    for (int i = 0; i < steps; ++i) {
        double y_pred = y + h * f(t, y);
        double t_next = t + h;
        y = y + (h / 2) * (f(t, y) + f(t_next, y_pred));
        t = t_next;
        t_values.push_back(t);
        y_values.push_back(y);
    }
}

int main() {
    std::cout << std::fixed << std::setprecision(5);

    // Part (a)
    std::vector<double> t_values_a, y_values_a, exact_y_values_a;
    heuns_method(f_a, 0.0, 0.0, 0.5, 2, t_values_a, y_values_a);
    for (double t : t_values_a) {
        exact_y_values_a.push_back(exact_solution_a(t));
    }
    std::cout << "Heun's Method (Problem a):" << std::endl;
    for (size_t i = 0; i < t_values_a.size(); ++i) {
        std::cout << "t = " << t_values_a[i] << ", Approx y = " << y_values_a[i] << ", Exact y = " << exact_y_values_a[i] << ", Error = " << std::abs(exact_y_values_a[i] - y_values_a[i]) << std::endl;
    }

    // Part (b)
    std::vector<double> t_values_b, y_values_b, exact_y_values_b;
    heuns_method(f_b, 1.0, 2.0, 0.5, 2, t_values_b, y_values_b);
    for (double t : t_values_b) {
        exact_y_values_b.push_back(exact_solution_b(t));
    }
    std::cout << "\nHeun's Method (Problem b):" << std::endl;
    for (size_t i = 0; i < t_values_b.size(); ++i) {
        std::cout << "t = " << t_values_b[i] << ", Approx y = " << y_values_b[i] << ", Exact y = " << exact_y_values_b[i] << ", Error = " << std::abs(exact_y_values_b[i] - y_values_b[i]) << std::endl;
    }

    // Part (c)
    std::vector<double> t_values_c, y_values_c, exact_y_values_c;
    heuns_method(f_c, 2.0, 1.0, 0.25, 4, t_values_c, y_values_c);
    for (double t : t_values_c) {
        exact_y_values_c.push_back(exact_solution_c(t));
    }
    std::cout << "\nHeun's Method (Problem c):" << std::endl;
    for (size_t i = 0; i < t_values_c.size(); ++i) {
        std::cout << "t = " << t_values_c[i] << ", Approx y = " << y_values_c[i] << ", Exact y = " << exact_y_values_c[i] << ", Error = " << std::abs(exact_y_values_c[i] - y_values_c[i]) << std::endl;
    }

    // Part (d)
    std::vector<double> t_values_d, y_values_d, exact_y_values_d;
    heuns_method(f_d, 1.0, 0.0, 0.25, 4, t_values_d, y_values_d);
    for (double t : t_values_d) {
        exact_y_values_d.push_back(exact_solution_d(t));
    }
    std::cout << "\nHeun's Method (Problem d):" << std::endl;
    for (size_t i = 0; i < t_values_d.size(); ++i) {
        std::cout << "t = " << t_values_d[i] << ", Approx y = " << y_values_d[i] << ", Exact y = " << exact_y_values_d[i] << ", Error = " << std::abs(exact_y_values_d[i] - y_values_d[i]) << std::endl;
    }

    return 0;
}
