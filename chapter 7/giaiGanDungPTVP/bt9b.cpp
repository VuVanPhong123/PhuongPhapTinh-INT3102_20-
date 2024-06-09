#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

// Function to compute the next w value using functional iteration
double g(double w, double wi, double wi1, double wi2, double h) {
    return wi + (h / 24) * (9 * std::exp(w) + 19 * std::exp(wi) - 5 * std::exp(wi1) + std::exp(wi2));
}

// Function to compute the derivative of g with respect to w
double g_prime(double w, double h) {
    return (h / 24) * 9 * std::exp(w);
}

// Exact solution function
double exact_solution(double t) {
    double et = 2.718281828459045 * t;  // e * t
    return 1 - std::log(1 - et);
}

int main() {
    double h = 0.01;
    int steps = 20;
    std::vector<double> w(steps + 1);

    try {
        // Exact starting values
        w[0] = exact_solution(0.0);
        w[1] = exact_solution(0.01);
        w[2] = exact_solution(0.02);
    } catch (const std::exception &e) {
        std::cerr << "Error in exact solution: " << e.what() << std::endl;
        return 1;
    }

    std::cout << std::fixed << std::setprecision(10);
    std::cout << "t\tw\n";
    std::cout << 0.00 << "\t" << w[0] << "\n";
    std::cout << 0.01 << "\t" << w[1] << "\n";
    std::cout << 0.02 << "\t" << w[2] << "\n";

    // Newton's method
    for (int i = 2; i < steps; ++i) {
        double wi = w[i];
        double wi1 = w[i - 1];
        double wi2 = w[i - 2];
        double w_next = wi; // Initial guess for w_next
        double w_prev = 0; // Previous value for convergence check
        double tol = 1e-10; // Tolerance for convergence

        for (int iter = 0; iter < 1000; ++iter) { // Iterate to find fixed point with a max iteration count
            double g_val = g(w_next, wi, wi1, wi2, h);
            double g_prime_val = g_prime(w_next, h);
            w_prev = w_next;
            w_next = w_next - (g_val - w_next) / (g_prime_val - 1);
            if (std::isnan(w_next) || std::isinf(w_next)) {
                std::cerr << "Numerical instability detected." << std::endl;
                return 1;
            }
            if (std::abs(w_next - w_prev) < tol) {
                break; // Converged
            }
        }

        if (std::isnan(w_next) || std::isinf(w_next)) {
            std::cerr << "Numerical instability detected." << std::endl;
            return 1;
        }

        w[i + 1] = w_next;
        std::cout << (i + 1) * h << "\t" << w[i + 1] << "\n";
    }

    return 0;
}
