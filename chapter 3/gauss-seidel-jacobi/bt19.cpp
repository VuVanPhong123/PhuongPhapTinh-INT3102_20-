#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Function to perform Gaussian elimination
vector<double> gauss(vector<vector<double>> augmented_matrix) {
    int n = augmented_matrix.size();
    for (int k = 0; k < n; k++) {
        // Find the row with the maximum element in column k
        int maxRow = k;
        for (int i = k + 1; i < n; i++) {
            if (fabs(augmented_matrix[i][k]) > fabs(augmented_matrix[maxRow][k])) {
                maxRow = i;
            }
        }

        // Swap the maximum row with the current row
        swap(augmented_matrix[k], augmented_matrix[maxRow]);

        // Check for singular matrix
        if (fabs(augmented_matrix[k][k]) < 1e-10) {
            cout << "No unique solution exists" << endl;
            return {};
        }

        // Eliminate the elements below the pivot
        for (int i = k + 1; i < n; i++) {
            double factor = augmented_matrix[i][k] / augmented_matrix[k][k];
            for (int j = k; j <= n; j++) {
                augmented_matrix[i][j] -= factor * augmented_matrix[k][j];
            }
        }
    }

    // Perform back substitution
    vector<double> x(n);
    for (int i = n - 1; i >= 0; i--) {
        x[i] = augmented_matrix[i][n] / augmented_matrix[i][i];
        for (int j = i - 1; j >= 0; j--) {
            augmented_matrix[j][n] -= augmented_matrix[j][i] * x[i];
        }
    }

    return x;
}

int main() {
    vector<vector<double>> augmented_matrix = {
        {10,1,1,6},
        {1,10,1,6},
        {1,1,10,6}
    };

    vector<double> solution = gauss(augmented_matrix);

    if (!solution.empty()) {
        cout << "Solution: ";
        for (double x : solution) {
            cout << x << " ";
        }
        cout << endl;
    }

    return 0;
}
