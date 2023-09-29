#include <cassert>
#include "Matrix.hpp"

// REQUIRES: mat points to a Matrix
//           0 < width && width <= MAX_MATRIX_WIDTH
//           0 < height && height <= MAX_MATRIX_HEIGHT
// MODIFIES: *mat
// EFFECTS:  Initializes *mat as a Matrix with the given width and height.
// NOTE:     Do NOT use new or delete here.
void Matrix_init(Matrix *mat, int width, int height)
{

  if (mat != nullptr)
  {
    if (width > 0 && width <= MAX_MATRIX_WIDTH)
    {
      mat->width = width;
    }
    if (height > 0 && height <= MAX_MATRIX_WIDTH)
    {
      mat->height = height;
    }
  }
}
// REQUIRES: mat points to a valid Matrix
// MODIFIES: os
// EFFECTS:  First, prints the width and height for the Matrix to os:
//             WIDTH [space] HEIGHT [newline]
//           Then prints the rows of the Matrix to os with one row per line.
//           Each element is followed by a space and each row is followed
//           by a newline. This means there will be an "extra" space at
//           the end of each line.
void Matrix_print(const Matrix *mat, std::ostream &os)
{
  // Print the width and height of the matrix
  if (mat != nullptr)
  {
    os << mat->width << " " << mat->height << "\n";

    // Print the rows of the matrix
    for (int i = 0; i < mat->height; ++i)
    {
      for (int j = 0; j < mat->width; ++j)
      {
        os << mat->data[i * mat->width + j] << " ";
      }
      os << "\n"; // Newline after each row
    }
  }
}
// REQUIRES: mat points to an valid Matrix
// EFFECTS:  Returns the width of the Matrix.
int Matrix_width(const Matrix *mat)
{
  if (mat != nullptr)
  {
    return mat->width;
  }
  return 0;
}
// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the height of the Matrix.
int Matrix_height(const Matrix *mat)
{
  if (mat != nullptr)
  {
    return mat->height;
  }
  return 0;
}
// REQUIRES: mat points to a valid Matrix
//           ptr points to an element in the Matrix
// EFFECTS:  Returns the row of the element pointed to by ptr.
int Matrix_row(const Matrix *mat, const int *ptr)
{
  if (mat != nullptr && ptr != nullptr)
  {
    for (int i = 0; i < mat->height * mat->width; i++)
    {
      if (&mat->data[i] == ptr)
      {
        return i / mat->width;
      }
    }
  }
  return 0;
}

// REQUIRES: mat points to a valid Matrix
//           ptr point to an element in the Matrix
// EFFECTS:  Returns the column of the element pointed to by ptr.
int Matrix_column(const Matrix *mat, const int *ptr)
{
  if (mat != nullptr && ptr != nullptr)
  {
    for (int i = 0; i < mat->height * mat->width; i++)
    {
      if (&mat->data[i] == ptr)
      {
        return i % mat->width;
      }
    }
  }
  return 0;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// MODIFIES: (The returned pointer may be used to modify an
//            element in the Matrix.)
// EFFECTS:  Returns a pointer to the element in the Matrix
//           at the given row and column.
int *Matrix_at(Matrix *mat, int row, int column)
{
  if (column < Matrix_width(mat) && 0 <= column)
  {
    if (mat != nullptr && 0 <= row && row < Matrix_height(mat))
    {
      return &mat->data[row * mat->width + column];
    }
  }
  return nullptr;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// EFFECTS:  Returns a pointer-to-const to the element in
//           the Matrix at the given row and column.
const int *Matrix_at(const Matrix *mat, int row, int column)
{   if( 0 <= column && column < Matrix_width(mat))
  {if (mat != nullptr && 0 <= row && row < Matrix_height(mat) )
  {
    int element = mat->data[row * mat->width + column];
    int *ptr = &element;
    return ptr;
  }}
  return nullptr;
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element of the Matrix to the given value.
void Matrix_fill(Matrix *mat, int value)
{
  if (mat != nullptr)
  {
    int size = mat->height * mat->width;
    for (int i = 0; i < size; i++)
    {
      mat->data[i] = value;
    }
  }
}
// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element on the border of the Matrix to
//           the given value. These are all elements in the first/last
//           row or the first/last column.
void Matrix_fill_border(Matrix *mat, int value)
{
  if (mat != nullptr)
  {
    for (int i = 0; i < mat->width; i++)
    {
      mat->data[i] = value;
      mat->data[(mat->height - 1) * mat->width + i] = value;
    }
    for (int i = 0; i < mat->height; i++)
    {
      *Matrix_at(mat, i, 0) = value;
      *Matrix_at(mat, i, mat->width - 1) = value;
    }
  }
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the value of the maximum element in the Matrix
int Matrix_max(const Matrix *mat)
{
  if (mat != nullptr)
  {
    int max = 0;
    for (int i = 0; i < mat->height * mat->width; i++)
    {
      if (mat->data[i] > max)
      {
        max = mat->data[i];
      }
    }
    return max;
  }
  return 0;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the column of the element with the minimal value
//           in a particular region. The region is defined as elements
//           in the given row and between column_start (inclusive) and
//           column_end (exclusive).
//           If multiple elements are minimal, returns the column of
//           the leftmost one.
int Matrix_column_of_min_value_in_row
  (const Matrix *mat, int row,int column_start, int column_end)
{ 
      assert(column_end <= Matrix_width(mat));
      assert(column_start < column_end);
    assert(mat != nullptr);
    assert(0 <= row);
    assert(row < Matrix_height(mat));
    assert(0 <= column_start );
  
  
  {
    int min_column = column_start;
    int min_value = mat->data[row * mat->width + column_start];

    for (int column = column_start; column < column_end; column++)
    {
      int current_value = mat->data[row * mat->width + column];
      if (current_value < min_value)
      {
        min_value = current_value;
        min_column = column;
      }
    }

    return min_column;
  }
  return 0;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the minimal value in a particular region. The region
//           is defined as elements in the given row and between
//           column_start (inclusive) and column_end (exclusive).
int Matrix_min_value_in_row(const Matrix *mat, int row, int column_start, int column_end)
{ 
    assert(column_end <= Matrix_width(mat));
    assert(column_start < column_end);
    assert(mat != nullptr);
    assert(0 <= row);
    assert(row < Matrix_height(mat));
    assert(0 <= column_start );
    int min_value = mat->data[row * mat->width + column_start];

    for (int column = column_start; column < column_end; column++)
    {
      int current_value = mat->data[row * mat->width + column];
      if (current_value < min_value)
      {
        min_value = current_value;
      }
    }

    return min_value;
  
  return 0;
}
