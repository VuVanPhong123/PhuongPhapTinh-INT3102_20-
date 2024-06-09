#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

// Function to perform cubic Hermite interpolation
double cubic_hermite_interpolate(const std::vector<double>& t_values, const std::vector<double>& y_values, const std::vector<double>& y_t_values, double t) {
    for (size_t i = 0; i < t_values.size() - 1; ++i) {
        if (t_values[i] <= t && t <= t_values[i + 1]) {
            double t0 = t_values[i], t1 = t_values[i + 1];
            double y0 = y_values[i], y1 = y_values[i + 1];
            double y0_t = y_t_values[i], y1_t = y_t_values[i + 1];

            double h = t1 - t0;
            double s = (t - t0) / h;

            double h00 = (1 + 2 * s) * (1 - s) * (1 - s);
            double h10 = s * (1 - s) * (1 - s);
            double h01 = s * s * (3 - 2 * s);
            double h11 = s * s * (s - 1);

            return h00 * y0 + h10 * h * y0_t + h01 * y1 + h11 * h * y1_t;
        }
    }
    return 0.0; // t is out of range
}

int main() {
    std::vector<double> t_values = {1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0};
    std::vector<double> y_values = {0.0, 0.31213, 0.69033, 1.13643, 1.65417, 2.24626, 2.91535, 3.66403, 4.49482, 5.41022, 6.41262}; // From part (c)
    std::vector<double> y_t_values = {2.71828, 3.00416, 3.32947, 3.69783, 4.11320, 4.57987, 5.10243, 5.68578, 6.33516, 7.05612, 7.85458}; // Derivatives from part (c)
    std::vector<double> exact_y_values;

    // Calculate exact values for comparison
    for (double t : t_values) {
        exact_y_values.push_back(t * t * (exp(t) - exp(1)));
    }

    std::vector<double> t_interpolate = {1.04, 1.55, 1.97};

    std::cout << "\nCubic Hermite Interpolation:" << std::endl;
    for (double t : t_interpolate) {
        double y_approx = cubic_hermite_interpolate(t_values, y_values, y_t_values, t);
        double y_exact = t * t * (exp(t) - exp(1));
        std::cout << "t = " << t << ", Cubic Hermite Approx y = " << y_approx << ", Exact y = " << y_exact << ", Error = " << fabs(y_exact - y_approx) << std::endl;
    }

    return 0;
}
