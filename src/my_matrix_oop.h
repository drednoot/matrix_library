#ifndef MYMATRIXPLUS_MYMATRIXOOP_H_
#define MYMATRIXPLUS_MYMATRIXOOP_H_
#define DEFAULT_ROWS 1
#define DEFAULT_COLUMNS 1

class MyMatrix {
public:
  MyMatrix();                      // Default constructor
  MyMatrix(int rows, int cols);    // Parametrized constructor
  MyMatrix(const MyMatrix &other); // Copy constructor
  MyMatrix(MyMatrix &&other);      // Move constructor
  ~MyMatrix() noexcept;            // Destructor

  int GetRows() const noexcept; // Accessors
  int GetCols() const noexcept;
  void SetRows(int rows); // Mutators
  void SetCols(int cols);

  // operations
  bool EqMatrix(const MyMatrix &other) noexcept;
  void SumMatrix(const MyMatrix &other);
  void SubMatrix(const MyMatrix &other);
  void MulNumber(const double num) noexcept;
  void MulMatrix(const MyMatrix &other);
  MyMatrix Transpose();
  MyMatrix CalcComplements();
  double Determinant();
  double Minor(int i, int j);
  MyMatrix InverseMatrix();

  // operator overloads
  double &operator()(int i, int j);
  double operator()(int i, int j) const;
  MyMatrix &operator=(const MyMatrix &other);
  MyMatrix &operator=(MyMatrix &&other);
  MyMatrix operator+(const MyMatrix &other) const;
  MyMatrix operator+() const noexcept;
  MyMatrix operator-(const MyMatrix &other) const;
  MyMatrix operator-() const;
  MyMatrix operator*(const MyMatrix &other) const;
  MyMatrix operator*(const double num) const;
  friend MyMatrix operator*(double num, const MyMatrix &other);
  bool operator==(const MyMatrix &other) noexcept;
  MyMatrix operator+=(const MyMatrix &other);
  MyMatrix operator-=(const MyMatrix &other);
  MyMatrix operator*=(const MyMatrix &other);
  MyMatrix operator*=(const double &num) noexcept;

private:
  int rows_ = 0, cols_ = 0;
  double **matrix_ = nullptr;

  void NullRow(int row_i, int cols, int start = 0) noexcept;
  void Alloc(int rows, int cols, bool set_null);
  void FreeMatrix() noexcept;
  void SumSubMatrix(const MyMatrix &other, bool is_sum) noexcept;
};

#endif
