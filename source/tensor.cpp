/**
* @file tensor.cpp
*
* @brief The base class representing tensors for complex algebraic 
* manipuplations of and things within coordinate frames in 3-dimensional space
*
* @author Pavlo Vlastos
*/

#include "tensor.h"
#include <math.h>
using namespace std;

#define DIM 3
#define QUATERNION_HEIGHT 4
#define QUATERNION_WIDTH 1

/******************************************************************************
 * PUBLIC FUNCTION IMPLEMENTATIONS
 *****************************************************************************/
tensor_status tensor::set_tensor_element(const unsigned int row,
                                         const unsigned int col,
                                         double value)
{
    tensor_status status = tensor_status::SUCCESS;
    if ((row < m_height) && (col < n_width))
    {
        content[row][col] = value;
    }
    else
    {
        status = tensor_status::FAILURE;
    }

    return status;
}

tensor_status tensor::set_tensor_content(const vector<vector<double>> &vv)
{
    tensor_status status = tensor_status::FAILURE;

    if ((vv.size() == m_height) && (vv[0].size() == n_width))
    {
        for (unsigned int row = 0; row < m_height; row++)
        {
            for (unsigned int col = 0; col < n_width; col++)
            {
                content[row][col] = vv[row][col];
            }
        }
        status = tensor_status::SUCCESS;
    }

    return status;
}

tensor multiply(const tensor &a, const tensor &b)
{
    tensor c(a.m_height, b.n_width);

    /* Check tensor dimensions */
    if (a.n_width == b.m_height)
    {

        /* Iterate through rows in tensor c */
        for (unsigned int i = 0; i < a.m_height; i++)
        {
            /* Iterate through columns in tensor b */
            for (unsigned int j = 0; j < b.n_width; j++)
            {
                c.content[i][j] = 0.0;

                /* Iterate through elements in row of tensor a, and column
                 * of tensor b, respectively */
                for (unsigned int k = 0; k < b.m_height; k++)
                {
                    c.content[i][j] += (a.content[i][k] * b.content[k][j]);
                }
            }
        }
    }
    return c;
}

tensor copy(const tensor &a)
{
    tensor b(a.m_height, a.n_width);

    b.set_tensor_content(a.content);

    return b;
}

tensor transpose(const tensor &a)
{
    tensor b(a.n_width, a.m_height);

    for (unsigned int i = 0; i < b.m_height; i++)
    {
        for (unsigned int j = 0; j < b.n_width; j++)
        {
            b.content[i][j] = a.content[j][i];
        }
    }

    return b;
}

tensor_status invert(const tensor &a, tensor &a_inv)
{
    tensor_status status = tensor_status::FAILURE;
    tensor aug = augment_width(a, eye(a.m_height, a.n_width));

    double pivot = 0.0;
    unsigned int pivot_row = 0;
    unsigned int pivot_col = 0;
    unsigned int pivot_dia = 0;
    double x = 0.0;
    unsigned int target_row = 0;

    // Perform Gaussian elimination down to get the upper triangular form
    for (pivot_col = 0; pivot_col < a.n_width; pivot_col++, pivot_dia++)
    {

        // Find the first pivot
        for (pivot_row = pivot_dia, pivot = aug.content[pivot_row][pivot_col];
             (pivot_row < aug.m_height) && (pivot == 0.0);
             pivot = aug.content[pivot_row][pivot_col], pivot_row++)
            ;

        // If all elements in the column are zero, return with failure status
        if (pivot == 0.0)
        {
            return status;
        }

        // If the pivot row is not at the top of the matrix, make it so
        if (pivot_row != pivot_dia)
        {
            if (aug.swap_rows(pivot_dia, pivot_row) == tensor_status::SUCCESS)
            {
                pivot_row = pivot_dia;
            }
            else
            {
                return status;
            }
        }

        /*
         * Find the next row with a non-zero pivot element, if the pivot row is
         * the target row, just scale it to one
        */
        if (pivot_row != (a.m_height - 1))
        {
            for (target_row = pivot_dia; target_row < a.m_height;
                 target_row++)
            {
                if ((aug.content[target_row][pivot_col] != 0.0) && (target_row > pivot_row))
                {
                    x = aug.content[pivot_row][pivot_col];
                    x /= aug.content[target_row][pivot_col];
                    break;
                }
            }

            // Scale the target row
            for (unsigned int i = 0; i < aug.n_width; i++)
            {
                aug.content[target_row][i] *= x;
            }

            // Apply the subtraction
            for (unsigned int i = 0; i < aug.n_width; i++)
            {
                aug.content[target_row][i] -= aug.content[pivot_row][i];
            }
        }
        else if (pivot_row == (a.m_height - 1))
        {
            target_row = pivot_row;
            x = 1.0 / aug.content[target_row][pivot_col];

            // Scale the target row
            for (unsigned int i = 0; i < aug.n_width; i++)
            {
                aug.content[target_row][i] *= x;
            }
        }
    }

    // By this point, the upper triangle form is achieved

    // Perform Gaussian elimination back up, to get the identity matrix
    pivot_row = a.m_height - 1;
    pivot_col = a.n_width - 1;
    for (int p = 0; p < ((int)a.m_height - 1); p++, pivot_row--, pivot_col--)
    {

        if (pivot_row > 0)
        {
            for (int q = 0, target_row = pivot_row - 1;
                 q < (int)pivot_row; q++, target_row--)
            {

                if (aug.content[target_row][pivot_col] != 0.0)
                {
                    if (aug.content[target_row][pivot_col] != 0.0)
                    {
                        x = aug.content[target_row][pivot_col];

                        // Apply the subtraction
                        for (unsigned int i = 0; i < aug.n_width; i++)
                        {
                            aug.content[target_row][i] -=
                                (x * aug.content[pivot_row][i]);
                        }
                    }
                }
            }
        }
    }

    // Tranfer conents of augmented section of the original matrix
    for (unsigned int i = 0; i < a.m_height; i++)
    {
        for (unsigned int j = 0; j < a.n_width; j++)
        {
            a_inv.content[i][j] = aug.content[i][a.n_width + j];
        }
    }

    status = tensor_status::SUCCESS;

    return status;
}

tensor augment_width(const tensor &a, const tensor &b)
{
    tensor c(a.m_height, a.n_width + b.n_width);

    if (a.m_height == b.m_height)
    {
        for (unsigned int i = 0; i < c.m_height; i++)
        {
            for (unsigned int j = 0; j < c.n_width; j++)
            {
                if (j < a.n_width)
                {
                    c.content[i][j] = a.content[i][j];
                }
                else if ((j >= a.n_width) && (j < c.n_width))
                {
                    c.content[i][j] = b.content[i][j - a.n_width];
                }
            }
        }
    }

    return c;
}

tensor augment_height(const tensor &a, const tensor &b)
{
    tensor c(a.m_height + b.m_height, a.n_width);

    if (a.n_width == b.n_width)
    {
        for (unsigned int i = 0; i < c.m_height; i++)
        {
            for (unsigned int j = 0; j < c.n_width; j++)
            {
                if (i < a.m_height)
                {
                    c.content[i][j] = a.content[i][j];
                }
                else if ((i >= a.m_height) && (i < c.m_height))
                {
                    c.content[i][j] = b.content[i - a.n_width][j];
                }
            }
        }
    }

    return c;
}

tensor eye(unsigned int m, unsigned int n)
{
    tensor a(m, n);

    for (unsigned int i = 0; i < m; i++)
    {
        for (unsigned int j = 0; j < n; j++)
        {
            if (i == j)
            {
                a.content[i][j] = 1.0;
            }
        }
    }

    return a;
}

tensor_status tensor::swap_rows(int row_a, int row_b)
{
    double temp_element = 0.0;
    tensor_status status = tensor_status::FAILURE;

    if ((row_a >= 0) && (row_b >= 0) && (row_a != row_b))
    {
        /* Copy the row to be swapped and begin swapping each element */
        for (unsigned int j = 0; j < n_width; j++)
        {
            temp_element = content[row_a][j];
            content[row_a][j] = content[row_b][j];
            content[row_b][j] = temp_element;
        }

        status = tensor_status::SUCCESS;
    }
    else if (row_a == row_b)
    {
        status = tensor_status::SUCCESS;
    }
    else
    {
        status = tensor_status::FAILURE;
    }

    return status;
}

double norm(const tensor &a)
{
    double x = 0.0;

    for (unsigned int i = 0; i < a.m_height; i++)
    {
        x += (a.content[i][0] * a.content[i][0]);
    }

    return sqrtf(x);
}
double norm(const tensor &a, const double p)
{
    double x = 0.0;

    for (unsigned int i = 0; i < a.m_height; i++)
    {
        x += powf(a.content[i][0], p);
    }

    return powf(x, (double)(1.0 / p));
}

tensor_status tensor::rotate_quaternion(double angle)
{
    tensor_status status = tensor_status::FAILURE;

    double q_scale = sin(angle / 2.0);

    if ((m_height == QUATERNION_HEIGHT) && (n_width == QUATERNION_WIDTH))
    {
        content[0][0] = cos(angle / 2.0);
        content[1][0] *= q_scale;
        content[2][0] *= q_scale;
        content[3][0] *= q_scale;

        status = tensor_status::SUCCESS;
    }

    return status;
}

tensor_status create_dcm(double psi, double theta, double phi, tensor &dcm)
{
    if ((dcm.m_height != DIM) || (dcm.n_width != DIM))
    {
        return tensor_status::FAILURE;
    }

    dcm.content[0][0] = cos(psi) * cos(theta);
    dcm.content[0][1] = sin(psi) * cos(theta);
    dcm.content[0][2] = -sin(theta);

    dcm.content[1][0] = cos(psi) * sin(theta) * sin(phi) - sin(psi) * cos(phi);
    dcm.content[1][1] = sin(psi) * sin(theta) * sin(phi) + cos(psi) * cos(phi);
    dcm.content[1][2] = cos(theta) * sin(phi);

    dcm.content[2][0] = cos(psi) * sin(theta) * cos(phi) + sin(psi) * sin(phi);
    dcm.content[2][1] = sin(psi) * sin(theta) * cos(phi) - cos(psi) * sin(phi);
    dcm.content[2][2] = cos(theta) * cos(phi);

    return tensor_status::SUCCESS;
}

void tensor::print(void)
{
    for (unsigned int row = 0; row < m_height; row++)
    {
        cout << "[ ";
        for (unsigned int col = 0; col < n_width; col++)
        {
            cout << content[row][col] << " ";
        }
        cout << "]\n";
    }
    cout << "Dimensions: " << m_height << " x " << n_width << "\n";
}

/******************************************************************************
 * UNIT TESTS
 *****************************************************************************/
#ifdef TESTING_TENSOR

int main(void)
{

#ifdef TEST_TENSOR_CLASS_CONSTRUCTOR
    {
        cout << "TEST_TENSOR_CLASS_CONSTRUCTOR\r\n";
        int rows;
        int cols;
        rows = 4;
        cols = 3;

        tensor tnsr0(rows, cols);

        tnsr0.print();

        tensor a(vector<vector<double>>{{1, 2}, {2, 1}, {1, 2}, {2, 1}});
        a.print();
    }
#endif

#ifdef TEST_TENSOR_MULTIPLICATION
    {
        cout << "TEST_TENSOR_MULTIPLICATION\r\n";
        tensor a(vector<vector<double>>{{1, 2, 0}, {2, 1, 0}});
        tensor b(vector<vector<double>>{{1}, {2}, {3}});

        cout << "first operand tensor:\r\n";
        a.print();

        cout << "second operand tensor:\r\n";
        b.print();

        tensor c = multiply(a, b);

        c.print();
    }
#endif
#ifdef TEST_TENSOR_COPY
    {
        cout << "TEST_TENSOR_COPY\r\n";
        cout << "first operand tensor to be copied:\r\n";
        tensor a(vector<vector<double>>{{1, 2, 5}, {2, 1, 50.02}});
        tensor b = copy(a);
        a.print();
        b.print();
    }
#endif
#ifdef TEST_TENSOR_TRANSPOSE
    {
        cout << "TEST_TENSOR_TRANSPOSE\r\n";
        cout << "first operand tensor to be tranposed:\r\n";
        tensor a(vector<vector<double>>{{1.0, 3.2, 0.5}, {0.2, 1.0, 50.02}, {0.1, 11, 25.01}});
        tensor b = transpose(a);
        a.print();
        b.print();
    }
#endif
#ifdef TEST_TENSOR_SWAP_ROWS
    {
        cout << "TEST_TENSOR_SWAP_ROWS\r\n";
        tensor a(vector<vector<double>>{{1.0, 3.2, 0.5}, {0.2, 1.0, 50.02}, {0.1, 11, 25.01}});
        a.print();
        a.swap_rows(0, 2);
        a.print();
    }
#endif
#ifdef TEST_TENSOR_AUGMENT_WIDTH
    {
        cout << "TEST_TENSOR_AUGMENT_WIDTH\r\n";
        tensor a(vector<vector<double>>{{1.0, 2.0, 3.0}, {0.0, 1.0, 4.0}, {5.0, 6.0, 1.0}});
        a.print();

        tensor b = copy(a);
        b.print();

        tensor c = augment_width(a, b);
        c.print();
    }
#endif
#ifdef TEST_TENSOR_AUGMENT_HEIGHT
    {
        cout << "TEST_TENSOR_AUGMENT_HEIGHT\r\n";
        tensor a(vector<vector<double>>{{1.0, 2.0, 3.0}, {0.0, 1.0, 4.0}, {5.0, 6.0, 1.0}});
        a.print();

        tensor b = copy(a);
        b.print();

        tensor c = augment_height(a, b);
        c.print();
    }
#endif
#ifdef TEST_TENSOR_EYE
    {
        cout << "TEST_TENSOR_EYE\r\n";
        tensor a = eye(4, 4);
        a.print();
    }
#endif
#ifdef TEST_TENSOR_INVERT
    {
        cout << "TEST_TENSOR_INVERT\r\n";
        tensor a(vector<vector<double>>{{1.0, 2.0, 3.0}, {0.0, 1.0, 4.0}, {5.0, 6.0, 1.0}});
        a.print();

        tensor a_inv(a.m_height, a.n_width);
        a_inv.print();

        invert(a, a_inv);

        a_inv.print();
    }
#endif
#ifdef TEST_TENSOR_NORM
    {
        cout << "TEST_TENSOR_NORM\r\n";
        tensor a(vector<vector<double>>{{1.0}, {2.0}, {3.0}});

        a.print();

        cout << "norm(a) = " << norm(a) << "\r\n";

        double p = 3.0;

        cout << "p = " << p << "\r\n";
        cout << "p-norm(a) = " << norm(a, p) << "\r\n";
    }
#endif
#ifdef TEST_TENSOR_DCM
    {
        cout << "TEST_TENSOR_DCM\r\n";

        tensor dcm(3,3);
        tensor a(vector<vector<double>>{{1.0}, {0.0}, {0.0}});

        dcm.print();
        a.print();

        create_dcm(30.0*M_PI/180.0, 0.0, 0.0, dcm);
        dcm.print();

        tensor b = multiply(dcm, a);

        b.print();
    }
#endif
    return 0;
}
#endif