/**
* @file particle.cpp
*
* @brief A class for a particle in various coordinate frames
*
* @author Pavlo Vlastos
*/

/******************************************************************************
 * INCLUDES
 *****************************************************************************/
#include "particle.h"

/******************************************************************************
 * PUBLIC FUNCTION IMPLEMENTATIONS
 *****************************************************************************/
tensor_status particle::update(const tensor &force)
{
    tensor_status status = tensor_status::FAILURE;

    if (force.m_height == (3 * get_dimension()))
    {

        status = tensor_status::SUCCESS;
    }
    return status;
}

tensor_status particle::set_phi(const double dt)
{
    if (dt == 0.0)
    {
        return tensor_status::FAILURE;
    }

    tensor new_phi(vector<vector<double>>{
        {1.0, 0.0, 0.0, dt, 0.0, 0.0},
        {0.0, 1.0, 0.0, dt, 0.0, 0.0},
        {0.0, 0.0, 1.0, 0.0, dt, 0.0},
        {0.0, 0.0, 0.0, 1.0, 0.0, dt},
        {0.0, 0.0, 0.0, 0.0, 1.0, 0.0},
        {0.0, 0.0, 0.0, 0.0, 0.0, 1.0}});

    if (phi.set_tensor_content(new_phi.content) == tensor_status::FAILURE)
    {
        return tensor_status::FAILURE;
    }

    return tensor_status::SUCCESS;
}

tensor_status particle::set_gamma(const double dt)
{
    if (dt == 0.0)
    {
        return tensor_status::FAILURE;
    }

    tensor new_gamma(vector<vector<double>>{
        {(dt * dt / mass), 0.0, 0.0},
        {0.0, (dt * dt / mass), 0.0},
        {0.0, 0.0, (dt * dt / mass)},
        {(dt / mass), 0.0, 0.0},
        {0.0, (dt / mass), 0.0},
        {0.0, 0.0, (dt / mass)}});

    if (gamma.set_tensor_content(new_gamma.content) == tensor_status::FAILURE)
    {
        return tensor_status::FAILURE;
    }

    return tensor_status::SUCCESS;
}

tensor_status particle::set_sample_time(double dt_new)
{
    tensor_status status = tensor_status::FAILURE;

    if (dt_new == 0.0)
    {
        return status;
    }

    dt = dt_new; /* Change the sample-time*/
    set_phi(dt_new);
    set_gamma(dt_new); /* Consequently update gamma */
    status = tensor_status::SUCCESS;
    return status;
}

uint8_t particle::get_dimension(void)
{
    return dimension;
}

/******************************************************************************
 * UNIT TESTS
 *****************************************************************************/
#ifdef TESTING_PARTICLE
#include <iostream>

void particle::print(void) 
{
    cout << "radius = " << radius << "\r\n";
    cout << "mass = " << mass << "\r\n";
}

using namespace std;

int main(void)
{
#ifdef TESTING_PARTICLE
    {
        particle a(1.2, 2.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
        a.print();
    }
#endif
    return 0;
}
#endif
