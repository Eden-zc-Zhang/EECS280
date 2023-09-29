#include "arrays.hpp"
#include "unit_test_framework.hpp"

// We define a test case with the TEST(<test_name>) macro.
// <test_name> can be any valid C++ function name.
TEST(test_slide_right) {
    int a[] = {1, 2, 3, 4, 5, 6};
    int b[] = {6, 1, 2, 3, 4, 5};
    slideRight(a, 6); 
    for (int i = 0; i < 6; i++) {
        ASSERT_EQUAL(a[i], b[i]);
    }
}

TEST(test_flip) {
    int a[] = {1, 2, 3, 4, 5, 6};
    int b[] = {6, 5, 4, 3, 2, 1};
    flip(a, 6); 
    for (int i = 0; i < 6; i++) {
        ASSERT_EQUAL(a[i], b[i]);
    }
}

TEST_MAIN() // No semicolon!