#include <iostream>
#include <cmath>
#include <iomanip>

// Define the differential equation dx/dt
double dxdt(double x, double k, double n1, double n2, double n3) {
    double term1 = n1 - x / 2.0;
    double term2 = n2 - x / 2.0;
    double term3 = n3 - 3.0 * x / 4.0;

    if (term1 < 0 || term2 < 0 || term3 < 0) {
        std::cerr << "Negative term encountered, which is invalid for this reaction." << std::endl;
        return 0;
    }

    return k * pow(term1, 2) * pow(term2, 2) * pow(term3, 3);
}

// Implement the Runge-Kutta method of order 4 (RK4)
double runge_kutta_4(double (*f)(double, double, double, double, double), double x0, double t0, double h, double k, double n1, double n2, double n3) {
    double k1 = h * f(x0, k, n1, n2, n3);
    double k2 = h * f(x0 + k1 / 2.0, k, n1, n2, n3);
    double k3 = h * f(x0 + k2 / 2.0, k, n1, n2, n3);
    double k4 = h * f(x0 + k3, k, n1, n2, n3);

    std::cout << "k1 = " << k1 << ", k2 = " << k2 << ", k3 = " << k3 << ", k4 = " << k4 << std::endl;

    return x0 + (k1 + 2 * k2 + 2 * k3 + k4) / 6.0;
}

int main() {
    // Constants
    const double k = 6.22e-19;
    const double n1 = 2000;
    const double n2 = 2000;
    const double n3 = 3000;

    // Initial conditions
    double x0 = 0;
    double t0 = 0;
    double t_final = 0.2;
    double h = 0.1; // Time step, reduced to 0.1 for better accuracy

    int steps = static_cast<int>(t_final / h);
    double x = x0;
    double t = t0;

    // Perform RK4 for multiple steps
    for (int i = 0; i < steps; ++i) {
        x = runge_kutta_4(dxdt, x, t, h, k, n1, n2, n3);
        t += h;

        std::cout << "After step " << i + 1 << ": t = " << t << ", x = " << x << std::endl;
    }

    // Output the final result
    std::cout << std::fixed << std::setprecision(10);
    std::cout << "After " << t_final << " seconds, the amount of KOH formed is approximately: " << x << " units." << std::endl;

    return 0;
}
