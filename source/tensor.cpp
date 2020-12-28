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

/******************************************************************************
 * PUBLIC FUNCTION IMPLEMENTATIONS
 *****************************************************************************/
tensor_status_t tensor::set_tensor_element(const unsigned int row,
    const unsigned int col, double value) {
    tensor_status_t status = SUCCESS;
    if ((row >= 0) && (row < m_height) && (col >= 0) && (col < n_width)) {
        content[row][col] = value;

    }
    else {
        status = FAILURE;
    }

    return status;
}

tensor_status_t tensor::set_tensor(const vector<vector<double>>& vv)
{
    tensor_status_t status = SUCCESS;

    if ((vv.size() == m_height) && (vv[0].size() == n_width)) {
        for (int row = 0; row < m_height; row++) {
            for (int col = 0; col < n_width; col++) {
                content[row][col] = vv[row][col];
            }
        }
    }

    return status;
}

tensor_status_t tensor::multiply(const tensor& a, const tensor& b) {
    tensor_status_t status = SUCCESS;

    /* Check tensor dimensions */
    if ((a.n_width == b.m_height) && (a.m_height == m_height)
        && (b.n_width == n_width)) {

        /* Iterate through rows in tensor c */
        for (int i = 0; i < a.m_height; i++) {

            /* Iterate through columns in tensor b */
            for (int j = 0; j < b.n_width; j++) {
                content[i][j] = 0.0;

                /* Iterate through elements in row of tensor a, and column
                 * of tensor b, respectively */
                for (int k = 0; k < b.m_height; k++) {
                    content[i][j] += (a.content[i][k] * b.content[k][j]);
                }
            }
        }

    }
    else {
        status = FAILURE;
    }
    return status;
}

#ifdef TESTING
#include <iostream>

void tensor::print_tensor(void)
{
    for (int row = 0; row < m_height; row++) {
        cout << "[ ";
        for (int col = 0; col < n_width; col++) {
            cout << content[row][col] << " ";
        }
        cout << "]\n";
    }
    cout << "Dimensions: " << m_height << " x " << n_width << "\n";
}

using namespace std;

int main(void) {

#ifdef TEST_TENSOR_CLASS_CONSTRUCTOR
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
#endif

#ifdef TEST_TENSOR_MULTIPLICATION
    tensor a(2, 3);
    tensor b(3, 1);
    tensor c(2, 1);;

    /* Set all of the tensors */
    vector<vector<double>> avv = {
        { 1, 2, 0 }, { 2, 1, 0 }
    };
    vector<vector<double>> bvv = { { 1 }, { 2 }, { 3 } };

    a.set_tensor(avv);
    b.set_tensor(bvv);

    /* Print everything */
    cout << "first operand tensor:\r\n";
    a.print_tensor();

    cout << "second operand tensor:\r\n";
    b.print_tensor();

    if (c.multiply(a, b) == SUCCESS) {
        cout << "tensor multiplication completed, result:\r\n";
    }
    c.print_tensor();
#endif

    return 1;
}
#endif