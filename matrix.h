#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>

struct Matrix {
  // Requires numRows >= 1 && numCols >= 1.
  // allocate space and set values in 2-D array to 0--fill later using 
  // either operator>> or set().
  Matrix(int numRows = 1, int numCols = 1);
  Matrix(const Matrix &);
  Matrix(Matrix &&);
  ~Matrix();

  Matrix &operator=(const Matrix &);
  Matrix &operator=(Matrix &&);

  Matrix operator+(const Matrix &) const;
  Matrix operator*(const Matrix &) const;
	
  int rows() const; // returns the number of rows in the matrix
  int cols() const; // returns the number of columns in the matrix

  // Sets this's [row][col] == value
  void set(int row, int col, int value); 

  // Returns this's [row][col] 
  int get(int row, int col) const; 


  // Add fields and helper methods below
  // DO NOT MODIFY CODE ABOVE THIS LINE

  int **m;
  int nrows;
  int ncols;
  void swap(Matrix &other);
  void zeroMaker(Matrix &m);
  
};

std::istream &operator>>(std::istream &, Matrix &);
std::ostream &operator<<(std::ostream &, const Matrix &);
#endif
