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
using namespace std;


/******************************************************************************
 * GLOBAL VARIABLES
 *****************************************************************************/
enum error_status {
    SUCCESS = 0,
    FAILURE
};
typedef error_status error_status_t;

/******************************************************************************
 * CLASS DEFINITION
 *****************************************************************************/
class tensor {
public:
    unsigned int m_height;              /* Number of rows*/
    unsigned int n_width;               /* Number of columns*/
    vector<vector<double>> content;

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
    }

    multiply()
};