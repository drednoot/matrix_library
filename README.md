# Matrix Library

This is a C++ matrix library. It operates on two-dimensional matrices, has a lot of convenient methods for using matrices in your application

## Usage 

Include header `my_matrix_oop.h`

## API

MyMatrix - the main class of the program  
It represents `mxn` matrix (m rows, n columns)

### Public constructors:

| Constructor | Description | Trows |
| ----------- | ----------- | ----- |
| `MyMatrix()` | Default constructor. Allocates a `1x1` matrix (initial value is `0.0`) | `std::bad_alloc` on allocation error
| `MyMatrix(int rows, int cols)` | Allocates a `rowsxcols` matrix (`rows` rows, `cols` cols) | `std::bad_alloc` on allocation error; `std::invalid_argument` if `rows` or `cols` are less than 1
| `MyMatrix(const MyMatrix &other)` | Copy constructor. Copies contents of `other` matrix | `std::bad_alloc` on allocation error; `std::invalid_argument` if `other` is empty
| `MyMatrix(MyMatrix &&other)` | Move constructor. Moves contents of `other` to the new matrix. The `other` matrix becomes empty | `std::invalid_argument` if `other` is empty

### Public methods:

| Method | Description | Trows |
| ------ | ----------- | ----- |
| `GetRows() -> int` | Returns current row count of the matrix | -
| `GetCols() -> int` | Returns current column count of the matrix | -
| `SetRows(int rows)` | Sets current row count to `rows`; fills new rows with `0.0` | `std::bad_alloc` on allocation error; `std::invalid_argument` if `rows` is less than 1
| `SetCols(int cols)` | Sets current column count to `cols`; fills new columns with `0.0` | `std::bad_alloc` on allocation error; `std::invalid_argument` if `cols` is less than 1
| `EqMatrix(const MyMatrix &other) -> bool` | Returns `true` if `other` is the same size as `this` matrix, if `other`'s elements are approximately the same as in `this` matrix (presicion 1e-6). Returns `false` otherwise | -
| `SumMatrix(const MyMatrix &other)` | Sums `this` matrix with `other`. The result is saved in `this` matrix | `std::invalid_argument` if matrices' dimenstions differ
| `SubMatrix(const MyMatrix &other)` | Subtracts `other` matrix from `this`. The result is saved in `this` matrix | `std::invalid_argument` if matrices' dimenstions differ
| `MulNumber(const double num)` | Multiplies `this` matrix by `num`. The result is saved in `this` matrix | -
| `MulMatrix(const MyMatrix &other)` | Multiplies `this` matrix by `other`. The result is saved in `this` matrix | `std::invalid_argument` if `this`' column count is different than `other`'s
| `Transpose() -> MyMatrix` | Returns transposed version of `this` matrix | `std::bad_alloc` on allocation error 
| `CalcComplements() -> Mymatrix` | Returns `this`' algebraic complement matrix | `std::bad_alloc` on allocation error 
| `Determinant -> double` | Returns `this`' determinant | `std::logic_error` if `this` is not a square matrix; `std::bad_alloc` on allocation error
| `Minor(int i, int j) -> double` | Returns minor of element at position `(i, j)` | `std::logic_error` if `this` is not a square matrix; `std::bad_alloc` on allocation error
| `InverseMatrix() -> MyMatrix` | Returns inverse of `this` matrix | `std::logic_error` if `this` is not a square matrix; `std::logic_error` if determinant of the matrix is zero; `std::bad_alloc` on allocation error

### Operator overloads:

All operations will be performed on `MyMatrix A, B;`

| Usage | Description | Trows |
| ----- | ----------- | ----- |
| `A(int i, int j)` | Returns element at `(i, j)` | `std::invalid_argument` if indices are out of bounds
| `A = B` | Same as `MyMatrix A(B);` | 
| `A = std::move(B)` | Same as `MyMatrix A(std::move(B));`
| `+A` | Same as `A` (plus operator overload)
| `-A` | Same as `A.MulNumber(-1.0);`
| `A + B` | Analogous to `SumMatrix` method
| `A - B` | Analogous to `SubMatrix` method
| `A * B` | Analogous to `MulMatrix` method
| `A * num` or `num * A` | Analogous to `MulNumber` method
| `A == B` | Analogous to `EqMatrix` method
| `A += B` | Same as `A = A + B`
| `A -= B` | Same as `A = A - B`
| `A *= B` | Same as `A = A * B`
| `A *= num` | Same as `A = A * num`

# Building

## Requirements

 - gcc
 - stdc++ (usually comes bundled with g++)
 - [Google Test](https://github.com/google/googletest) (for tests)

## Build steps

```
cd src
make my_matrix_oop.a
```

# Testing

Testing is done on [Google Test](https://github.com/google/googletest) testing framework. To run tests, run the following:

```
cd src
make test
```

