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

    } else {
        status = FAILURE;
    }

    return status;
}

tensor_status_t tensor::set_tensor_content(const vector<vector<double>>& vv) {
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

tensor multiply(const tensor& a, const tensor& b) {
    tensor c(a.m_height, b.n_width);

    /* Check tensor dimensions */
    if (a.n_width == b.m_height) {

        /* Iterate through rows in tensor c */
        for (int i = 0; i < a.m_height; i++) {

            /* Iterate through columns in tensor b */
            for (int j = 0; j < b.n_width; j++) {
                c.content[i][j] = 0.0;

                /* Iterate through elements in row of tensor a, and column
                 * of tensor b, respectively */
                for (int k = 0; k < b.m_height; k++) {
                    c.content[i][j] += (a.content[i][k] * b.content[k][j]);
                }
            }
        }
    }

    return c;
}

tensor copy(const tensor& a) {
    tensor b(a.m_height, a.n_width);

    b.set_tensor_content(a.content);

    for (int i = 0; i < b.ref_point_a.size(); i++) {
        b.ref_point_a[i] = a.ref_point_a[i];
        b.ref_point_b[i] = a.ref_point_b[i];
    }
    return b;
}

tensor transpose(const tensor& a) {
    tensor b(a.n_width, a.m_height);

    for (int i = 0; i < b.m_height; i++) {
        for (int j = 0; j < b.n_width; j++) {
            b.content[i][j] = a.content[j][i];
        }
    }

    return b;
}

/******************************************************************************
 * UNIT TESTS
 *****************************************************************************/
#ifdef TESTING
#include <iostream>

/**
 * @todo: print all the other tensor class attributes
*/
void tensor::print_tensor(void) {
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
    cout << "Testing tensor constructor\r\n";
    int rows;
    int cols;
    rows = 4;
    cols = 3;

    tensor tnsr0(rows, cols);

    tnsr0.print_tensor();

    tensor a(vector<vector<double>> { { 1, 2 }, { 2, 1 }, { 1, 2 },
             { 2, 1} });
    a.print_tensor();
#endif

#ifdef TEST_TENSOR_MULTIPLICATION
    {
        cout << "Testing tensor multiplication\r\n";
        tensor a(vector<vector<double>> { { 1, 2, 0 }, { 2, 1, 0 } });
        tensor b(vector<vector<double>> { { 1 }, { 2 }, { 3 } });

        cout << "first operand tensor:\r\n";
        a.print_tensor();

        cout << "second operand tensor:\r\n";
        b.print_tensor();

        tensor c = multiply(a, b);

        c.print_tensor();
    }
#endif
#ifdef TEST_TENSOR_COPY
    {
        cout << "Testing tensor copy()\r\n";
        cout << "first operand tensor to be copied:\r\n";
        tensor a(vector<vector<double>> { { 1, 2, 5 }, { 2, 1, 50.02 } });
        tensor b = copy(a);
        a.print_tensor();
        b.print_tensor();
    }
#endif
#ifdef TEST_TENSOR_TRANSPOSE
    {
        cout << "Testing tensor transpose()\r\n";
        cout << "first operand tensor to be tranposed:\r\n";
        tensor a(vector<vector<double>> { { 1.0, 3.2, 0.5 }, { 0.2, 1.0, 50.02 },
                 { 0.1, 11, 25.01 }});
        tensor b = transpose(a);
        a.print_tensor();
        b.print_tensor();
    }
#endif

    return 1;
}
#endif