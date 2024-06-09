
#include<bits/stdc++.h>
using namespace std;

// Define the function f(x)
double f(double x) {
    return pow(3, 3*x + 1) - 7 * pow(5, 2*x);
}

// Define the derivative f'(x)
double df(double x) {
    return 3 * pow(3, 3*x+1) * log(3) - 14 * pow(5, 2*x) * log(5);
}

// Newton's method to find the root
void newtonsMethod(double p0, double TOL, int N0) {
    int i = 1;
    double p;

    while (i <= N0) {
        double fp0 = f(p0);
        double dfp0 = df(p0);

        if (dfp0 == 0) {
            cout << "The derivative is zero. No solution found." << std::endl;
            return;
        }

        p = p0 - fp0 / dfp0;

        if (fabs(p - p0) < TOL) {
            cout << "The procedure was successful. The root is: " << p << std::endl;
            return;
        }
        cout<<fixed<<setprecision(10)<<p<<endl;
        p0 = p;
        i++;
    }

    cout << "The method failed after " << N0 << " iterations." << std::endl;
}

int main() {
    // Initial approximation
    double p0 = 10.8;
    // Tolerance
    double TOL = 1e-10;
    // Maximum number of iterations
    int N0 = 100;

    newtonsMethod(p0, TOL, N0);

    return 0;
}
