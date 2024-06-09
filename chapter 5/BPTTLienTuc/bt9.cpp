#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <functional>

using namespace std;

double inner_product(function<double(double)> f, function<double(double)> g, double a, double b, int n = 1000) {
    double sum = 0.0;
    double h = (b - a) / n;
    for (int i = 0; i <= n; ++i) {
        double x = a + i * h;
        sum += f(x) * g(x) * (i == 0 || i == n ? 0.5 : 1);
    }
    return sum * h;
}

void gram_schmidt(const vector<function<double(double)>>& basis, vector<function<double(double)>>& orthogonal, double a, double b) {
    for (size_t i = 0; i < basis.size(); ++i) {
        auto f = basis[i];
        for (size_t j = 0; j < i; ++j) {
            auto g = orthogonal[j];
            double dot_fg = inner_product(f, g, a, b);
            double dot_gg = inner_product(g, g, a, b);
            double coeff = dot_fg / dot_gg;
            f = [=](double x) { return f(x) - coeff * g(x); };
        }
        orthogonal.push_back(f);
    }
}

vector<double> least_squares_coefficients(const vector<function<double(double)>>& orthogonal, function<double(double)> f, double a, double b) {
    vector<double> coefficients;
    for (const auto& phi : orthogonal) {
        double dot_fp = inner_product(f, phi, a, b);
        double dot_pp = inner_product(phi, phi, a, b);
        coefficients.push_back(dot_fp / dot_pp);
    }
    return coefficients;
}

int main() {
    // Define the interval and the function
    double a = 0.0, b = 1.0;
    auto f = [](double x) { return x * x + 3 * x + 2; };

    // Define the basis polynomials
    vector<function<double(double)>> basis = {
        [](double x) { return 1.0; },
        [](double x) { return x; },
        [](double x) { return x * x; },
        [](double x) { return x * x * x; }
    };

    // Perform the Gram-Schmidt process to orthogonalize the basis
    vector<function<double(double)>> orthogonal;
    gram_schmidt(basis, orthogonal, a, b);

    // Find the least squares coefficients
    auto coefficients = least_squares_coefficients(orthogonal, f, a, b);

    // Output the results
    cout << fixed << setprecision(5);
    cout << "Least squares polynomial approximation of degree 3 for f(x) = x^2 + 3x + 2 on [0, 1]:" << endl;
    for (size_t i = 0; i < coefficients.size(); ++i) {
        cout << "Coefficient of orthogonal polynomial phi_" << i << "(x): " << coefficients[i] << endl;
    }

    return 0;
}
