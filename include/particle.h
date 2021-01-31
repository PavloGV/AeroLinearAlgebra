/**
* @file particle.cpp
*
* @brief A class for a particle in various coordinate frames
*
* @author Pavlo Vlastos
*/

#ifndef PARTICLE_H
#define PARTICLE_H

/******************************************************************************
 * INCLUDES
 *****************************************************************************/
#include "particle.h"
#include "tensor.h"
#include <vector>

/******************************************************************************
 * CLASS DEFINITION AND FUNCTION DECLARATIONS
 *****************************************************************************/
class particle
{
private:
    uint8_t dimension = 3;
    double dt = 0.001;
    
    double radius = 1.0; /* Must have non-zero default values */
    double mass = 1.0;

    /* Body-frame axes */
    vector<double> xb{1.0, 0.0, 0.0};
    vector<double> yb{1.0, 1.0, 0.0};
    vector<double> zb{1.0, 0.0, 1.0};

    tensor state;
    tensor phi;
    tensor gamma;

public:
    /* Class constructors */
    particle(double x, double y, double z) : state(2 * dimension), // Initializer list
                     phi(vector<vector<double>>{
                         {1.0, 0.0, 0.0, dt, 0.0, 0.0},
                         {0.0, 1.0, 0.0, dt, 0.0, 0.0},
                         {0.0, 0.0, 1.0, 0.0, dt, 0.0},
                         {0.0, 0.0, 0.0, 1.0, 0.0, dt},
                         {0.0, 0.0, 0.0, 0.0, 1.0, 0.0},
                         {0.0, 0.0, 0.0, 0.0, 0.0, 1.0}}),
                     gamma(vector<vector<double>>{
                         {(dt * dt / mass), 0.0, 0.0},
                         {0.0, (dt * dt / mass), 0.0},
                         {0.0, 0.0, (dt * dt / mass)},
                         {(dt / mass), 0.0, 0.0},
                         {0.0, (dt / mass), 0.0},
                         {0.0, 0.0, (dt / mass)}})
    {
        // Position
        state.content[0][0] = x; // x
        state.content[1][0] = y; // y
        state.content[2][0] = z; // z

        // Velocity
        state.content[3][0] = 0.0; // dx
        state.content[4][0] = 0.0; // dy
        state.content[5][0] = 0.0; // dz
    }
    particle(double r, double m, double x, double y, double z, double dx,
             double dy, double dz) : state(2 * dimension), // Initializer list
                                     phi(vector<vector<double>>{
                                         {1.0, 0.0, 0.0, dt, 0.0, 0.0},
                                         {0.0, 1.0, 0.0, dt, 0.0, 0.0},
                                         {0.0, 0.0, 1.0, 0.0, dt, 0.0},
                                         {0.0, 0.0, 0.0, 1.0, 0.0, dt},
                                         {0.0, 0.0, 0.0, 0.0, 1.0, 0.0},
                                         {0.0, 0.0, 0.0, 0.0, 0.0, 1.0}}),
                                     gamma(vector<vector<double>>{
                                         {(dt * dt / mass), 0.0, 0.0},
                                         {0.0, (dt * dt / mass), 0.0},
                                         {0.0, 0.0, (dt * dt / mass)},
                                         {(dt / mass), 0.0, 0.0},
                                         {0.0, (dt / mass), 0.0},
                                         {0.0, 0.0, (dt / mass)}})
    {
        radius = r; // radius
        mass = m;   // mass

        // Position
        state.content[0][0] = x; // x
        state.content[1][0] = y; // y
        state.content[2][0] = z; // z

        // Velocity
        state.content[3][0] = dx; // dx
        state.content[4][0] = dy; // dy
        state.content[5][0] = dz; // dz
    }

    /**
     * @brief Updates the position and velocity of the particle, based on an 
     * input force tensor
     * @param force A force tensor
     * @return tensor_status SUCCESS or FAILURE
    */
    tensor_status update(const tensor &force);

    /**
     * @brief Set the state transition tensor, phi 
     * @param dt The sample-time
     * @return tensor_status SUCCESS or FAILURE
    */
    tensor_status set_phi(const double dt);

    /**
     * @brief Set the input tensor, gamma 
     * @param dt The sample-time
     * @return tensor_status SUCCESS or FAILURE
    */
    tensor_status set_gamma(const double dt);

    /**
     * @brief Sets the sample-time of the particle. This is also meant for
     * dynamic sample-times in case of time dilation 
     * @param dt_new The new sample time
     * @return tensor_status SUCCESS or FAILURE
    */
    tensor_status set_sample_time(double dt_new);

    /**
     * @brief Get the dimension attribute value
    */
    uint8_t get_dimension(void);

    /**
     * @brief Print out the attributes of the particle
    */
    void print(void);
};

#endif /* PARTICLE_H */
