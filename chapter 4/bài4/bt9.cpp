#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

// Function to construct the natural cubic spline
void naturalCubicSpline(const vector<double>& x, const vector<double>& y, vector<double>& a, vector<double>& b, vector<double>& c, vector<double>& d) {
    int n = x.size() - 1;
    vector<double> h(n), alpha(n), l(n + 1), mu(n + 1), z(n + 1);

    for (int i = 0; i < n; i++) {
        h[i] = x[i + 1] - x[i];
    }

    for (int i = 1; i < n; i++) {
        alpha[i] = (3 / h[i]) * (y[i + 1] - y[i]) - (3 / h[i - 1]) * (y[i] - y[i - 1]);
    }

    l[0] = 1;
    mu[0] = 0;
    z[0] = 0;

    for (int i = 1; i < n; i++) {
        l[i] = 2 * (x[i + 1] - x[i - 1]) - h[i - 1] * mu[i - 1];
        mu[i] = h[i] / l[i];
        z[i] = (alpha[i] - h[i - 1] * z[i - 1]) / l[i];
    }

    l[n] = 1;
    z[n] = 0;
    c[n] = 0;

    for (int j = n - 1; j >= 0; j--) {
        c[j] = z[j] - mu[j] * c[j + 1];
        b[j] = (y[j + 1] - y[j]) / h[j] - h[j] * (c[j + 1] + 2 * c[j]) / 3;
        d[j] = (c[j + 1] - c[j]) / (3 * h[j]);
        a[j] = y[j];
    }
}

// Function to construct the clamped cubic spline
void clampedCubicSpline(const vector<double>& x, const vector<double>& y, vector<double>& a, vector<double>& b, vector<double>& c, vector<double>& d, double f_prime0, double f_primeN) {
    int n = x.size() - 1;
    vector<double> h(n), alpha(n + 1), l(n + 1), mu(n + 1), z(n + 1);

    for (int i = 0; i < n; i++) {
        h[i] = x[i + 1] - x[i];
    }

    alpha[0] = 3 * (y[1] - y[0]) / h[0] - 3 * f_prime0;
    alpha[n] = 3 * f_primeN - 3 * (y[n] - y[n - 1]) / h[n - 1];

    for (int i = 1; i < n; i++) {
        alpha[i] = (3 / h[i]) * (y[i + 1] - y[i]) - (3 / h[i - 1]) * (y[i] - y[i - 1]);
    }

    l[0] = 2 * h[0];
    mu[0] = 0.5;
    z[0] = alpha[0] / l[0];

    for (int i = 1; i < n; i++) {
        l[i] = 2 * (x[i + 1] - x[i - 1]) - h[i - 1] * mu[i - 1];
        mu[i] = h[i] / l[i];
        z[i] = (alpha[i] - h[i - 1] * z[i - 1]) / l[i];
    }

    l[n] = h[n - 1] * (2 - mu[n - 1]);
    z[n] = (alpha[n] - h[n - 1] * z[n - 1]) / l[n];
    c[n] = z[n];

    for (int j = n - 1; j >= 0; j--) {
        c[j] = z[j] - mu[j] * c[j + 1];
        b[j] = (y[j + 1] - y[j]) / h[j] - h[j] * (c[j + 1] + 2 * c[j]) / 3;
        d[j] = (c[j + 1] - c[j]) / (3 * h[j]);
        a[j] = y[j];
    }
}

// Function to evaluate the spline and its derivative
double evaluateSpline(const vector<double>& a, const vector<double>& b, const vector<double>& c, const vector<double>& d, const vector<double>& x, double x_val, bool derivative = false) {
    int n = x.size() - 1;
    int i = n - 1;

    while (i >= 0) {
        if (x_val >= x[i]) break;
        i--;
    }

    double dx = x_val - x[i];
    if (derivative) {
        return b[i] + 2 * c[i] * dx + 3 * d[i] * dx * dx;
    } else {
        return a[i] + b[i] * dx + c[i] * dx * dx + d[i] * dx * dx * dx;
    }
}

int main() {
    vector<double> x1 = {8.3, 8.6};
    vector<double> y1 = {17.56492, 18.50515};

    vector<double> x2 = {0.8, 1.0};
    vector<double> y2 = {0.22363362, 0.65809197};

    vector<double> x3 = {-0.5, -0.25, 0};
    vector<double> y3 = {-0.0247500, 0.3349375, 1.1010000};

    vector<double> x4 = {0.1, 0.2, 0.3, 0.4};
    vector<double> y4 = {-0.62049958, -0.28398668, 0.00660095, 0.24842440};

    vector<vector<double>> xs = {x1, x2, x3, x4};
    vector<vector<double>> ys = {y1, y2, y3, y4};

    vector<double> a, b, c, d;

    // Natural cubic spline for each set of data
    for (int i = 0; i < xs.size(); i++) {
        int n = xs[i].size();
        a.resize(n - 1);
        b.resize(n - 1);
        c.resize(n - 1);
        d.resize(n - 1);

        naturalCubicSpline(xs[i], ys[i], a, b, c, d);

        // Print results for natural cubic spline
        cout << "Natural Cubic Spline coefficients for dataset " << i + 1 << ":\n";
        for (int j = 0; j < n - 1; j++) {
            cout << "Interval [" << xs[i][j] << ", " << xs[i][j + 1] << "]:\n";
            cout << "a = " << a[j] << ", b = " << b[j] << ", c = " << c[j] << ", d = " << d[j] << "\n";
        }
    }

    // Clamped cubic spline for each set of data
    vector<double> f_prime0 = {3.116256, 2.1691753, 0.7510000, 3.58502082};
    vector<double> f_primeN = {3.151762, 2.0466965, 4.0020000, 2.16529366};

    for (int i = 0; i < xs.size(); i++) {
        int n = xs[i].size();
        a.resize(n - 1);
        b.resize(n - 1);
        c.resize(n - 1);
        d.resize(n - 1);

        clampedCubicSpline(xs[i], ys[i], a, b, c, d, f_prime0[i], f_primeN[i]);

        // Print results for clamped cubic spline
        cout << "Clamped Cubic Spline coefficients for dataset " << i + 1 << ":\n";
        for (int j = 0; j < n - 1; j++) {
            cout << "Interval [" << xs[i][j] << ", " << xs[i][j + 1] << "]:\n";
            cout << "a = " << a[j] << ", b = " << b[j] << ", c = " << c[j] << ", d = " << d[j] << "\n";
        }
    }

    // Approximations using the natural cubic spline
    vector<double> x_vals = {8.4, 0.9, -1.0/3.0, 0.25};
    vector<double> actual_f = {8.4 * log(8.4), sin(exp(0.9) - 2), pow(-1.0/3.0, 3) + 4.001 * pow(-1.0/3.0, 2) + 4.002 * (-1.0/3.0) + 1.101, 0.25 * cos(0.25) - 2 * pow(0.25, 2) + 3 * 0.25 - 1};
    vector<double> actual_f_prime = {log(8.4) + 1, cos(exp(0.9) - 2) * exp(0.9), 3 * pow(-1.0/3.0, 2) + 2 * 4.001 * (-1.0/3.0) + 4.002, cos(0.25) - 4 * 0.25 + 3 - 0.25 * sin(0.25)};

    for (int i = 0; i < xs.size(); i++) {
        int n = xs[i].size();
        a.resize(n - 1);
        b.resize(n - 1);
        c.resize(n - 1);
        d.resize(n - 1);

        naturalCubicSpline(xs[i], ys[i], a, b, c, d);

        double approx_f = evaluateSpline(a, b, c, d, xs[i], x_vals[i]);
        double approx_f_prime = evaluateSpline(a, b, c, d, xs[i], x_vals[i], true);

        cout << "Natural Cubic Spline Approximation for f(" << x_vals[i] << "): " << approx_f << "\n";
        cout << "Actual f(" << x_vals[i] << "): " << actual_f[i] << "\n";
        cout << "Error: " << fabs(approx_f - actual_f[i]) << "\n";

        cout << "Natural Cubic Spline Approximation for f'(" << x_vals[i] << "): " << approx_f_prime << "\n";
        cout << "Actual f'(" << x_vals[i] << "): " << actual_f_prime[i] << "\n";
        cout << "Error: " << fabs(approx_f_prime - actual_f_prime[i]) << "\n";
    }

    // Approximations using the clamped cubic spline
    for (int i = 0; i < xs.size(); i++) {
        int n = xs[i].size();
        a.resize(n - 1);
        b.resize(n - 1);
        c.resize(n - 1);
        d.resize(n - 1);

        clampedCubicSpline(xs[i], ys[i], a, b, c, d, f_prime0[i], f_primeN[i]);

        double approx_f = evaluateSpline(a, b, c, d, xs[i], x_vals[i]);
        double approx_f_prime = evaluateSpline(a, b, c, d, xs[i], x_vals[i], true);

        cout << "Clamped Cubic Spline Approximation for f(" << x_vals[i] << "): " << approx_f << "\n";
        cout << "Actual f(" << x_vals[i] << "): " << actual_f[i] << "\n";
        cout << "Error: " << fabs(approx_f - actual_f[i]) << "\n";

        cout << "Clamped Cubic Spline Approximation for f'(" << x_vals[i] << "): " << approx_f_prime << "\n";
        cout << "Actual f'(" << x_vals[i] << "): " << actual_f_prime[i] << "\n";
        cout << "Error: " << fabs(approx_f_prime - actual_f_prime[i]) << "\n";
    }

    return 0;
}
