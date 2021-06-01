/**
 * @file config.h
 * 
 * @brief Configurations for various classes and subsequent tests
 */

// #define TESTING_TENSOR
#ifdef TESTING_TENSOR

#define TEST_TENSOR_CLASS_CONSTRUCTOR
#define TEST_TENSOR_MULTIPLICATION
#define TEST_TENSOR_ADD
#define TEST_TENSOR_COPY
#define TEST_TENSOR_TRANSPOSE
#define TEST_TENSOR_SWAP_ROWS
#define TEST_TENSOR_AUGMENT_WIDTH
#define TEST_TENSOR_AUGMENT_HEIGHT
#define TEST_TENSOR_EYE
#define TEST_TENSOR_INVERT
#define TEST_TENSOR_NORM
#define TEST_TENSOR_TO_GNUPLOT_DOT
#define TEST_TENSOR_DCM

#endif

#define TESTING_PARTICLE
#ifdef TESTING_PARTICLE

#define TEST_PARTICLE_PRINT
#define TEST_PARTICLE_UPDATE

#endif

// #define TESTING_PLOT_GEN
#ifdef TESTING_PLOT_GEN

#define TEST_GEN_DAT

#endif