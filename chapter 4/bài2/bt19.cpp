#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// Hàm tính đa thức nội suy Lagrange tại một điểm x
double lagrangeInterpolation(const vector<double>& x, const vector<double>& y, double x_val) {
    int n = x.size();
    double result = 0.0;

    for (int i = 0; i < n; i++) {
        double term = y[i];
        for (int j = 0; j < n; j++) {
            if (j != i) {
                term *= (x_val - x[j]) / (x[i] - x[j]);
            }
        }
        result += term;
    }
    return result;
}

// Hàm tìm điểm cực trị (giá trị lớn nhất) của đa thức nội suy trong khoảng từ 0 đến 28
double findMaxValue(const vector<double>& x, const vector<double>& y, double start, double end, int num_points) {
    double max_val = -INFINITY;
    double step = (end - start) / num_points;

    for (int i = 0; i <= num_points; i++) {
        double x_val = start + i * step;
        double y_val = lagrangeInterpolation(x, y, x_val);
        if (y_val > max_val) {
            max_val = y_val;
        }
    }
    return max_val;
}

int main() {
    // Dữ liệu mẫu 1
    vector<double> days = {0, 6, 10, 13, 17, 20, 28};
    vector<double> weights_sample1 = {6.67, 17.33, 42.67, 37.33, 30.10, 29.31, 28.74};
    vector<double> weights_sample2 = {6.67, 16.11, 18.89, 15.00, 10.56, 9.44, 8.89};

    // Tìm trọng lượng trung bình tối đa gần đúng cho mỗi mẫu
    double max_weight_sample1 = findMaxValue(days, weights_sample1, 0, 28, 1000);
    double max_weight_sample2 = findMaxValue(days, weights_sample2, 0, 28, 1000);

    cout << "trong luong trung binh mau 1: " << max_weight_sample1 << " mg" << endl;
    cout << "trong luong trung binh mau 2: " << max_weight_sample2 << " mg" << endl;

    return 0;
}
