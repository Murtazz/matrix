# Matrix

mimics a matrix. The mechanics will be listed in the readme.


c mi Initializes matrix mi by calling its constructor and passing in the dimensions, and then setting its values, where the information is read from standard input. Invokes the matrix destructor if the object previously existed. 

C mi Invokes the copy constructor to create a temporary matrix, passing in mi as the parameter. Outputs the temporary matrix and mi using operator>> to standard output. 

d mi Invokes the destructor of matrix mi.

a mi mj Assign copies mj to mi (mi = mj ) by performing a deep copy. Outputs mi and mj using operator>> to standard output.

A mi mj Assign moves mj to mi (mi = std::move( mj )) so mi steals the information from mj , leaving mj empty. std::move is used to explicitly mark mj as an rvalue.

r mi Uses operator>> to initialize matrix mi by reading the dimensions (row, then column) and value from standard input. Since the operator requires an object, an initially empty matrix is created using the default constructor. Outputs mi using operator>> to standard output.

p mi Uses operator<< to output matrix mi to standard output.

m mi Uses the move constructor to move the contents of mi to a temporary matrix. Outputs the temporary matrix and mi using operator>> to standard output. 

s mi x y z Set mi [x][y] = z and output to standard output. 

g mi x y Get mi [x][y] and output to standard output.

+ mi mj : Create a temporary matrix that is equal to mi + mj if the dimensions of mi and mj are the same. Outputs the temporary matrix using operator>> to standard output.

* mi mj : Create a temporary matrix that is equal to mi × mj if the number of columns in mi equals the number of rows in mj . Outputs the temporary matrix using operator>> to standard output
