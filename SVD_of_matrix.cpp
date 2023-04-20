#include <iostream>
#include <Eigen/Dense>  // Using Eigen library for matrix computations

using namespace Eigen;
using namespace std;

int main()
{
    MatrixXd A(2,3);  // Define matrix A
    A << 3, 2, 2,
         2, 3, -2;
    cout << "Input matrix A:\n" << A << endl << endl;  // Output input matrix A
    
    JacobiSVD<MatrixXd> svd(A, ComputeThinU | ComputeThinV);  // Compute SVD of A
    MatrixXd U = svd.matrixU();  // Get left singular vectors
    MatrixXd V = svd.matrixV();  // Get right singular vectors
    VectorXd S = svd.singularValues();  // Get singular values
    
    cout << "U:\n" << U << endl << endl;  // Output left singular vectors
    cout << "Singular values:\n" << S << endl << endl;  // Output singular values
    cout << "V:\n" << V << endl << endl;  // Output right singular vectors
    
    // Verify decomposition by computing A = U*S*V'
    MatrixXd US = U * S.asDiagonal();  // Compute U*S
    MatrixXd AV = A * V;  // Compute A*V
    MatrixXd USVt = US * V.transpose();  // Compute U*S*V'
    cout << "Reconstruction error (A - U*S*V'):\n" << A - USVt << endl;  // Output reconstruction error
    
    return 0;
}
