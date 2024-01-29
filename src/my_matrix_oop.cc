#include "my_matrix_oop.h"

#include <cmath>
#include <new>
#include <stdexcept>

// ---------------------  CONSTRUCTORS  ---------------------

MyMatrix::MyMatrix() {
  rows_ = DEFAULT_ROWS;
  cols_ = DEFAULT_COLUMNS;
  Alloc(DEFAULT_ROWS, DEFAULT_COLUMNS, true);
}

MyMatrix::MyMatrix(int rows, int cols) {
  if (rows > 0 && cols > 0) {
    rows_ = rows;
    cols_ = cols;
    Alloc(rows, cols, true);
  } else {
    throw std::invalid_argument("Row count or Column count is less than 1");
  }
}

MyMatrix::MyMatrix(const MyMatrix &other) { *this = other; }

MyMatrix::MyMatrix(MyMatrix &&other) { *this = std::move(other); }

void MyMatrix::Alloc(int rows, int cols, bool set_null) {
  matrix_ = new double *[rows];
  for (int i = 0; i < rows; ++i) {
    matrix_[i] = nullptr;
  }
  try {
    for (int i = 0; i < rows; ++i) {
      matrix_[i] = new double[cols];
      if (set_null)
        NullRow(i, cols);
    }
  } catch (const std::bad_alloc &e) {
    FreeMatrix();
    throw e;
  }
}

void MyMatrix::FreeMatrix() noexcept {
  for (int i = 0; i < rows_ && matrix_; ++i) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
}

MyMatrix::~MyMatrix() noexcept { FreeMatrix(); }

// ---------------------  GETTERS/SETTERS  ---------------------

void MyMatrix::SetCols(int cols) {
  if (cols > 0) {
    int oldCols = cols_;
    cols_ = cols;
    for (int i = 0; i < rows_; ++i) {
      double *newRow = new double[cols];
      for (int j = 0; j < oldCols && j < cols; ++j) {
        newRow[j] = matrix_[i][j];
      }
      delete[] matrix_[i];
      matrix_[i] = newRow;
      NullRow(i, cols, oldCols);
    }
  } else {
    throw std::invalid_argument("Column count is less than 1");
  }
}

void MyMatrix::SetRows(int rows) {
  if (rows > 0) {
    double **newMatrix = new double *[rows];
    for (int i = 0; i < rows_ && i < rows; ++i) {
      newMatrix[i] = matrix_[i];
    }
    if (rows > rows_) {
      delete[] matrix_;
      matrix_ = newMatrix;
      for (int i = rows_; i < rows; ++i) {
        matrix_[i] = new double[cols_];
        NullRow(i, cols_);
        rows_ = i + 1;
      }
    } else {
      for (int i = rows; i < rows_; ++i) {
        delete[] matrix_[i];
      }
      delete[] matrix_;
      matrix_ = newMatrix;
      rows_ = rows;
    }
  } else {
    throw std::invalid_argument("Row count is less than 1");
  }
}

int MyMatrix::GetRows() const noexcept { return rows_; };
int MyMatrix::GetCols() const noexcept { return cols_; };

// ---------------------  OPERATIONS  ---------------------

void MyMatrix::NullRow(int row_i, int cols, int start) noexcept {
  for (int j = start; j < cols; ++j) {
    matrix_[row_i][j] = 0;
  }
}

bool MyMatrix::EqMatrix(const MyMatrix &other) noexcept {
  bool result = true;

  if (rows_ != other.rows_ || cols_ != other.cols_) {
    result = false;
  }
  if (result) {
    for (int i = 0; i < rows_ && result; ++i) {
      for (int j = 0; j < cols_ && result; ++j) {
        result = fabs(other.matrix_[i][j] - matrix_[i][j]) <= 1E-6;
      }
    }
  }

  return result;
}

void MyMatrix::SumMatrix(const MyMatrix &other) {
  if (rows_ == other.rows_ && cols_ == other.cols_) {
    SumSubMatrix(other, true);
  } else {
    throw std::invalid_argument("Matrices have different sizes in Sum");
  }
}

void MyMatrix::SubMatrix(const MyMatrix &other) {
  if (rows_ == other.rows_ && cols_ == other.cols_) {
    SumSubMatrix(other, false);
  } else {
    throw std::invalid_argument("Matrices have different sizes in Sub");
  }
}

void MyMatrix::SumSubMatrix(const MyMatrix &other, bool is_sum) noexcept {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (is_sum) {
        matrix_[i][j] += other.matrix_[i][j];
      } else {
        matrix_[i][j] -= other.matrix_[i][j];
      }
    }
  }
}

void MyMatrix::MulNumber(const double num) noexcept {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}

void MyMatrix::MulMatrix(const MyMatrix &other) {
  if (cols_ == other.rows_) {
    MyMatrix temp = MyMatrix(*this);
    SetCols(other.cols_);
    for (int i = 0; i < temp.rows_; ++i) {
      for (int j = 0; j < other.cols_; ++j) {
        double s = 0;
        for (int k = 0; k < temp.cols_; ++k) {
          s += temp.matrix_[i][k] * other.matrix_[k][j];
        }
        matrix_[i][j] = s;
      }
    }
  } else {
    throw std::invalid_argument(
        "Matrix A's Column count differs from Matrix B's Row count");
  }
}

MyMatrix MyMatrix::Transpose() {
  MyMatrix transposed = MyMatrix(cols_, rows_);
  for (int i = 0; i < cols_; ++i) {
    for (int j = 0; j < rows_; ++j) {
      transposed.matrix_[i][j] = matrix_[j][i];
    }
  }

  return transposed;
}

MyMatrix MyMatrix::CalcComplements() {
  MyMatrix compMatrix(rows_, cols_);
  if (cols_ == rows_ && cols_ > 1) {
    int sign = 1;
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        compMatrix.matrix_[i][j] = sign * Minor(i, j);
        sign *= -1;
      }
    }
  } else if (cols_ != rows_) {
    throw std::logic_error("Matrix is not a Square Matrix");
  } else {
    throw std::logic_error("Can't find 1x1 matrix's Minor");
  }

  return compMatrix;
}

double MyMatrix::Determinant() {
  double determinant = 0;

  if (cols_ == rows_ && rows_ > 1) {
    MyMatrix triang = MyMatrix(*this);
    bool iszero = false;

    for (int p = 0; p < rows_ - 1 && !iszero; ++p) { // p means pivot
      for (int i = p + 1; i < rows_ && !iszero; ++i) {
        double m = -triang.matrix_[i][p] / triang.matrix_[p][p];
        iszero = triang.matrix_[p][p] == 0;
        for (int j = 0; j < cols_ && !iszero; ++j) {
          triang.matrix_[i][j] += triang.matrix_[p][j] * m;
        }
      }
    }

    determinant = iszero ? 0 : triang.matrix_[0][0];
    for (int i = 1; i < rows_ && !iszero; ++i) {
      determinant *= triang.matrix_[i][i];
    }
  } else if (rows_ == 1) {
    determinant = matrix_[0][0];
  } else {
    throw std::logic_error("Matrix is not a Square Matrix");
  }

  return determinant;
}

double MyMatrix::Minor(int i, int j) {
  MyMatrix minorm(rows_ - 1, cols_ - 1);
  for (int oi = 0, mi = 0; oi < rows_; ++oi) {
    for (int oj = 0, mj = 0; oj < cols_; ++oj) {
      mi = oi < i ? oi : oi - 1;
      mj = oj < j ? oj : oj - 1;
      if (oi != i && oj != j) {
        minorm.matrix_[mi][mj] = matrix_[oi][oj];
      }
    }
  }

  return minorm.Determinant();
}

MyMatrix MyMatrix::InverseMatrix() {
  double det = Determinant();
  MyMatrix inverse(rows_, cols_);

  if (det != 0 && rows_ > 1) {
    inverse = CalcComplements().Transpose();
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        inverse.matrix_[i][j] /= det;
      }
    }
  } else if (rows_ == 1) {
    inverse.matrix_[0][0] = 1.0 / matrix_[0][0];
  } else {
    throw std::logic_error("Determinant of the Matrix is zero");
  }

  return inverse;
}

// ---------------------  OPERATOR OVERLOADS  ---------------------

double &MyMatrix::operator()(int i, int j) {
  double *rtn = nullptr;
  if (i >= 0 && i < rows_ && j >= 0 && j < cols_) {
    rtn = &matrix_[i][j];
  } else {
    throw std::invalid_argument("Indexes are out of the scope of this Matrix");
  }

  return *rtn;
}

double MyMatrix::operator()(int i, int j) const {
  double rtn = 0;
  if (i >= 0 && i < rows_ && j >= 0 && j < cols_) {
    rtn = matrix_[i][j];
  } else {
    throw std::invalid_argument("Indexes are out of the scope of this Matrix");
  }

  return rtn;
}

MyMatrix &MyMatrix::operator=(const MyMatrix &other) {
  if (this != &other && other.rows_ > 0 && other.cols_ > 0) {
    SetRows(other.rows_);
    SetCols(other.cols_);
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        matrix_[i][j] = other.matrix_[i][j];
      }
    }
  } else if (other.rows_ == 0 || other.cols_ == 0) {
    throw std::invalid_argument("Can't copy empty matrix");
  }
  return *this;
}

MyMatrix &MyMatrix::operator=(MyMatrix &&other) {
  if (this != &other && other.rows_ > 0 && other.cols_ > 0) {
    FreeMatrix();
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;
    other.matrix_ = nullptr;
    other.rows_ = 0;
    other.cols_ = 0;
  } else if (other.rows_ == 0 || other.cols_ == 0) {
    throw std::invalid_argument("Can't move empty matrix");
  }
  return *this;
}

MyMatrix MyMatrix::operator+(const MyMatrix &other) const {
  MyMatrix sum(*this);
  sum.SumMatrix(other);
  return sum;
}

MyMatrix MyMatrix::operator+() const noexcept { return *this; };

MyMatrix MyMatrix::operator-(const MyMatrix &other) const {
  MyMatrix sub(*this);
  sub.SubMatrix(other);
  return sub;
}

MyMatrix MyMatrix::operator-() const { return -1 * (*this); };

MyMatrix MyMatrix::operator*(const MyMatrix &other) const {
  MyMatrix mul(*this);
  mul.MulMatrix(other);
  return mul;
}

MyMatrix MyMatrix::operator*(const double num) const {
  MyMatrix mul(*this);
  mul.MulNumber(num);
  return mul;
}

MyMatrix operator*(double num, const MyMatrix &other) { return other * num; };

bool MyMatrix::operator==(const MyMatrix &other) noexcept {
  return EqMatrix(other);
};

MyMatrix MyMatrix::operator+=(const MyMatrix &other) {
  SumMatrix(other);
  return *this;
}

MyMatrix MyMatrix::operator-=(const MyMatrix &other) {
  SubMatrix(other);
  return *this;
}

MyMatrix MyMatrix::operator*=(const MyMatrix &other) {
  MulMatrix(other);
  return *this;
}

MyMatrix MyMatrix::operator*=(const double &num) noexcept {
  MulNumber(num);
  return *this;
}
