#include <iostream>
#include <utility>
#include <iomanip>
#include "matrix.h"

using namespace std;

// makes a new matrix array
int **makeMatrixArr(int rows, int cols) {
    int **m = new int* [rows];
    for (int i = 0; i < rows; ++i) {
        m[i] = new int[cols];
    }
    return m;
}

// makes stolen matrices
void Matrix::zeroMaker(Matrix &zeroM) {
    for (int r = 0; r < zeroM.nrows; ++r) {
        delete[] zeroM.m[r];
    }
    delete[] zeroM.m;
    zeroM.nrows = 1;
    zeroM.ncols = 1;
    zeroM.m = new int* [1];
    zeroM.m[0] = new int[1];
    zeroM.m[0][0] = 0;
}

// swaps matrices
void Matrix::swap(Matrix &other) {
    using std::swap;
    swap(m, other.m);
    swap(nrows, other.nrows);
    swap(ncols, other.ncols);
}

// Matrix Constructor
Matrix::Matrix(int numRows, int numCols) {
    m = makeMatrixArr(numRows, numCols);
    nrows = numRows;
    ncols = numCols;
}

// Matrix Destructor
Matrix::~Matrix() {
    for (int r = 0; r < this->nrows; ++r) {
        delete[] this->m[r];
    }
    delete[] this->m;
}

// Gets total rows
int Matrix::rows() const { // returns the number of rows in the matrix
    return this->nrows;
}

// Gets total columns
int Matrix::cols() const { // returns the number of columns in the matrix
    return this->ncols;
}

// Matrix Copy Constructor
Matrix::Matrix(const Matrix &copy): nrows{copy.nrows}, ncols{copy.ncols} {
    m = makeMatrixArr(nrows, ncols);
    for (int i = 0; i < nrows; ++i) {
        for (int j = 0; j < ncols; ++j) {
            m[i][j] = copy.m[i][j];
        }
    }
}

// Matrix Copy Assignment Operator
Matrix &Matrix::operator=(const Matrix &other) {
    Matrix copy{other};
    swap(copy);
    return *this;
}

int Matrix::get(int row, int col) const{
    return m[row][col];
}
void Matrix::set(int row, int col, int value) {
    m[row][col] = value;
}

// Matrix Move Constructor
Matrix::Matrix(Matrix &&moved): nrows{moved.nrows}, ncols{moved.ncols} {
    m = makeMatrixArr(nrows, ncols);
    for (int i = 0; i < nrows; ++i) {
        for (int j = 0; j < ncols; ++j) {
            m[i][j] = moved.m[i][j];
        }
    }
    zeroMaker(moved);
}

//Matrix Move Assignment Operator
Matrix &Matrix::operator=(Matrix &&other) {
    swap(other);
    zeroMaker(other);
    return *this;
}

// Overloaded + to handle Matrix addition 
Matrix Matrix::operator+(const Matrix &m2) const {
    Matrix* sumM = new Matrix(nrows, ncols);
    for (int i = 0; i < nrows; ++i) {
        for (int j = 0; j < ncols; ++j) {
            sumM->m[i][j] = m[i][j] + m2.m[i][j];
        }
    }
    return *sumM;
}

// Overloaded * to handle Matrix multiplication 
Matrix Matrix::operator*(const Matrix &m2) const {
    Matrix* multM = new Matrix(nrows, ncols);
    for (int i = 0; i < nrows; ++i) {
        for (int j = 0; j < ncols; ++j) {
            for (int x = 0; x < nrows; ++x) {
                multM->m[i][j] += m[i][x] * m2.m[x][j];
            } 
        }
    }
    return *multM;
}

// overloaded >> to use standard input to create a Matrix 
istream &operator>>(std::istream &in, Matrix &mat) {
    in >> mat.nrows;
    in >> mat.ncols;
    for (int r = 0; r < mat.nrows; ++r) {
        delete[] mat.m[r];
    }
    delete[] mat.m;
    mat.m = makeMatrixArr(mat.nrows, mat.ncols);
    for (int i = 0; i < mat.nrows; ++i) {
        for (int j = 0; j < mat.ncols; ++j) {
            in >> mat.m[i][j];
        }
    }
    return in;
}

// overloaded << to output Matrix to standard output 
ostream &operator<<(std::ostream &out, const Matrix &mat) {
    for (int i = 0; i < mat.nrows; ++i) {
        for (int j = 0; j < mat.ncols; ++j) {
            if (j == mat.ncols-1) {
                out << setw(4) << mat.m[i][j] << " ";
            } else {
                out << setw(4) << mat.m[i][j] << " ";
            }
        }
        out << endl;
    }
    return out;
}
