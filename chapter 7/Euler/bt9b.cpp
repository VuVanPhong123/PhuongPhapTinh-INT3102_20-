#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

double linear_interpolate(const std::vector<double>& t_values, const std::vector<double>& y_values, double t) {
    for (size_t i = 0; i < t_values.size() - 1; ++i) {
        if (t_values[i] <= t && t <= t_values[i + 1]) {
            double t0 = t_values[i], t1 = t_values[i + 1];
            double y0 = y_values[i], y1 = y_values[i + 1];
            return y0 + (y1 - y0) * (t - t0) / (t1 - t0);
        }
    }
    return 0.0; // t is out of range
}

double exact_solution(double t) {
    return t * t * (std::exp(t) - std::exp(1));
}

int main() {
    std::vector<double> t_values = {1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0};
    std::vector<double> y_values = {0.0, 0.27183, 0.61716, 1.04156, 1.55088, 2.15121, 2.84893, 3.65069, 4.56341, 5.59426, 6.75068}; // From part (a)

    std::vector<double> t_interpolate = {1.04, 1.55, 1.97};

    std::cout << "\nLinear Interpolation:" << std::endl;
    for (double t : t_interpolate) {
        double y_approx = linear_interpolate(t_values, y_values, t);
        double y_exact = exact_solution(t);
        std::cout << "t = " << t << ", Linear Approx y = " << y_approx << ", Exact y = " << y_exact << ", Error = " << std::abs(y_exact - y_approx) << std::endl;
    }

    return 0;
}
