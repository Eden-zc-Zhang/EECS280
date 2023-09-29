#include <iostream>
#include <cassert>
#include "Matrix.hpp"
#include "Matrix_test_helpers.hpp"
#include "unit_test_framework.hpp"

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }

  delete mat; // delete the Matrix
}

// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.hpp as needed.

TEST (test_print) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 2, 2);
  *Matrix_at(mat, 0, 0) = 42;
  *Matrix_at(mat, 0, 1) = 43;
  *Matrix_at(mat, 1, 0) = 44;
  *Matrix_at(mat, 1, 1) = 45;
  ostringstream expected;
  expected << "2 2\n"
           << "42 43 \n"
           << "44 45 \n";
  ostringstream actual;
  Matrix_print(mat, actual);
  ASSERT_EQUAL(expected.str(), actual.str());

  delete mat;
}

TEST (test_Width) {
  Matrix *mat = new Matrix;

  Matrix_init(mat, 1, 5);
  ASSERT_EQUAL(Matrix_width(mat), 1);

  delete mat;
}

TEST (test_Height) {
  Matrix *mat = new Matrix;

  Matrix_init(mat, 3, 1);
  ASSERT_EQUAL(Matrix_height(mat), 1);

  delete mat;
}

TEST (test_Get_Element_Basic) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 5, 3);
  Matrix_fill(mat, 5);

  int *ptr = Matrix_at(mat, 2, 4);
  ASSERT_EQUAL(Matrix_row(mat, ptr), 2);
  ASSERT_EQUAL(Matrix_column(mat, ptr), 4);
  ASSERT_EQUAL(*ptr, 5);

  ptr = Matrix_at(mat, 0, 0);
  ASSERT_EQUAL(Matrix_row(mat, ptr), 0);
  ASSERT_EQUAL(Matrix_column(mat, ptr), 0);
  ASSERT_EQUAL(*ptr, 5);

  ptr = Matrix_at(mat, 0, 4);
  ASSERT_EQUAL(Matrix_row(mat, ptr), 0);
  ASSERT_EQUAL(Matrix_column(mat, ptr), 4);
  ASSERT_EQUAL(*ptr, 5);

  ptr = Matrix_at(mat, 2, 0);
  ASSERT_EQUAL(Matrix_row(mat, ptr), 2);
  ASSERT_EQUAL(Matrix_column(mat, ptr), 0);
  ASSERT_EQUAL(*ptr, 5);

  delete mat;
}

TEST (test_fill_border) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 5, 3);
  Matrix_fill(mat, 5);
  Matrix_fill_border(mat, 1);
  ASSERT_EQUAL(*Matrix_at(mat, 0, 0), 1);
  ASSERT_EQUAL(*Matrix_at(mat, 0, 1), 1);
  ASSERT_EQUAL(*Matrix_at(mat, 0, 2), 1);
  ASSERT_EQUAL(*Matrix_at(mat, 0, 3), 1);
  ASSERT_EQUAL(*Matrix_at(mat, 0, 4), 1);
  ASSERT_EQUAL(*Matrix_at(mat, 1, 0), 1);
  ASSERT_EQUAL(*Matrix_at(mat, 2, 0), 1);
  ASSERT_EQUAL(*Matrix_at(mat, 2, 1), 1);
  ASSERT_EQUAL(*Matrix_at(mat, 2, 2), 1);
  ASSERT_EQUAL(*Matrix_at(mat, 2, 3), 1);
  ASSERT_EQUAL(*Matrix_at(mat, 2, 4), 1);
  ASSERT_EQUAL(*Matrix_at(mat, 1, 4), 1);

  // ostringstream expected;
  // Matrix_print(mat, expected);
  // cout << expected.str();

  delete mat;
}

TEST (Fill_border_edge_case) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 5, 1);
  Matrix_fill(mat, 5);
  Matrix_fill_border(mat, 1);
  ASSERT_EQUAL(*Matrix_at(mat, 0, 0), 1);
  ASSERT_EQUAL(*Matrix_at(mat, 0, 1), 1);
  ASSERT_EQUAL(*Matrix_at(mat, 0, 2), 1);
  ASSERT_EQUAL(*Matrix_at(mat, 0, 3), 1);
  ASSERT_EQUAL(*Matrix_at(mat, 0, 4), 1);

  Matrix_init(mat, 1, 5);
  Matrix_fill(mat, 5);
  Matrix_fill_border(mat, 1);

  ASSERT_EQUAL(*Matrix_at(mat, 0, 0), 1);
  ASSERT_EQUAL(*Matrix_at(mat, 1, 0), 1);
  ASSERT_EQUAL(*Matrix_at(mat, 2, 0), 1);
  ASSERT_EQUAL(*Matrix_at(mat, 3, 0), 1);
  ASSERT_EQUAL(*Matrix_at(mat, 4, 0), 1);
  delete mat;
}


TEST (test_Max) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 2, 2);
  *Matrix_at(mat, 0, 0) = 42;
  *Matrix_at(mat, 0, 1) = 43;
  *Matrix_at(mat, 1, 0) = 44;
  *Matrix_at(mat, 1, 1) = 45;
  ASSERT_EQUAL(Matrix_max(mat), 45);

  delete mat;
}

TEST (test_Column_Min_value_in_row) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 5, 5);
  Matrix_fill(mat, 10);

  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 2, 0, Matrix_width(mat)), 0);

  Matrix_init(mat, 5, 1);
  *Matrix_at(mat, 0, 0) = 45;
  *Matrix_at(mat, 0, 1) = 42;
  *Matrix_at(mat, 0, 2) = 44;
  *Matrix_at(mat, 0, 3) = 45;
  *Matrix_at(mat, 0, 4) = 42;
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 0, 0, Matrix_width(mat)), 1);
  delete mat;
}

TEST (test_min_value) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 5, 5);
  Matrix_fill(mat, 10);

  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 4, 0, Matrix_width(mat)), 10);

  Matrix_init(mat, 5, 1);
  *Matrix_at(mat, 0, 0) = 42;
  *Matrix_at(mat, 0, 1) = 45;
  *Matrix_at(mat, 0, 2) = 44;
  *Matrix_at(mat, 0, 3) = 45;
  *Matrix_at(mat, 0, 4) = 43;
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 0, 0, Matrix_width(mat)), 42);
  delete mat;
}


// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
