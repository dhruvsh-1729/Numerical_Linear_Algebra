#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int ROWS = 3;
const int COLS = 3;

void printMatrix(double matrix[ROWS][COLS]) {
    // Prints out the matrix
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

void printVector(double vector[], int size) {
    // Prints out the vector
    for(int i = 0; i < size; i++) {
        cout << vector[i] << endl;
    }
}

void partialPivoting(double matrix[ROWS][COLS], double vector[], int size) {
    // Implements partial pivoting to ensure stability of the algorithm
    for(int i = 0; i < size; i++) {
        // Find the pivot row
        int maxRow = i;
        for(int j = i+1; j < size; j++) {
            if(abs(matrix[j][i]) > abs(matrix[maxRow][i])) {
                maxRow = j;
            }
        }
        // Swap rows if necessary
        if(maxRow != i) {
            for(int j = 0; j < size; j++) {
                double temp = matrix[i][j];
                matrix[i][j] = matrix[maxRow][j];
                matrix[maxRow][j] = temp;
            }
            double temp = vector[i];
            vector[i] = vector[maxRow];
            vector[maxRow] = temp;
        }
    }
}

double findGrowthFactor(double matrix[ROWS][COLS], double vector[], int size) {
    // Implements the algorithm to find the growth factor with partial pivoting
    double maxEntry;
    double temp;
    double growthFactor = 1;
    for(int i = 0; i < size; i++) {
        maxEntry = 0;
        for(int j = 0; j < size; j++) {
            temp = abs(matrix[i][j]);
            if(temp > maxEntry) {
                maxEntry = temp;
            }
        }
        growthFactor = max(growthFactor, maxEntry);
    }
    return growthFactor;
}

int main() {
    // Define the input matrices
    double A[ROWS][COLS] = {{1, 2, 3}, {2, 3, 4}, {0, 5, 6}};
    double B[ROWS] = {6, 9, 11};
    // Print out the input matrices
    cout << "Matrix A:" << endl;
    printMatrix(A);
    cout << "Vector B:" << endl;
    printVector(B, ROWS);
    // Implement partial pivoting
    partialPivoting(A, B, ROWS);
    // Print out the pivoted matrices
    cout << "Matrix A after partial pivoting:" << endl;
    printMatrix(A);
    cout << "Vector B after partial pivoting:" << endl;
    printVector(B, ROWS);
    // Find the growth factor
    double growthFactor = findGrowthFactor(A, B, ROWS);
    // Print out the growth factor
    cout << "Growth factor with partial pivoting: " << growthFactor << endl;
    return 0;
}
