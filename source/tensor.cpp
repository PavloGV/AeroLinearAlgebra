/**
* @file tensor.cpp
* 
* @brief A class representing tensors for complex algebraic manipuplations of 
* and things within coordinate frames in 3-dimensional space
* 
* @author Pavlo Vlastos
*/

#include "tensor.h"
#include "tensor_config.h"

#ifdef TEST_CLASS_CONSTRUCTOR
#include <iostream>

using namespace std;

int main (void) {
    int rows;
    int cols;
    rows = 4;
    cols = 3;

    tensor tnsr0(rows, cols);

    for (int row = 0; row < tnsr0.m_height; row++) {
        cout << "[ ";
        for (int col = 0; col < tnsr0.n_width; col++) {
            cout << tnsr0.content[row][col] << " ";
        }
        cout << "]\n";
    }
    cout << "Dimensions: " << tnsr0.m_height << " x " << tnsr0.n_width << "\n";
    return 1;
}
#endif