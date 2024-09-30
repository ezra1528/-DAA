#include <stdio.h>
#include <stdlib.h>

// Function to allocate memory for a matrix of size n x n
int **allocateMatrix(int n) {
    int **matrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        matrix[i] = (int *)malloc(n * sizeof(int));
    return matrix;
}

// Function to deallocate memory for a matrix of size n x n
void deallocateMatrix(int **matrix, int n) {
    for (int i = 0; i < n; i++)
        free(matrix[i]);
    free(matrix);
}

// Function to add two matrices
void addMatrix(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

// Function to subtract one matrix from another
void subtractMatrix(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

// Function to multiply two matrices using the standard method
void standardMatrixMultiply(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
}

// Function to divide a matrix into quarters
void divideMatrix(int **P, int **C, int row, int col, int n) {
    for (int i1 = 0, i2 = row; i1 < n; i1++, i2++)
        for (int j1 = 0, j2 = col; j1 < n; j1++, j2++)
            C[i1][j1] = P[i2][j2];
}

// Function to combine four matrices into a single matrix
void combineMatrix(int **C, int **P, int row, int col, int n) {
    for (int i1 = 0, i2 = row; i1 < n; i1++, i2++)
        for (int j1 = 0, j2 = col; j1 < n; j1++, j2++)
            C[i2][j2] = P[i1][j1];
}

// Function to multiply two matrices using the Strassen algorithm
void strassenMatrixMultiply(int **A, int **B, int **C, int n) {
    // Base case: if the matrices are of size 1x1
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    // Create submatrices
    int **A11 = allocateMatrix(n / 2);
    int **A12 = allocateMatrix(n / 2);
    int **A21 = allocateMatrix(n / 2);
    int **A22 = allocateMatrix(n / 2);
    int **B11 = allocateMatrix(n / 2);
    int **B12 = allocateMatrix(n / 2);
    int **B21 = allocateMatrix(n / 2);
    int **B22 = allocateMatrix(n / 2);

    int **C11 = allocateMatrix(n / 2);
    int **C12 = allocateMatrix(n / 2);
    int **C21 = allocateMatrix(n / 2);
    int **C22 = allocateMatrix(n / 2);

    int **P1 = allocateMatrix(n / 2);
    int **P2 = allocateMatrix(n / 2);
    int **P3 = allocateMatrix(n / 2);
    int **P4 = allocateMatrix(n / 2);
    int **P5 = allocateMatrix(n / 2);
    int **P6 = allocateMatrix(n / 2);
    int **P7 = allocateMatrix(n / 2);

    int **temp1 = allocateMatrix(n / 2);
    int **temp2 = allocateMatrix(n / 2);

    // Divide matrices A and B into submatrices
    divideMatrix(A, A11, 0, 0, n / 2);
    divideMatrix(A, A12, 0, n / 2, n / 2);
    divideMatrix(A, A21, n / 2, 0, n / 2);
    divideMatrix(A, A22, n / 2, n / 2, n / 2);
    divideMatrix(B, B11, 0, 0, n / 2);
    divideMatrix(B, B12, 0, n / 2, n / 2);
    divideMatrix(B, B21, n / 2, 0, n / 2);
    divideMatrix(B, B22, n / 2, n / 2, n / 2);

    // Compute seven products (P1, P2, ..., P7)
    addMatrix(A11, A22, temp1, n / 2); // A11 + A22
    addMatrix(B11, B22, temp2, n / 2); // B11 + B22
    strassenMatrixMultiply(temp1, temp2, P1, n / 2); // P1 = (A11 + A22) * (B11 + B22)

    addMatrix(A21, A22, temp1, n / 2); // A21 + A22
    strassenMatrixMultiply(temp1, B11, P2, n / 2); // P2 = (A21 + A22) * B11

    subtractMatrix(B12, B22, temp1, n / 2); // B12 - B22
    strassenMatrixMultiply(A11, temp1, P3, n / 2); // P3 = A11 * (B12 - B22)

    subtractMatrix(B21, B11, temp1, n / 2); // B21 - B11
    strassenMatrixMultiply(A22, temp1, P4, n / 2); // P4 = A22 * (B21 - B11)

    addMatrix(A11, A12, temp1, n / 2); // A11 + A12
    strassenMatrixMultiply(temp1, B22, P5, n / 2); // P5 = (A11 + A12) * B22

    subtractMatrix(A21, A11, temp1, n / 2); // A21 - A11
    addMatrix(B11, B12, temp2, n / 2); // B11 + B12
    strassenMatrixMultiply(temp1, temp2, P6, n / 2); // P6 = (A21 - A11) * (B11 + B12)

    subtractMatrix(A12, A22, temp1, n / 2); // A12 - A22
    addMatrix(B21, B22, temp2, n / 2); // B21 + B22
    strassenMatrixMultiply(temp1, temp2, P7, n / 2); // P7 = (A12 - A22) * (B21 + B22)

    // Compute submatrices C11, C12, C21, C22 using P1, P2, ..., P7
    addMatrix(P1, P4, temp1, n / 2); // P1 + P4
    subtractMatrix(temp1, P5, temp2, n / 2); // (P1 + P4) - P5
    addMatrix(temp2, P7, C11, n / 2); // (P1 + P4 - P5) + P7

    addMatrix(P3, P5, C12, n / 2); // P3 + P5

    addMatrix(P2, P4, C21, n / 2); // P2 + P4

    addMatrix(P1, P3, temp1, n / 2); // P1 + P3
    subtractMatrix(temp1, P2, temp2, n / 2); // (P1 + P3) - P2
    addMatrix(temp2, P6, C22, n / 2); // (P1 + P3 - P2) + P6

    // Combine submatrices C11, C12, C21, C22 into matrix C
    combineMatrix(C, C11, 0, 0, n / 2);
    combineMatrix(C, C12, 0, n / 2, n / 2);
    combineMatrix(C, C21, n / 2, 0, n / 2);
    combineMatrix(C, C22, n / 2, n / 2, n / 2);

    // Deallocate memory for submatrices and temporary matrices
    deallocateMatrix(A11, n / 2);
    deallocateMatrix(A12, n / 2);
    deallocateMatrix(A21, n / 2);
    deallocateMatrix(A22, n / 2);
    deallocateMatrix(B11, n / 2);
    deallocateMatrix(B12, n / 2);
    deallocateMatrix(B21, n / 2);
    deallocateMatrix(B22, n / 2);
    deallocateMatrix(C11, n / 2);
    deallocateMatrix(C12, n / 2);
    deallocateMatrix(C21, n / 2);
    deallocateMatrix(C22, n / 2);
    deallocateMatrix(P1, n / 2);
    deallocateMatrix(P2, n / 2);
    deallocateMatrix(P3, n / 2);
    deallocateMatrix(P4, n / 2);
    deallocateMatrix(P5, n / 2);
    deallocateMatrix(P6, n / 2);
    deallocateMatrix(P7, n / 2);
    deallocateMatrix(temp1, n / 2);
    deallocateMatrix(temp2, n / 2);
}

// Function to print a matrix
void printMatrix(int **matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
}

int main() {
    int n = 4; // Size of matrices
    int **A = allocateMatrix(n); // First matrix
    int **B = allocateMatrix(n); // Second matrix
    int **C = allocateMatrix(n); // Result matrix

    // Initialize matrices A and B
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            A[i][j] = i + j;
            B[i][j] = i - j;
        }

    printf("Matrix A:\n");
    printMatrix(A, n);
    printf("\nMatrix B:\n");
    printMatrix(B, n);

    // Multiply matrices A and B using the Strassen algorithm
    strassenMatrixMultiply(A, B, C, n);

    printf("\nResult Matrix (C = A * B):\n");
    printMatrix(C, n);

    // Deallocate memory for matrices
    deallocateMatrix(A, n);
    deallocateMatrix(B, n);
    deallocateMatrix(C, n);

    return 0;
}
