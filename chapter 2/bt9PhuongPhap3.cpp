#include<bits/stdc++.h>
using namespace std;

// Function to perform the False Position Method
double false_position(function<double(double)> f, double p0, double p1, double tol, int N0) {
    double q0 = f(p0);
    double q1 = f(p1);
    if (q0 * q1 > 0) {
        cout << "The function must have opposite signs at the endpoints." << endl;
        return NAN;
    }

    int i = 2;
    double p, q;
    while (i <= N0) {
        p = p1 - q1 * (p1 - p0) / (q1 - q0);  // Compute the next approximation
        if (fabs(p - p1) < tol) {
            return p;  // If within tolerance, return the result
        }
        i++;
        q = f(p);
        if (q * q1 < 0) {
            p0 = p1;
            q0 = q1;
        }
        p1 = p;
        q1 = q;
    }

    cout << "Method failed after " << N0 << " iterations." << endl;
    return NAN;
}

// Define the functions for each problem
double f_a(double x) {
    return pow(x, 3) - 2 * pow(x, 2) - 5;
}

double f_b(double x) {
    return pow(x, 3) + 3 * pow(x, 2) - 1;
}

double f_c(double x) {
    return x - cos(x);
}

double f_d(double x) {
    return x - 0.8 - 0.2 * sin(x);
}

int main() {
    double tol = 1e-10;
    int N0 = 1000;

    // Problem a: x^3 - 2x^2 - 5 = 0, [1, 4]
    double root_a = false_position(f_a, 1.0, 4.0, tol, N0);
    cout <<fixed<<setprecision(10)<< "Root for problem a: " << root_a << endl;

    // Problem b: x^3 + 3x^2 - 1 = 0, [-3, -2]
    double root_b = false_position(f_b, -3.0, -2.0, tol, N0);
    cout <<fixed<<setprecision(10)<< "Root for problem b: " << root_b << endl;

    // Problem c: x - cos(x) = 0, [0, pi/2]
    double root_c = false_position(f_c, 0.0, M_PI_2, tol, N0);
    cout <<fixed<<setprecision(10)<< "Root for problem c: " << root_c << endl;

    // Problem d: x - 0.8 - 0.2 sin(x) = 0, [0, pi/2]
    double root_d = false_position(f_d, 0.0, M_PI_2, tol, N0);
    cout <<fixed<<setprecision(10)<< "Root for problem d: " << root_d << endl;

    return 0;
}
