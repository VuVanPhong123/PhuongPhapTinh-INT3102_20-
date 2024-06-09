#include <iostream>
#include <vector>

using namespace std;

vector<double> calculate_derivatives(const vector<double>& x, const vector<double>& f) {
    vector<double> f_prime(x.size(), 0.0);
    int n = x.size();

    // Forward difference for the first point
    f_prime[0] = (f[1] - f[0]) / (x[1] - x[0]);

    // Central difference for interior points
    for (int i = 1; i < n - 1; ++i) {
        f_prime[i] = (f[i + 1] - f[i - 1]) / (x[i + 1] - x[i - 1]);
    }

    // Backward difference for the last point
    f_prime[n - 1] = (f[n - 1] - f[n - 2]) / (x[n - 1] - x[n - 2]);

    return f_prime;
}

int main() {
    // Table (a)
    vector<double> x_a = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
    vector<double> f_a = {-1.709847, -1.373823, -1.119214, -0.9160143, -0.7470223, -0.6015966};
    vector<double> f_prime_a = calculate_derivatives(x_a, f_a);

    cout << "Table (a) derivatives:" << endl;
    for (size_t i = 0; i < x_a.size(); ++i) {
        cout << "x = " << x_a[i] << ", f'(x) = " << f_prime_a[i] << endl;
    }

    // Table (b)
    vector<double> x_b = {-3.0, -2.8, -2.6, -2.4, -2.2, -2.0};
    vector<double> f_b = {9.367879, 8.233241, 7.180350, 6.209329, 5.320305, 4.513417};
    vector<double> f_prime_b = calculate_derivatives(x_b, f_b);

    cout << "Table (b) derivatives:" << endl;
    for (size_t i = 0; i < x_b.size(); ++i) {
        cout << "x = " << x_b[i] << ", f'(x) = " << f_prime_b[i] << endl;
    }

    return 0;
}
