/**
* @file tensor.h
*
* @brief A class representing tensors for complex algebraic manipuplations of
* and things within coordinate frames in 3-dimensional space
*
* @author Pavlo Vlastos
*/

/******************************************************************************
 * INCLUDES
 *****************************************************************************/
#include <vector>
#include "tensor_config.h"
using namespace std;


/******************************************************************************
 * GLOBAL VARIABLES
 *****************************************************************************/
enum tensor_status {
    SUCCESS = 0,
    FAILURE
};
typedef tensor_status tensor_status_t;

/******************************************************************************
 * CLASS DEFINITION AND FUNCTION DECLARATIONS
 *****************************************************************************/
class tensor {
private:
    uint8_t dimension = 3;

public:
    unsigned int m_height;              /* Number of rows*/
    unsigned int n_width;               /* Number of columns*/
    vector<vector<double>> content;

    vector<double> ref_point_a;
    vector<double> ref_point_b;

    tensor(int m_rows, int n_cols) {    /* Tensor class constructor*/
        vector<double> rows;

        for (int i_col = 0; i_col < n_cols; i_col++) {
            rows.push_back(0.0);
        }
        for (int i_row = 0; i_row < m_rows; i_row++) {
            content.push_back(rows);
        }

        m_height = content.size();
        n_width = content[0].size();


        for (int i = 0; i < dimension; i++) {
            ref_point_a.push_back(0.0);
            ref_point_b.push_back(0.0);
        }
    }
    
    /** 
     * @brief set a the value of a tensor element
     * @param row The row of the tensor where the elemement value will be set
     * @param col The column of the tensor where the element value will be set
     * @param value The value of the element to be set of the tensor
     * @param a The tensor that will have its element set
     * @return Tensor status (SUCCESS or FAILURE)
    */
    tensor_status_t set_tensor_element(const unsigned int row, 
        const unsigned int col, double value);

    /**
     * @brief Set all elements of the tensor
     * @param a A tensor to have all values set
     * @param avv A vector of vectors
     * @return Tensor status (SUCCESS or FAILURE)
    */
    tensor_status_t set_tensor(const vector<vector<double>>& avv);

    tensor_status_t multiply(const tensor& a, const tensor& b);

#ifdef TESTING
    /**
     * @brief print the tensor
    */
    void print_tensor(void);
#endif
};