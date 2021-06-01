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
#include "tensor.h"

/******************************************************************************
 * DEFINES
 *****************************************************************************/
#define STATE_SIZE 12

/******************************************************************************
 * CLASS DEFINITION AND FUNCTION DECLARATIONS
 *****************************************************************************/
class particle
{
private:
    double dt = 0.001;

    double radius = 1.0; /* Must have non-zero default values */
    double mass = 1.0;
    double moi = 2.0 * (mass * radius * radius) / 5.0; /* Moment of inertia */

    tensor state;      /* The particle state vector*/
    tensor phi;        /* The discrete state transition, or dynamics matrix */
    tensor gamma;      /* The input matrix */
    tensor u;          /* The input vector */
    tensor body_frame; /* Body-frame axes */

public:
    /* Class constructor (Just one for now) */
    particle(const double x, const double y, const double z)
        : state(STATE_SIZE), // Initializer list
          phi(vector<vector<double>>{
              {1.0, 0.0, 0.0, dt, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
              {0.0, 1.0, 0.0, 0.0, dt, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
              {0.0, 0.0, 1.0, 0.0, 0.0, dt, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
              {0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
              {0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
              {0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
              {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, dt, 0.0, 0.0},
              {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, dt, 0.0},
              {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, dt},
              {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0},
              {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0},
              {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0}}),
          gamma(vector<vector<double>>{
              {(dt * dt / mass), 0.0, 0.0, 0.0, 0.0, 0.0},
              {0.0, (dt * dt / mass), 0.0, 0.0, 0.0, 0.0},
              {0.0, 0.0, (dt * dt / mass), 0.0, 0.0, 0.0},
              {(dt / mass), 0.0, 0.0, 0.0, 0.0, 0.0},
              {0.0, (dt / mass), 0.0, 0.0, 0.0, 0.0},
              {0.0, 0.0, (dt / mass), 0.0, 0.0, 0.0},
              {0.0, 0.0, 0.0, (radius * dt * dt / moi), 0.0, 0.0, 0.0},
              {0.0, 0.0, 0.0, 0.0, (radius * dt * dt / moi), 0.0, 0.0},
              {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, (radius * dt * dt / moi)},
              {0.0, 0.0, 0.0, (radius * dt / moi), 0.0, 0.0, 0.0},
              {0.0, 0.0, 0.0, 0.0, (radius * dt / moi), 0.0, 0.0},
              {0.0, 0.0, 0.0, 0.0, 0.0, (radius * dt / moi)}}),
          u(vector<vector<double>>{
              {0.0},
              {0.0},
              {0.0},
              {0.0},
              {0.0},
              {0.0}}),
          body_frame(vector<vector<double>>{
              {1.0, 0.0, 0.0},
              {0.0, 1.0, 0.0},
              {0.0, 0.0, 1.0}})
    {
        /* Position */
        state.content[0][0] = x; // x
        state.content[1][0] = y; // y
        state.content[2][0] = z; // z

        /* Velocity */
        state.content[3][0] = 0.0; // dx
        state.content[4][0] = 0.0; // dy
        state.content[5][0] = 0.0; // dz

        /* Angular Orientation */
        /* Orientation in *SOME* reference frame @TODO: figure out which 
         * reference frame. I think it is inertial technically, but this might
         * be assignable in relation to another particle */
        state.content[6][0] = 0.0; // yaw: radians
        state.content[7][0] = 0.0; // pitch: radians
        state.content[8][0] = 0.0; // roll: radians

        /* Angular Rates */
        state.content[9][0] = 0.0;  // yaw-rate: radians per second
        state.content[10][0] = 0.0; // pitch-rate: radians per second
        state.content[11][0] = 0.0; // roll-rate: radians per second
    }

    /**
     * @brief Updates the state of the particle, based on the input force
     * member. Make sure to call set_u() before calling this method/function
     * @return tensor_status SUCCESS or FAILURE
    */
    tensor_status update(void);

    /**************************************************************************
     * Setters
    **************************************************************************/
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
     * @brief Set the input tensor, gamma 
     * @note Any force on a particle is broken up into the normal and tangent
     * components of the force. Then, the x,y,z components are
     * @param fnx The x-component of normal force in the particle body-frame
     * @param fny The y-component of normal force in the particle body-frame
     * @param fnz The z-component of normal force in the particle body-frame
     * @param ftx The x-component of force tangent to the surface of the 
     * particle in the particles body-reference-frame
     * @param fty The x-component of force tangent to the surface of the 
     * particle in the particles body-reference-frame
     * @param ftz The x-component of force tangent to the surface of the 
     * particle in the particles body-reference-frame
     * @return tensor_status SUCCESS or FAILURE
    */
    tensor_status set_u(const double fnx, const double fny, const double fnz,
                        const double ftx, const double fty, const double ftz);

    /**
     * @brief Set the mass of the particle
     * @note This function does NOT call set_moi() for an obvious reason: 
     * recusion. However, it still updates the moi. No extra call needed.
     * @param mass The mass of the sphere representing the particle
     * @return tensor_status SUCCESS or FAILURE
     */
    tensor_status set_mass(const double mass);

    /**
     * @brief Set the mass of the particle
     * @note This function does NOT call set_moi() for an obvious reason: 
     * recusion. However, it still updates the moi. No extra call needed.
     * @param radius The radius of the sphere representing the particle
     * @return tensor_status SUCCESS or FAILURE
     */
    tensor_status set_radius(const double radius);

    /**
     * @brief Set the moment of inertia for the particle modeled as a solid 
     * sphere with uniform mass
     * @note This method will update the particle's mass and radius, by calling
     * set_mass() and set_radius()
     * @param radius The radius of the sphere representing the particle
     */
    tensor_status set_moi(const double mass, const double radius);

    /**
     * @brief Sets the sample-time of the particle. This is also meant for
     * dynamic sample-times in case of time dilation 
     * @param dt_new The new sample time
     * @return tensor_status SUCCESS or FAILURE
    */
    tensor_status set_sample_time(double dt_new);

    /**************************************************************************
     * Getters
    **************************************************************************/
    /**
     * @brief Gets the state of the particle
     * @return the state vector of the particle as a tensor object
     */
    tensor get_state(void);

    /**
     * @brief Print out the attributes of the particle
    */
    void print(void);
};

#endif /* PARTICLE_H */
