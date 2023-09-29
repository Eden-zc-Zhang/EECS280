#include "processing.hpp"
#include "cassert"

using namespace std;

// v DO NOT CHANGE v ------------------------------------------------
// The implementation of rotate_left is provided for you.
// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  The image is rotated 90 degrees to the left (counterclockwise).
void rotate_left(Image* img) {

  // for convenience
  int width = Image_width(img);
  int height = Image_height(img);

  // auxiliary image to temporarily store rotated image
  Image *aux = new Image;
  Image_init(aux, height, width); // width and height switched

  // iterate through pixels and place each where it goes in temp
  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      Image_set_pixel(aux, width - 1 - c, r, Image_get_pixel(img, r, c));
    }
  }

  // Copy data back into original
  *img = *aux;
  delete aux;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------

// v DO NOT CHANGE v ------------------------------------------------
// The implementation of rotate_right is provided for you.
// REQUIRES: img points to a valid Image.
// MODIFIES: *img
// EFFECTS:  The image is rotated 90 degrees to the right (clockwise).
void rotate_right(Image* img){

  // for convenience
  int width = Image_width(img);
  int height = Image_height(img);

  // auxiliary image to temporarily store rotated image
  Image *aux = new Image;
  Image_init(aux, height, width); // width and height switched

  // iterate through pixels and place each where it goes in temp
  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      Image_set_pixel(aux, c, height - 1 - r, Image_get_pixel(img, r, c));
    }
  }

  // Copy data back into original
  *img = *aux;
  delete aux;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------


// v DO NOT CHANGE v ------------------------------------------------
// The implementation of diff2 is provided for you.
static int squared_difference(Pixel p1, Pixel p2) {
  int dr = p2.r - p1.r;
  int dg = p2.g - p1.g;
  int db = p2.b - p1.b;
  // Divide by 100 is to avoid possible overflows
  // later on in the algorithm.
  return (dr*dr + dg*dg + db*db) / 100;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------


// ------------------------------------------------------------------
// You may change code below this line!



// REQUIRES: img points to a valid Image.
//           energy points to a Matrix.
// MODIFIES: *energy
// EFFECTS:  energy serves as an "output parameter".
//           The Matrix pointed to by energy is initialized to be the same
//           size as the given Image, and then the energy matrix for that
//           image is computed and written into it.
//           See the project spec for details on computing the energy matrix.
void compute_energy_matrix(const Image* img, Matrix* energy) {
    assert(img != nullptr && energy != nullptr);
    int width = Image_width(img);
    int height = Image_height(img);
    int x_energy = 0;
    int y_energy = 0;
    Matrix_init(energy, width, height);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (x > 0 && x < width - 1 && y > 0 && y < height - 1) {
                Pixel x_left = Image_get_pixel(img, y, x - 1);
                Pixel x_right = Image_get_pixel(img, y, x + 1);
                x_energy = squared_difference(x_left, x_right);

                Pixel y_top = Image_get_pixel(img, y - 1, x);
                Pixel y_bottom = Image_get_pixel(img, y + 1, x);
                y_energy = squared_difference(y_top, y_bottom);
            }
            *(Matrix_at(energy, y, x)) = x_energy + y_energy;
        }
    }
    Matrix_fill_border(energy, Matrix_max(energy));
}

// REQUIRES: energy points to a valid Matrix.
//           cost points to a Matrix.
//           energy and cost aren't pointing to the same Matrix
// MODIFIES: *cost
// EFFECTS:  cost serves as an "output parameter".
//           The Matrix pointed to by cost is initialized to be the same
//           size as the given energy Matrix, and then the cost matrix is
//           computed and written into it.
//           See the project spec for details on computing the cost matrix.
void compute_vertical_cost_matrix(const Matrix* energy, Matrix* cost) {
    assert (energy != nullptr && cost != nullptr && energy != cost);
    int width = Matrix_width(energy);
    int height = Matrix_height(energy);
    Matrix_init(cost, width, height);

    for (int c = 0; c < width; c++) {
        *Matrix_at(cost, 0, c) = *Matrix_at(energy, 0, c);
    }
    int min_cost = 0;
    for (int r = 1; r < height; r++) {
        for (int c = 0; c < width; c++) {
            min_cost = *Matrix_at(cost, r - 1, c);
            if (c > 0) {
                min_cost = std::min(min_cost, *Matrix_at(cost, r - 1, c - 1));
            }
            if (c < width - 1) {
                min_cost = std::min(min_cost, *Matrix_at(cost, r - 1, c + 1));
            }

            *Matrix_at(cost, r, c) = *Matrix_at(energy, r, c) + min_cost;
        }
    }
}

// REQUIRES: cost points to a valid Matrix
//           seam points to an array
//           the size of seam is >= Matrix_height(cost)
// MODIFIES: seam[0]...seam[Matrix_height(cost)-1]
// EFFECTS:  seam serves as an "output parameter".
//           The vertical seam with the minimal cost according to the given
//           cost matrix is found and the seam array is filled with the column
//           numbers for each pixel along the seam, with the pixel for each
//           row r placed at seam[r]. While determining the seam, if any pixels
//           tie for lowest cost, the leftmost one (i.e. with the lowest
//           column number) is used.
//           See the project spec for details on computing the minimal seam.
// NOTE:     You should compute the seam in reverse order, starting
//           with the bottom of the image and proceeding to the top,
//           as described in the project spec.
void find_minimal_vertical_seam(const Matrix* cost, int seam[]) {
    if (cost != nullptr && seam != nullptr) {
        int height = Matrix_height(cost);
        int width = Matrix_width(cost);
        int min = 0;
        for (int r = height - 1; r >= 0 ; r--) {
            if (r == height-1) {
                min = Matrix_column_of_min_value_in_row(cost, height - 1, 0, width);
                seam[height - 1] = min;
            }                
            else if ( r<height-1 && min == 0) { 
                min = Matrix_column_of_min_value_in_row(cost, r , 0, 2);
                seam[r] = min;
            }
            else if(r<height-1 && min == width - 1) {
                min = Matrix_column_of_min_value_in_row(cost, r, width - 2, width);
                seam[r] = min;
            }
            else {
                min = Matrix_column_of_min_value_in_row(cost, r, min - 1, min + 2);
                seam[r] = min;
            }
        }
    }
}

// REQUIRES: img points to a valid Image with width >= 2
//           seam points to an array
//           the size of seam is == Image_height(img)
//           each element x in seam satisfies 0 <= x < Image_width(img)
// MODIFIES: *img
// EFFECTS:  Removes the given vertical seam from the Image. That is, one
//           pixel will be removed from every row in the image. The pixel
//           removed from row r will be the one with column equal to seam[r].
//           The width of the image will be one less than before.
//           See the project spec for details on removing a vertical seam.
// NOTE:     Use the new operator here to create the smaller Image,
//           and then use delete when you are done with it.
void remove_vertical_seam(Image* img, const int seam[]) {
    assert (img!= nullptr && seam!= nullptr);
    int height = Image_height(img);
    int width = Image_width(img);

    Image* newImg = new Image;
    Image_init(newImg, width - 1, height);
    int seamCol = 0;
    int newCol = 0;
    Pixel pixel;
    for (int r = 0; r < height; r++) {
        seamCol = seam[r];
        newCol = 0;

        for (int c = 0; c < width; c++) {
            if (c != seamCol) {
                pixel = Image_get_pixel(img, r, c);
                Image_set_pixel(newImg, r, newCol, pixel);
                newCol++;
            }
        }
    }

    *img = *newImg;
    delete newImg;
}


// REQUIRES: img points to a valid Image
//           0 < newWidth && newWidth <= Image_width(img)
// MODIFIES: *img
// EFFECTS:  Reduces the width of the given Image to be newWidth by using
//           the seam carving algorithm. See the spec for details.
// NOTE:     Use the new operator here to create Matrix objects, and
//           then use delete when you are done with them.
// NOTE:     The size of an array local variable must be a compile-time
//           constant. You can use MAX_MATRIX_HEIGHT as the constant,
//           since an image's height can be no larger than that.
void seam_carve_width(Image* img, int newWidth) {
    if (img != nullptr && newWidth > 0 && newWidth <= Image_width(img)) {
        int currentWidth = Image_width(img);

        while (currentWidth > newWidth) {
            Matrix* energy = new Matrix;
            Matrix_init(energy, currentWidth, Image_height(img));
            compute_energy_matrix(img, energy);

            Matrix* cost = new Matrix;
            compute_vertical_cost_matrix(energy, cost);

            int seam[MAX_MATRIX_HEIGHT];
            find_minimal_vertical_seam(cost, seam);
            remove_vertical_seam(img, seam);

            currentWidth--;
            delete energy;
            delete cost;
        }
    }
}

// REQUIRES: img points to a valid Image
//           0 < newHeight && newHeight <= Image_height(img)
// MODIFIES: *img
// EFFECTS:  Reduces the height of the given Image to be newHeight.
// NOTE:     This is equivalent to first rotating the Image 90 degrees left,
//           then applying seam_carve_width(img, newHeight), then rotating
//           90 degrees right.
void seam_carve_height(Image* img, int newHeight) {
    if (img!= nullptr && newHeight > 0 && newHeight <= Image_height(img)) {
        rotate_left(img);
        seam_carve_width(img, newHeight);

        rotate_right(img);
    }
}

// REQUIRES: img points to a valid Image
//           0 < newWidth && newWidth <= Image_width(img)
//           0 < newHeight && newHeight <= Image_height(img)
// MODIFIES: *img
// EFFECTS:  Reduces the width and height of the given Image to be newWidth
//           and newHeight, respectively.
// NOTE:     This is equivalent to applying seam_carve_width(img, newWidth)
//           and then applying seam_carve_height(img, newHeight).
void seam_carve(Image* img, int newWidth, int newHeight) {
    if (img!= nullptr) {
        if (newWidth > 0 && newWidth <= Image_width(img)) {
            if (newHeight > 0 && newHeight <= Image_height(img)) {
                seam_carve_width(img, newWidth);
                seam_carve_height(img, newHeight);
            }
        }
    }
}