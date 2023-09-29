#include "Matrix.hpp"
#include "Image_test_helpers.hpp"
#include "unit_test_framework.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>
#include <fstream>
using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
  Image *img = new Image; // create an Image in dynamic memory

  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(img, 2, 2);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);

  // Capture our output
  ostringstream s;
  Image_print(img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete img; // delete the Image
}

TEST(test_print_single) {
  
  Image *img = new Image;
  Image_init(img, 1, 1);
  const Pixel pixel = {128, 64, 32};
  Image_set_pixel(img, 0, 0, pixel); 
  ostringstream s;
  Image_print(img, s);
  ostringstream correct;
  correct << "P3\n1 1\n255\n";
  correct << "128 64 32 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete img;
}

TEST(test_print_max) {
  Image *img = new Image;
  Image_init(img, MAX_MATRIX_WIDTH, MAX_MATRIX_HEIGHT);
  const Pixel w = {255, 255, 255};
  Image_fill(img, w);
  ostringstream s;
  Image_print(img, s);
  ostringstream right;
  right << "P3\n500 500\n255\n";
  for (int i = 0; i < MAX_MATRIX_HEIGHT; i++) {
    for (int j = 0; j < MAX_MATRIX_WIDTH; j++) {
      right << "255 255 255 ";
    }
    right << "\n";
  }
  ASSERT_EQUAL(s.str(), right.str());
  delete img;
}

TEST(test_init_with_invalid_dimensions) {
  Image img;
  Image_init(&img, 10, 10);
  ASSERT_EQUAL(Image_width(&img), 10);
  ASSERT_EQUAL(Image_height(&img), 10);
}

TEST(test_fill_image_with_color) {
  Image img;
  Image_init(&img, 10, 10);
  Pixel color = {128, 128, 128};
  Image_fill(&img, color);
  for (int row = 0; row < Image_height(&img); row++) {
    for (int col = 0; col < Image_width(&img); col++) {
      Pixel pixel = Image_get_pixel(&img, row, col);
      ASSERT_EQUAL(pixel.r, color.r);
      ASSERT_EQUAL(pixel.g, color.g);
      ASSERT_EQUAL(pixel.b, color.b);
    }
  }
    Image img1;
  Image_init(&img1, 45, 23);
  Pixel color1 = {124, 23, 74};
  Image_fill(&img1, color1);
  for (int row = 0; row < Image_height(&img1); row++) {
    for (int col = 0; col < Image_width(&img1); col++) {
      Pixel pixel = Image_get_pixel(&img1, row, col);
      ASSERT_EQUAL(pixel.r, color1.r);
      ASSERT_EQUAL(pixel.g, color1.g);
      ASSERT_EQUAL(pixel.b, color1.b);
    }
  }
}

TEST(test_with_ppm){
  string filename="crabster.ppm";
  Image* img = new Image;
  // Test left rotation
  ifstream fin;
  fin.open(filename.c_str());

  Image_init(img, fin);
  
  Pixel p;
  p.r=255;
  p.g=255;
  p.b=255;
  assert(Pixel_equal(Image_get_pixel(img,0,0), p));
  assert(Pixel_equal(Image_get_pixel(img,0,1), p));
  assert(Pixel_equal(Image_get_pixel(img,0,2), p));
  assert(Pixel_equal(Image_get_pixel(img,0,3), p));
  assert(Pixel_equal(Image_get_pixel(img,0,4), p));
  assert(Pixel_equal(Image_get_pixel(img,0,5), p));
  Pixel p2;
  p2.r=100;
  p2.g=100;
  p2.b=100;
  Image_set_pixel(img, 0, 0, p2);
  assert(Pixel_equal(Image_get_pixel(img,0,0), p2));
  Image_set_pixel(img, 1, 12, p2);
  assert(Pixel_equal(Image_get_pixel(img,1,12), p2));
  Image_set_pixel(img, 13, 14, p2);
  assert(Pixel_equal(Image_get_pixel(img,13,14), p2));
  Image_set_pixel(img, 15, 23, p2);
  assert(Pixel_equal(Image_get_pixel(img,15,23), p2));
  Image_set_pixel(img, 33, 12, p2);
  assert(Pixel_equal(Image_get_pixel(img,33,12), p2));
  Image_fill(img,p2);

  ASSERT_EQUAL(Image_width(img), 74);
  ASSERT_EQUAL(Image_height(img), 45);
   for (int row = 0; row < Image_height(img); row++) {
    for (int col = 0; col < Image_width(img); col++) {
      Pixel pixel = Image_get_pixel(img, row, col);
      ASSERT_EQUAL(pixel.r, p2.r);
      ASSERT_EQUAL(pixel.g, p2.g);
      ASSERT_EQUAL(pixel.b, p2.b);
    }
  }
  cout << "PASS" << endl;
  cout << "PASS" << endl;

  delete img;
}


// Add more tests as needed for specific functionalities of your Image and Matrix classes.


// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
