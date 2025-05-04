#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int>> matrix;

matrix strassen_mult(matrix A, matrix B);
matrix add(const matrix &A, const matrix &B);
matrix sub(const matrix &A, const matrix &B);

int main() {

	matrix A = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};

	matrix B = {
	    {17, 18, 19, 20}, {21, 22, 23, 24}, {25, 26, 27, 28}, {29, 30, 31, 32}};

	matrix result = strassen_mult(A, B);

	for (int i = 0; i < result.size(); i++) {
		for (int j = 0; j < result[i].size(); j++) {
			cout << result[i][j] << " ";
		}
		cout << endl;
	}

	return 0;
}
matrix strassen_mult(matrix A, matrix B) {
	int n = A.size();
	if (n == 1)
		return {{A[0][0] * B[0][0]}};

	int mid = n / 2;

	matrix A11(mid, vector<int>(mid)), A12(mid, vector<int>(mid));
	matrix A21(mid, vector<int>(mid)), A22(mid, vector<int>(mid));
	matrix B11(mid, vector<int>(mid)), B12(mid, vector<int>(mid));
	matrix B21(mid, vector<int>(mid)), B22(mid, vector<int>(mid));

	for (int i = 0; i < mid; i++) {
		for (int j = 0; j < mid; j++) {
			A11[i][j] = A[i][j];
			A12[i][j] = A[i][j + mid];
			A21[i][j] = A[i + mid][j];
			A22[i][j] = A[i + mid][j + mid];
			B11[i][j] = B[i][j];
			B12[i][j] = B[i][j + mid];
			B21[i][j] = B[i + mid][j];
			B22[i][j] = B[i + mid][j + mid];
		}
	}

	matrix M1 = strassen_mult(add(A11, A22), add(B11, B22));
	matrix M2 = strassen_mult(add(A21, A22), B11);
	matrix M3 = strassen_mult(A11, sub(B12, B22));
	matrix M4 = strassen_mult(A22, sub(B21, B11));
	matrix M5 = strassen_mult(add(A11, A12), B22);
	matrix M6 = strassen_mult(sub(A21, A11), add(B11, B12));
	matrix M7 = strassen_mult(sub(A12, A22), add(B21, B22));

	matrix C(n, vector<int>(n));
	for (int i = 0; i < mid; i++) {
		for (int j = 0; j < mid; j++) {
			C[i][j] = M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];
			C[i][j + mid] = M3[i][j] + M5[i][j];
			C[i + mid][j] = M2[i][j] + M4[i][j];
			C[i + mid][j + mid] = M1[i][j] - M2[i][j] + M3[i][j] + M6[i][j];
		}
	}

	return C;
}

matrix add(const matrix &A, const matrix &B) {
	int n = A.size();
	matrix C(n, vector<int>(n));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			C[i][j] = A[i][j] + B[i][j];
	return C;
}

matrix sub(const matrix &A, const matrix &B) {
	int n = A.size();
	matrix C(n, vector<int>(n));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			C[i][j] = A[i][j] - B[i][j];
	return C;
}
