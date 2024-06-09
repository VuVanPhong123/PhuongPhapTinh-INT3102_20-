#include <iostream>
#include <vector>
#include <iomanip>

// Define the functions for the system of differential equations
double dx1dt(double x1, double x2, double k1, double k2) {
    return k1 * x1 - k2 * x1 * x2;
}

double dx2dt(double x1, double x2, double k3, double k4) {
    return k3 * x1 * x2 - k4 * x2;
}

// Implement the Runge-Kutta method of order 4 (RK4)
void runge_kutta_4(double (*f1)(double, double, double, double), double (*f2)(double, double, double, double),
                   double& x1, double& x2, double t, double h, double k1, double k2, double k3, double k4) {
    double k1_1 = h * f1(x1, x2, k1, k2);
    double k1_2 = h * f2(x1, x2, k3, k4);

    double k2_1 = h * f1(x1 + k1_1 / 2, x2 + k1_2 / 2, k1, k2);
    double k2_2 = h * f2(x1 + k1_1 / 2, x2 + k1_2 / 2, k3, k4);

    double k3_1 = h * f1(x1 + k2_1 / 2, x2 + k2_2 / 2, k1, k2);
    double k3_2 = h * f2(x1 + k2_1 / 2, x2 + k2_2 / 2, k3, k4);

    double k4_1 = h * f1(x1 + k3_1, x2 + k3_2, k1, k2);
    double k4_2 = h * f2(x1 + k3_1, x2 + k3_2, k3, k4);

    x1 = x1 + (k1_1 + 2 * k2_1 + 2 * k3_1 + k4_1) / 6;
    x2 = x2 + (k1_2 + 2 * k2_2 + 2 * k3_2 + k4_2) / 6;
}

int main() {
    // Constants
    const double k1 = 3.0;
    const double k2 = 0.002;
    const double k3 = 0.0006;
    const double k4 = 0.5;

    // Initial conditions
    double x1 = 1000;
    double x2 = 500;
    double t = 0.0;
    double t_final = 4.0;
    double h = 0.01; // Time step

    int steps = static_cast<int>(t_final / h);

    // Vectors to store results
    std::vector<double> t_values;
    std::vector<double> x1_values;
    std::vector<double> x2_values;

    // Store initial values
    t_values.push_back(t);
    x1_values.push_back(x1);
    x2_values.push_back(x2);

    // Perform RK4 for multiple steps
    for (int i = 0; i < steps; ++i) {
        runge_kutta_4(dx1dt, dx2dt, x1, x2, t, h, k1, k2, k3, k4);
        t += h;
        t_values.push_back(t);
        x1_values.push_back(x1);
        x2_values.push_back(x2);
    }

    // Print results
    std::cout << std::fixed << std::setprecision(5);
    std::cout << "Time\tPrey (x1)\tPredator (x2)" << std::endl;
    for (size_t i = 0; i < t_values.size(); ++i) {
        std::cout << t_values[i] << "\t" << x1_values[i] << "\t" << x2_values[i] << std::endl;
    }

    return 0;
}
