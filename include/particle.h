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

/******************************************************************************
 * CLASS DEFINITION AND FUNCTION DECLARATIONS
 *****************************************************************************/
class particle
{
private:
    uint8_t dimension = 3;
    double dt = 0.001;

    tensor phi(vector<vector<double>>{
        {1.0, 0.0, 0.0, dt, 0.0, 0.0},
        {0.0, 1.0, 0.0, dt, 0.0, 0.0},
        {0.0, 0.0, 1.0, 0.0, dt, 0.0},
        {0.0, 0.0, 0.0, 1.0, 0.0, dt},
        {0.0, 0.0, 0.0, 0.0, 1.0, 0.0},
        {0.0, 0.0, 0.0, 0.0, 0.0, 1.0}});

    tensor gamma(vector<vector<double>>{
        {(dt * dt / mass), 0.0, 0.0},
        {0.0, (dt * dt / mass), 0.0},
        {0.0, 0.0, (dt * dt / mass)},
        {(dt / mass), 0.0, 0.0},
        {0.0, (dt / mass), 0.0},
        {0.0, 0.0, (dt / mass)}});

public:
    double radius = 1.0;
    double mass = 0.0;

    tensor state(3 * dimension, 1);

    /* Class constructors */
    particle(double r, double m, double x, double y, double z, double dx,
             double dy, double dz)
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
    particle(double r, double m, const vector<double> &a)
    {
        radius = r; // radius
        mass = m;   // mass

        if (a.size() == (3 * dimension))
        {
            // Position
            state.content[0][0] = a[0]; // x
            state.content[1][0] = a[1]; // y
            state.content[2][0] = a[2]; // z

            // Velocity
            state.content[3][0] = a[3]; // dx
            state.content[4][0] = a[4]; // dy
            state.content[5][0] = a[5]; // dz
        }
    }
    particle(double r, double m, const tensor &a)
    {
        radius = r; // radius
        mass = m;   // mass

        if (a.m_height == (3 * dimension))
        {
            // Position
            state.content[0][0] = a.content[0][0]; // x
            state.content[1][0] = a.content[1][0]; // y
            state.content[2][0] = a.content[2][0]; // z

            // Velocity
            state.content[3][0] = a.content[3][0]; // dx
            state.content[4][0] = a.content[4][0]; // dy
            state.content[5][0] = a.content[5][0]; // dz
        }
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

#ifdef TESTING_PARTICLE
    /**
     * @brief Print out the attributes of the particle
    */
    void print(void);
#endif
};

#endif /* PARTICLE_H */
