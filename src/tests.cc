#include "my_matrix_oop.h"
#include "gtest/gtest.h"

TEST(MyMatrixTest, BasicConstructor) {
  MyMatrix m;
  EXPECT_DOUBLE_EQ(m.GetRows(), 1);
  EXPECT_DOUBLE_EQ(m.GetCols(), 1);
}

TEST(MyMatrixTest, ParametrizedConstructor) {
  MyMatrix m(6, 9);
  EXPECT_DOUBLE_EQ(m.GetRows(), 6);
  EXPECT_DOUBLE_EQ(m.GetCols(), 9);
  EXPECT_ANY_THROW(MyMatrix m2(0, 1));
}

TEST(MyMatrixTest, CopyConstructor) {
  MyMatrix m1(2, 2);
  m1(0, 0) = 1;
  m1(0, 1) = 3;
  m1(1, 0) = 3;
  m1(1, 1) = 7;
  MyMatrix m2(m1);
  EXPECT_DOUBLE_EQ(m2(0, 0), 1);
  EXPECT_DOUBLE_EQ(m2(0, 1), 3);
  EXPECT_DOUBLE_EQ(m2(1, 0), 3);
  EXPECT_DOUBLE_EQ(m2(1, 1), 7);
  EXPECT_DOUBLE_EQ(m2.GetRows(), 2);
  EXPECT_DOUBLE_EQ(m2.GetCols(), 2);
}

TEST(MyMatrixTest, MoveConstructor) {
  MyMatrix m1(2, 2);
  m1(0, 0) = 1;
  m1(0, 1) = 3;
  m1(1, 0) = 3;
  m1(1, 1) = 7;
  MyMatrix m2(std::move(m1));
  EXPECT_DOUBLE_EQ(m2(0, 0), 1);
  EXPECT_DOUBLE_EQ(m2(0, 1), 3);
  EXPECT_DOUBLE_EQ(m2(1, 0), 3);
  EXPECT_DOUBLE_EQ(m2(1, 1), 7);
  EXPECT_DOUBLE_EQ(m2.GetRows(), 2);
  EXPECT_DOUBLE_EQ(m2.GetCols(), 2);
}

TEST(MyMatrixTest, EqMatrix_true) {
  MyMatrix m1(2, 2);
  MyMatrix m2(2, 2);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(1, 0) = 3;
  m1(1, 1) = 4;
  m2(0, 0) = 1;
  m2(0, 1) = 2;
  m2(1, 0) = 3;
  m2(1, 1) = 4;
  ASSERT_TRUE(m1.EqMatrix(m2));

  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(1, 0) = 3;
  m1(1, 1) = 4;
  m2(0, 0) = 1;
  m2(0, 1) = 2;
  m2(1, 0) = 3;
  m2(1, 1) = 1;
  ASSERT_FALSE(m1.EqMatrix(m2));

  MyMatrix m_t1(3, 2);
  MyMatrix m_t2(2, 2);
  ASSERT_FALSE(m_t1.EqMatrix(m_t2));
}
//
TEST(MyMatrixTest, SumMatrix) {
  MyMatrix m1(2, 2);
  MyMatrix m2(2, 2);
  MyMatrix m3(2, 2);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(1, 0) = 3;
  m1(1, 1) = 4;
  m2(0, 0) = 1;
  m2(0, 1) = 2;
  m2(1, 0) = 3;
  m2(1, 1) = 4;
  m3(0, 0) = 2;
  m3(0, 1) = 4;
  m3(1, 0) = 6;
  m3(1, 1) = 8;
  m1.SumMatrix(m2);
  ASSERT_TRUE(m1 == m3);

  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(1, 0) = 3;
  m1(1, 1) = 4;
  m1 = m1 + m2;
  ASSERT_TRUE(m1 == m3);

  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(1, 0) = 3;
  m1(1, 1) = 4;
  m1 += m2;
  ASSERT_TRUE(m1 == m3);

  MyMatrix m_t1(3, 2);
  MyMatrix m_t2(2, 2);
  ASSERT_ANY_THROW(m_t1.SumMatrix(m_t2));
}
//
TEST(MyMatrixTest, SubMatrix) {
  MyMatrix m1(2, 2);
  MyMatrix m2(2, 2);
  MyMatrix m3(2, 2);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(1, 0) = 3;
  m1(1, 1) = 4;
  m2(0, 0) = 1;
  m2(0, 1) = 2;
  m2(1, 0) = 3;
  m2(1, 1) = 4;
  m3(0, 0) = 0;
  m3(0, 1) = 0;
  m3(1, 0) = 0;
  m3(1, 1) = 0;
  m1.SubMatrix(m2);
  ASSERT_TRUE(m1 == m3);

  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(1, 0) = 3;
  m1(1, 1) = 4;
  m1 = m1 - m2;
  ASSERT_TRUE(m1 == m3);

  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(1, 0) = 3;
  m1(1, 1) = 4;
  m1 -= m2;
  ASSERT_TRUE(m1 == m3);

  MyMatrix m_t1(3, 2);
  MyMatrix m_t2(2, 2);
  ASSERT_ANY_THROW(m_t1.SubMatrix(m_t2));
}

TEST(MyMatrixTest, MulNumber) {
  MyMatrix m1(2, 2);
  MyMatrix m2(2, 2);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(1, 0) = 3;
  m1(1, 1) = 4;
  m2(0, 0) = 10;
  m2(0, 1) = 20;
  m2(1, 0) = 30;
  m2(1, 1) = 40;
  m1.MulNumber(10);
  ASSERT_TRUE(m1 == m2);

  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(1, 0) = 3;
  m1(1, 1) = 4;
  m1 = m1 * 10;
  ASSERT_TRUE(m1 == m2);

  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(1, 0) = 3;
  m1(1, 1) = 4;
  m1 *= 10;
  ASSERT_TRUE(m1 == m2);
}

TEST(MyMatrixTest, MulMatrix) {
  MyMatrix m1(3, 2);
  MyMatrix m2(2, 4);
  MyMatrix m3(3, 4);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(1, 0) = 3;
  m1(1, 1) = 4;
  m1(2, 0) = 5;
  m1(2, 1) = 6;
  m2(0, 0) = 1;
  m2(0, 1) = 2;
  m2(0, 2) = 3;
  m2(0, 3) = 4;
  m2(1, 0) = 5;
  m2(1, 1) = 6;
  m2(1, 2) = 7;
  m2(1, 3) = 8;
  m3(0, 0) = 11;
  m3(0, 1) = 14;
  m3(0, 2) = 17;
  m3(0, 3) = 20;
  m3(1, 0) = 23;
  m3(1, 1) = 30;
  m3(1, 2) = 37;
  m3(1, 3) = 44;
  m3(2, 0) = 35;
  m3(2, 1) = 46;
  m3(2, 2) = 57;
  m3(2, 3) = 68;
  m1.MulMatrix(m2);
  ASSERT_TRUE(m1 == m3);

  MyMatrix m4(3, 2);
  m4(0, 0) = 1;
  m4(0, 1) = 2;
  m4(1, 0) = 3;
  m4(1, 1) = 4;
  m4(2, 0) = 5;
  m4(2, 1) = 6;
  m4 = m4 * m2;
  ASSERT_TRUE(m4 == m3);

  MyMatrix m5(3, 2);
  m5(0, 0) = 1;
  m5(0, 1) = 2;
  m5(1, 0) = 3;
  m5(1, 1) = 4;
  m5(2, 0) = 5;
  m5(2, 1) = 6;
  m5 *= m2;
  ASSERT_TRUE(m5 == m3);

  MyMatrix m_t1(2, 5);
  MyMatrix m_t2(2, 2);
  ASSERT_ANY_THROW(m_t1.MulMatrix(m_t2));
}

TEST(MyMatrixTest, Transpose) {
  MyMatrix m1(2, 3);
  MyMatrix m3(3, 2);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(0, 2) = 3;
  m1(1, 0) = 4;
  m1(1, 1) = 5;
  m1(1, 2) = 6;

  m3(0, 0) = 1;
  m3(0, 1) = 4;
  m3(1, 0) = 2;
  m3(1, 1) = 5;
  m3(2, 0) = 3;
  m3(2, 1) = 6;

  MyMatrix m2 = m1.Transpose();
  ASSERT_TRUE(m2 == m3);
}

TEST(MyMatrixTest, CalcComplementsTest) {
  MyMatrix m1(3, 3);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(0, 2) = 3;
  m1(1, 0) = 4;
  m1(1, 1) = 5;
  m1(1, 2) = 6;
  m1(2, 0) = 7;
  m1(2, 1) = 8;
  m1(2, 2) = 9;

  MyMatrix result = m1.CalcComplements();

  EXPECT_NEAR(result(0, 0), -3, 1E-6);
  EXPECT_NEAR(result(0, 1), 6, 1E-6);
  EXPECT_NEAR(result(0, 2), -3, 1E-6);

  MyMatrix m2(1, 1);
  ASSERT_ANY_THROW(m2.CalcComplements());

  MyMatrix nonsquare(2, 3);
  ASSERT_ANY_THROW(nonsquare.CalcComplements());
}

TEST(MyMatrixTest, Determinant) {
  MyMatrix m1(3, 3);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(0, 2) = 3;
  m1(1, 0) = 4;
  m1(1, 1) = 5;
  m1(1, 2) = 6;
  m1(2, 0) = 7;
  m1(2, 1) = 8;
  m1(2, 2) = 9;
  double d = m1.Determinant();
  EXPECT_DOUBLE_EQ(d, 0);

  MyMatrix m2(1, 1);
  m2(0, 0) = 1;
  d = m2.Determinant();
  EXPECT_DOUBLE_EQ(d, 1);

  MyMatrix nonsquare(2, 3);
  ASSERT_ANY_THROW(nonsquare.Determinant());
}

TEST(MyMatrixTest, InverseMatrix) {
  MyMatrix m1(3, 3);
  MyMatrix m2(3, 3);
  m1(0, 0) = 2.0;
  m1(0, 1) = 5.0;
  m1(0, 2) = 7.0;
  m1(1, 0) = 6.0;
  m1(1, 1) = 3.0;
  m1(1, 2) = 4.0;
  m1(2, 0) = 5.0;
  m1(2, 1) = -2.0;
  m1(2, 2) = -3.0;
  m2(0, 0) = 1.0;
  m2(0, 1) = -1.0;
  m2(0, 2) = 1.0;
  m2(1, 0) = -38.0;
  m2(1, 1) = 41.0;
  m2(1, 2) = -34.0;
  m2(2, 0) = 27.0;
  m2(2, 1) = -29.0;
  m2(2, 2) = 24.0;
  ASSERT_TRUE(m1.InverseMatrix() == m2);

  MyMatrix m3(1, 1);
  MyMatrix m4(1, 1);
  m3(0, 0) = 1;
  m4(0, 0) = 1;
  ASSERT_TRUE(m3.InverseMatrix() == m4);

  MyMatrix zero(3, 3);
  ASSERT_ANY_THROW(zero.InverseMatrix());
}

TEST(MyMatrixTest, SetRows) {
  MyMatrix m(2, 2);
  m(0, 0) = 6.9;
  m.SetRows(1);
  EXPECT_DOUBLE_EQ(m.GetRows(), 1);
  EXPECT_DOUBLE_EQ(m(0, 0), 6.9);

  m.SetRows(5);
  EXPECT_DOUBLE_EQ(m.GetRows(), 5);
  EXPECT_DOUBLE_EQ(m(0, 0), 6.9);

  MyMatrix m_t;
  ASSERT_ANY_THROW(m_t.SetRows(0));
}

TEST(MyMatrixTest, SetCols) {
  MyMatrix m(2, 2);
  m(0, 0) = 6.9;
  m.SetCols(1);
  EXPECT_DOUBLE_EQ(m.GetCols(), 1);
  EXPECT_DOUBLE_EQ(m(0, 0), 6.9);

  m.SetCols(5);
  EXPECT_DOUBLE_EQ(m.GetCols(), 5);
  EXPECT_DOUBLE_EQ(m(0, 0), 6.9);

  MyMatrix m_t;
  ASSERT_ANY_THROW(m_t.SetCols(0));
}

TEST(MyMatrixTest, CheckIndex) {
  MyMatrix m(2, 2);
  m(1, 1) = 69;
  const MyMatrix mconst(m);
  EXPECT_DOUBLE_EQ(mconst(1, 1), 69);
  EXPECT_ANY_THROW(mconst(0, -1));

  MyMatrix m_t(2, 2);
  EXPECT_ANY_THROW(m_t(0, -1) = 6.9);
}

TEST(MyMatrixTest, CopyEmpty) {
  MyMatrix m1(2, 2), m2;
  m2 = std::move(m1);
  EXPECT_ANY_THROW(MyMatrix m3(m1));

  MyMatrix m_t(2, 2);
  EXPECT_ANY_THROW(m_t(0, -1) = 6.9);
}

TEST(MyMatrixTest, EqualCopy) {
  MyMatrix m1(2, 2), m2;
  m1(0, 0) = 7;
  m1(1, 0) = 2;
  m1(0, 1) = 7;
  m2 = m1;

  EXPECT_DOUBLE_EQ(m1(0, 0), 7);
  EXPECT_DOUBLE_EQ(m1(1, 0), 2);
  EXPECT_DOUBLE_EQ(m1(0, 1), 7);
}

TEST(MyMatrixTest, EqualMove) {
  MyMatrix m1(2, 2), m2, m3;
  m1(0, 0) = 7;
  m1(1, 0) = 2;
  m1(0, 1) = 7;
  m2 = std::move(m1);

  EXPECT_ANY_THROW(m3 = std::move(m1));
}

TEST(MyMatrixTest, UnaryPlus) {
  MyMatrix m1(2, 2), m2;
  m1(0, 0) = 7;
  m1(1, 0) = 2;
  m1(0, 1) = 7;
  m2 = +m1;

  EXPECT_DOUBLE_EQ(m2(0, 0), 7);
  EXPECT_DOUBLE_EQ(m2(1, 0), 2);
  EXPECT_DOUBLE_EQ(m2(0, 1), 7);
}

TEST(MyMatrixTest, UnaryMinus) {
  MyMatrix m1(2, 2), m2;
  m1(0, 0) = 7;
  m1(1, 0) = 2;
  m1(0, 1) = 7;
  m2 = -m1;

  EXPECT_DOUBLE_EQ(m2(0, 0), -7);
  EXPECT_DOUBLE_EQ(m2(1, 0), -2);
  EXPECT_DOUBLE_EQ(m2(0, 1), -7);
}

TEST(MyMatrixTest, FriendMultiply) {
  MyMatrix m1(2, 2), m2;
  m1(0, 0) = 7;
  m1(1, 0) = 2;
  m1(0, 1) = 7;
  m2 = 5 * m1;

  EXPECT_DOUBLE_EQ(m2(0, 0), 35);
  EXPECT_DOUBLE_EQ(m2(1, 0), 10);
  EXPECT_DOUBLE_EQ(m2(0, 1), 35);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
