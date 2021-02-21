/**
* @file tensor.h
*
* @brief The base class representing tensors for complex algebraic 
* manipuplations of and things within coordinate frames in 3-dimensional space
*
* @author Pavlo Vlastos
*/

#ifndef TENSOR_H
#define TENSOR_H

/******************************************************************************
 * INCLUDES
 *****************************************************************************/
#include <vector>
#include <stdint.h>
#include <iostream>
#include "config.h"
using namespace std;

/******************************************************************************
 * GLOBAL VARIABLES AND DATATYPES
 *****************************************************************************/
enum class tensor_status
{
    SUCCESS = 0,
    FAILURE
};

/******************************************************************************
 * CLASS DEFINITION AND FUNCTION DECLARATIONS
 *****************************************************************************/
class tensor
{
private:
    uint8_t dimension = 3;

public:
    unsigned int m_height; /* Number of rows*/
    unsigned int n_width;  /* Number of columns*/
    vector<vector<double>> content;

    tensor(unsigned int m_rows, unsigned int n_cols)
    {
        vector<double> rows;

        if (m_rows < 1)
        { /* Check input number of rows */
            m_rows = 1;
        }

        if (n_cols < 1)
        { /* Check input number of columns */
            n_cols = 1;
        }

        for (unsigned int i_col = 0; i_col < n_cols; i_col++)
        {
            rows.push_back(0.0);
        }
        for (unsigned int i_row = 0; i_row < m_rows; i_row++)
        {
            content.push_back(rows);
        }

        m_height = content.size();
        n_width = content[0].size();
    }

    /* Tensor class constructor overloaded */
    tensor(unsigned int m_rows)
    {
        vector<double> rows;

        /* Check input number of rows */
        if (m_rows < 1)
        {
            m_rows = 1;
        }

        rows.push_back(0.0); // One column

        for (unsigned int i_row = 0; i_row < m_rows; i_row++)
        {
            content.push_back(rows);
        }

        m_height = content.size();
        n_width = content[0].size();
    }

    /* Tensor class constructor overloaded */
    tensor(const vector<vector<double>> &v)
    {
        vector<double> rows;

        unsigned int m_rows = v.size();
        unsigned int n_cols = v[0].size();

        for (unsigned int i_col = 0; i_col < n_cols; i_col++)
        {
            rows.push_back(0.0);
        }
        for (unsigned int i_row = 0; i_row < m_rows; i_row++)
        {
            content.push_back(rows);
        }

        for (unsigned int i_row = 0; i_row < m_rows; i_row++)
        {
            for (unsigned int i_col = 0; i_col < n_cols; i_col++)
            {
                content[i_row][i_col] = v[i_row][i_col];
            }
        }

        m_height = content.size();
        n_width = content[0].size();
    }

    /**
     * @brief set a the value of a tensor element
     * @param row The row of the tensor where the elemement value will be set
     * @param col The column of the tensor where the element value will be set
     * @param value The value of the element to be set of the tensor
     * @param a The tensor that will have its element set
     * @return Tensor status (SUCCESS or FAILURE)
    */
    tensor_status set_tensor_element(const unsigned int row,
                                     const unsigned int col, double value);

    /**
    * @brief Set all elements of the tensor
    * @param a A tensor to have all values set
    * @param avv A vector of vectors
    * @return Tensor status (SUCCESS or FAILURE)
    */
    tensor_status set_tensor_content(const vector<vector<double>> &avv);

    /**
     * @brief Swap the rows of a tensor content
     * @param row_a The row number [0,1,..., m] to swap with row_b
     * @param row_b The row number [0,1,..., m] to swap with row_a
     * @return Tensor status (SUCCESS or FAILURE)
    */
    tensor_status swap_rows(int row_a, int row_b);

    /**
     * @brief Rotate a quaternion
     * @param angle The angle of rotation in radians
     * @return Tensor status (SUCCESS or FAILURE)
    */
    tensor_status rotate_quaternion(double angle);

    /**
     * @brief print the tensor
    */
    void print(void);
};

/**
 * @brief multiply two tensors together to make a new tensor
 * @param a A tensor
 * @param b Another tensor
 * @return c A new tensor, being the matrix product of a and b.
 */
tensor multiply(const tensor &a, const tensor &b);

/**
 * @brief add two tensors together to make a new tensor
 * @param a A tensor
 * @param b Another tensor
 * @return c A new tensor, being the matrix addition of a and b.
 */
tensor add(const tensor &a, const tensor &b);

/**
 * @brief Makes a copy of the immediate tensor
 * @return copy of the immediate tensor
 */
tensor copy(const tensor &a);

/**
 * @brief tansposes the immediate tensor
 */
tensor transpose(const tensor &a);

tensor_status invert(const tensor &a, tensor &a_inv);

/**
 * @brief Performs gaussian elimination to row reduce tensor to upper
 * triangular form.
*/
tensor gaussian_elimination(const tensor &a);

/**
 * @brief Appends a tensor with another tensor if they have the same height
 * @param a A tensor
 * @param b Another tensor
 * @return c The width-augmented tensor
*/
tensor augment_width(const tensor &a, const tensor &b);

/**
 * @brief Appends a tensor with another tensor if they have the same width
 * @param a A tensor
 * @param b Another tensor
 * @return c The height-augmented tensor
*/
tensor augment_height(const tensor &a, const tensor &b);

/**
 * @brief Makes an identity matrix, doesn't have to be square
 * @param m The number of rows
 * @param n The number of columns
*/
tensor eye(unsigned int m, unsigned int n);

/**
 * @brief Computes the norm or p-norm of a rank 1 tensor
 * @param a A tensor of rank 1
 * @return The norm or p-norm of a tensor
*/
double norm(const tensor &a);
double norm(const tensor &a, const double p);

/**
 * @brief Create a Direction Cosine Matrix (DCM) in (yaw,pitch,roll) -> (ZXY) 
 * format
 * @param psi Yaw rotation angle value in radians
 * @param theta Pitch rotation angle value in radians
 * @param phi Roll rotation angle value in radians
 * @param dcm A tensor that will be converted to a dcm (all elements ovewritten)
 * @return Tensor status (SUCCESS or FAILURE)
*/
tensor_status create_dcm(double psi, double theta, double phi, tensor &dcm);

/**
 * @brief Convert Euler angle to a quaternion
*/
tensor_status euler_to_quaternion(double psi, double theta, double phi,
                                  tensor &q);
// tensor_status quaternion_to_dcm();
#endif /* TENSOR_H */