#include<bits/stdc++.h>
using namespace std;

const double EPSILON = 1e-8;

void qr_decomposition(vector<vector<double>>& A, vector<vector<double>>& Q, vector<vector<double>>& R) {
    int n = A.size();
    Q = vector<vector<double>>(n, vector<double>(n, 0));
    R = vector<vector<double>>(n, vector<double>(n, 0));

    for (int k = 0; k < n - 1; k++) {
        for (int i = k + 1; i < n; i++) {
            double theta = atan2(A[i][k], A[k][k]);
            double c = cos(theta), s = sin(theta);
            for (int j = 0; j < n; j++) {
                double t = c * A[k][j] + s * A[i][j];
                A[i][j] = -s * A[k][j] + c * A[i][j];
                A[k][j] = t;
            }
            for (int j = k + 1; j < n; j++) {
                double t = c * R[k][j] + s * R[i][j];
                R[i][j] = -s * R[k][j] + c * R[i][j];
                R[k][j] = t;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        double norm = 0;
        for (int j = 0; j < n; j++) {
            norm += A[i][j] * A[i][j];
        }
        norm = sqrt(norm);
        for (int j = 0; j < n; j++) {
            Q[i][j] = A[i][j] / norm;
        }
        for (int j = i; j < n; j++) {
            R[i][j] = A[i][j];
        }
    }
}

int main() {
    // Define the input matrix A
    vector<vector<double>> A = {{10, 1, 1, 1}, {2, 10, 1, 1}, {1, 1, 10, 1}, {1, 1, 1, 10}};

    // Display the input matrix A
    cout << "Input matrix A:" << endl;
    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < A[i].size(); j++) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }

    // Compute the QR decomposition of A
    vector<vector<double>> Q, R;
    qr_decomposition(A, Q, R);

    // Display the resulting matrices Q and R
    cout << "Q = " << endl;
    for (int i = 0; i < Q.size(); i++) {
        for (int j = 0; j < Q[i].size(); j++) {
            cout << Q[i][j] << " ";
        }
        cout << endl;
    }

    cout << "R = " << endl;
    for (int i =    0; i < R.size(); i++) {
        for (int j = 0; j < R[i].size(); j++) {
            cout << R[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}

