#include <iostream>
#include "matrix.h"

using namespace std;

//************************************************************************
//  Helper variables and functions for test harness
//************************************************************************

//  testharness operators
enum Op {NONE, CONSTRUCT, DELETE, COPY, MOVE, COPY_ASSIGN, MOVE_ASSIGN, READ, PRINT, SET, GET, ADD, MULT};

// converts a one-character input into its corresponding test harness operator
Op convertOp(string opStr) {
  switch (opStr[0]) {
   case 'c': return CONSTRUCT; 
   case 'C': return COPY;
   case 'd': return DELETE;
   case 'a': return COPY_ASSIGN;
   case 'A': return MOVE_ASSIGN;
   case 'r': return READ;
   case 'p': return PRINT;
   case 'm': return MOVE;
   case 's': return SET;
   case 'g': return GET;
   case '+': return ADD;
   case '*': return MULT;
   default: return NONE;
  }
}

// Reads a Matrix id (m#) from cin. 
int readName() {	
  char m;
  cin >> m;
  if ( m != 'm' ) {
    cerr << "Invalid name of Matrix variable.\n";
  }

  int index;
  cin >> index;
  return index;
}

// Read in the number of rows/columns
int readDimension(string dimensionDescription) {
  int dimension;
  cerr << "Enter number of " << dimensionDescription << " (>=1): ";
  cin >> dimension;
  return dimension;
}

// Given the Matrix object whose dimensions have been set, retrieve the dimensions and then read in the
// values from standard input.
void readMatrix(Matrix *matrix) {
  int numRows = matrix->rows();
  int numCols = matrix->cols();
  for (int i = 0; i < numRows; ++i) {
    for (int j = 0; j < numCols; ++j) {
      int value;
      cin >> value;
      matrix->set(i,j,value);
    }
  }
}

// Create a matrix using the constructor to set the dimensions, then read in the values from cin.
void buildMatrix(Matrix *matrices[]) {
  int index = readName();
  int numRows = readDimension("rows");
  int numCols = readDimension( "columns");
  delete matrices[index];
  matrices[index] = new Matrix(numRows, numCols);
  readMatrix(matrices[index]);
}

// Use operator>> to read in the matrix of values.
void readInMatrix(Matrix *matrices[]) {
  int index = readName();
  cerr << "Enter matrix dimensions (number of rows, number of columns) followed by values: ";
  delete matrices[index];
  matrices[index] = new Matrix();
  cin >> *(matrices[index]);
  cout << "Matrix m" << index << " =\n" << *(matrices[index]) << endl;
}

// Invoke the destructor on the matrix.
void deleteMatrix(Matrix *matrices[]) {
  int index = readName();
  delete matrices[index];
  matrices[index] = nullptr;
  cout << "Matrix m" << index << " deleted" << endl;
}

// Use operator<< to output the matrix.
void printMatrix(Matrix *matrices[]) {
  int index = readName();
  cout << "Matrix m" << index << " =\n" << *(matrices[index]) << endl;
}

// Use Matrix move constructor to move contents of one matrix to another, temporary matrix.
void moveMatrix(Matrix *matrices[]) {
  int index = readName();
  Matrix m(std::move(*matrices[index]));
  cout << "New Matrix =\n" << m << "\nm" << index << " =\n" << *(matrices[index]) << endl;
}

// Use Matrix copy constructor to copy contents of one matrix to another, temporary matrix.
void copyMatrix(Matrix *matrices[]) {
  int index = readName();
  Matrix m(*matrices[index]);
  cout << "New Matrix =\n" << m << "\nm" << index<< " =\n" << *(matrices[index]) << endl;
}

// Use Matrix copy assignment operator to copy contents of one matrix to another.
void copyAssignMatrix(Matrix *matrices[]) {
  int index1 = readName();
  int index2 = readName();
  *matrices[index1] = *matrices[index2];
  cout << "New Matrix =\n" << *(matrices[index1]) << "\nold Matrix =\n" << *(matrices[index2]) << endl;
}

// Use Matrix move assignment operator to move contents of one matrix to another.
void moveAssignMatrix(Matrix *matrices[]) {
  int index1 = readName();
  int index2 = readName();
  *matrices[index1] = std::move(*matrices[index2]);
  cout << "m" << index1 << " =\n" << *(matrices[index1]) << "\nm" << index2 << " =\n"  
    << *(matrices[index2]) << endl;
}

// Set m#[row][col] = value
void setMatrix(Matrix * matrices[]) {
  int index = readName();
  cerr << "Enter the row, column and value: ";
  int row, col, value;
  cin >> row >> col >> value;
  matrices[index]->set(row, col, value);
  cout << "m" << index << "[" << row << "][" << col << "] = " << value << endl;
}

// Get m#[row][col] 
void getMatrix(Matrix *matrices[]) {
  int index = readName();
  cerr << "Enter the row and column: ";
  int row, col;
  cin >> row >> col;
  cout << "m" << index << "[" << row << "][" << col << "] = " 
      << matrices[index]->get(row, col ) << endl;
}

void addMatrices(Matrix *matrices[]) {
  int index1 = readName();
  int index2 = readName();
  if (matrices[index1]->rows() != matrices[index2]->rows() || 
    matrices[index1]->cols() != matrices[index2]->cols()) {
    cerr << "Dimensions of m" << index1 << " != m" << index2 << endl;
    return;
  }
  Matrix m = *matrices[index1] + *matrices[index2];
  cout << "m" << index1 << " + m" << index2 << " =\n"  << m << endl;
}

void multMatrices(Matrix *matrices[]) {
  int index1 = readName();
  int index2 = readName();
  if (matrices[index1]->cols() != matrices[index2]->rows()) {
    cerr << "Dimensions of m" << index1 << " != m" << index2 << endl;
    return;
  }
  Matrix m = (*matrices[index1]) * (*matrices[index2]);
  cout << "m" << index1 << " * m" << index2 << " =\n"  << m << endl;
}

int main () {
  Matrix *matrices[10] = {nullptr};

  for (;;) {
    cerr << "Command: ";
    string command;
    if (!(cin >> command)) break;

    Op op = convertOp(command);

    switch(op) {
     case CONSTRUCT: 
      buildMatrix(matrices);
      break;
     case DELETE:
      deleteMatrix(matrices);
      break;
     case READ: 
      readInMatrix(matrices);
      break;
     case PRINT: 
      printMatrix(matrices);
      break;				
     case MOVE:
      moveMatrix(matrices);
      break;
     case COPY: 
      copyMatrix(matrices);
      break;
     case COPY_ASSIGN: 
      copyAssignMatrix(matrices);
      break;
     case MOVE_ASSIGN: 
      moveAssignMatrix(matrices);
      break;
     case SET:
      setMatrix(matrices);
      break;
     case GET:
      getMatrix(matrices);
      break;
     case ADD:
      addMatrices(matrices);
      break;
     case MULT:
      multMatrices(matrices);
      break;
     default: 
      cerr << "Invalid command." << endl;
      break;
    } 
  }
    
  for (auto &m: matrices) delete m;
}
