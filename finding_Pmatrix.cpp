#include <bits/stdc++.h>

using namespace std;

int main()
{
    // Define matrix A
    double A[3][3] = {{6, 4, -2},
                      {4, 12, -4},
                      {-2, -4, 13}};
    
    // Find the eigenvectors and eigenvalues of A
    double eigvals[3];
    double eigvecs[3][3];
    double eigvecs_transpose[3][3];
    
    // Find the eigenvectors and eigenvalues using the Eigen library
    // Replace this part with your own eigendecomposition algorithm if you don't have Eigen
    Eigen::Matrix3d A_eigen;
    A_eigen << 6, 4, -2,
               4, 12, -4,
               -2, -4, 13;
    Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> eigensolver(A_eigen);
    if (eigensolver.info() != Eigen::Success) {
        cout << "Eigendecomposition failed." << endl;
        return 1;
    }
    Eigen::VectorXd eigenvalues = eigensolver.eigenvalues();
    Eigen::MatrixXd eigenvectors = eigensolver.eigenvectors();
    
    // Convert Eigen matrix to raw arrays
    for (int i = 0; i < 3; i++) {
        eigvals[i] = eigenvalues(i);
        for (int j = 0; j < 3; j++) {
            eigvecs[i][j] = eigenvectors(j, i);
        }
    }
    
    // Calculate P from the eigenvectors
    double P[3][3];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            P[i][j] = eigvecs[i][j] / sqrt(eigvals[j]);
        }
    }
    
    // Calculate Ptranspose
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            eigvecs_transpose[i][j] = P[j][i];
        }
    }
    
    // Calculate Ptranspose*A*P
    double PAP[3][3];
    double I[3][3] = {{1, 0, 0},
                      {0, 1, 0},
                      {0, 0, 1}};
    double eps = 1e-10; // tolerance for rounding errors
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            PAP[i][j] = 0;
            for (int k = 0; k < 3; k++) {
                PAP[i][j] += eigvecs_transpose[i][k] * A[k][j];
            }
            PAP[i][j] = abs(PAP[i][j]) < eps ? 0 : PAP[i][j];
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            double diff =         abs(PAP[i][j] - I[i][j]);
        if (diff > eps) {
            cout << "Error: Ptranspose*A*P is not equal to I." << endl;
            return 1;
        }
    }
}

// Print out Ptranspose*A*P and P for verification
cout << "Ptranspose*A*P:" << endl;
for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
        cout << PAP[i][j] << " ";
    }
    cout << endl;
}
cout << endl;

cout << "P:" << endl;
for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
        cout << P[i][j] << " ";
    }
    cout << endl;
}

return 0;
}
