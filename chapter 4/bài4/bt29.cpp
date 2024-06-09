#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

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
    vector<double> time = {0, 3, 5, 8, 13};
    vector<double> distance = {0, 225, 383, 623, 993};
    vector<double> speed = {75, 77, 80, 74, 72}; // in ft/s

    // Convert speed from ft/s to mi/h for speed limit checking
    double speed_limit = 55 * 5280 / 3600; // 55 mi/h in ft/s

    // Derivative at the endpoints
    double f_prime0 = speed[0];
    double f_primeN = speed[speed.size() - 1];

    vector<double> a, b, c, d;
    int n = time.size();
    a.resize(n - 1);
    b.resize(n - 1);
    c.resize(n - 1);
    d.resize(n - 1);

    // Construct clamped cubic spline for distance
    clampedCubicSpline(time, distance, a, b, c, d, f_prime0, f_primeN);

    // Part (a): Predict the position and speed at t = 10 s
    double t = 10;
    double position = evaluateSpline(a, b, c, d, time, t);
    double speed_at_t = evaluateSpline(a, b, c, d, time, t, true);

    cout << fixed << setprecision(5);
    cout << "Position at t = 10 s: " << position << " ft" << endl;
    cout << "Speed at t = 10 s: " << speed_at_t << " ft/s" << endl;

    // Part (b): Check if the car exceeds the speed limit
    bool exceeds_speed_limit = false;
    double time_exceeding_limit = -1;
    for (double t = time[0]; t <= time[n - 1]; t += 0.01) {
        double current_speed = evaluateSpline(a, b, c, d, time, t, true);
        if (current_speed > speed_limit) {
            exceeds_speed_limit = true;
            time_exceeding_limit = t;
            break;
        }
    }

    if (exceeds_speed_limit) {
        cout << "The car exceeds the speed limit of 55 mi/h at t = " << time_exceeding_limit << " s" << endl;
    } else {
        cout << "The car does not exceed the speed limit of 55 mi/h." << endl;
    }

    // Part (c): Find the predicted maximum speed
    double max_speed = -1;
    for (double t = time[0]; t <= time[n - 1]; t += 0.01) {
        double current_speed = evaluateSpline(a, b, c, d, time, t, true);
        if (current_speed > max_speed) {
            max_speed = current_speed;
        }
    }

    cout << "Predicted maximum speed: " << max_speed << " ft/s" << endl;

    return 0;
}
