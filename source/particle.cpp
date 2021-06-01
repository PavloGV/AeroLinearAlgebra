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
 * DEFINES
 *****************************************************************************/

/******************************************************************************
 * PUBLIC FUNCTION IMPLEMENTATIONS
 *****************************************************************************/
tensor_status particle::update(void)
{
    tensor_status status = tensor_status::FAILURE;

    state = add(multiply(phi, state), multiply(gamma, u));

    status = tensor_status::SUCCESS;

    return status;
}

/******************************************************************************
 * Setters
******************************************************************************/
tensor_status particle::set_u(const double fnx, const double fny,
                              const double fnz, const double ftx,
                              const double fty, const double ftz)
{
    /* The components of the force normal to the surface of the sphere. These
     * components can impart linear momentum only. */
    u.content[0][0] = fnx;
    u.content[1][0] = fny;
    u.content[2][0] = fnz;

    /* The components of the force tangent to the particle's sphere. These
     * components only create moments that can rotate the particle. */
    u.content[3][0] = ftx;
    u.content[4][0] = fty;
    u.content[5][0] = ftz;

    return tensor_status::SUCCESS;
}

tensor_status particle::set_mass(const double mass)
{
    this->mass = mass;
    moi = 2.0 * (mass * radius * radius) / 5.0; /* Moment of inertia */
    return tensor_status::SUCCESS;
}

tensor_status particle::set_radius(const double radius)
{
    this->radius = radius;
    moi = 2.0 * (mass * radius * radius) / 5.0; /* Moment of inertia */
    return tensor_status::SUCCESS;
}

tensor_status particle::set_moi(const double mass, const double radius)
{
    set_mass(mass);
    set_radius(radius);
    this->moi = 2.0 * (mass * radius * radius) / 5.0; /* Moment of inertia */
    return tensor_status::SUCCESS;
}

tensor_status particle::set_sample_time(double dt_new)
{
    if (dt_new == 0.0)
    {
        return tensor_status::FAILURE;
    }

    dt = dt_new; /* Change the sample-time*/
    // set_phi(dt_new);
    // set_gamma(dt_new); /* Consequently update gamma */
    return tensor_status::SUCCESS;
    ;
}
/******************************************************************************
 * Getters
******************************************************************************/
tensor particle::get_state(void)
{
    return copy(state);
}

void particle::print(void)
{
    cout << "radius = " << radius << " meters\r\n";
    cout << "mass = " << mass << " kg\r\n";
    cout << "moment of inertia = " << moi << "\r\n";
    cout << "state (X):\r\n";
    state.print();
    cout << "dynamics matrix (Phi):\r\n";
    phi.print();
    cout << "input matrix (Gamma):\r\n";
    gamma.print();
    cout << "input vector (u):\r\n";
    u.print();
}
/******************************************************************************
 * UNIT TESTS
 *****************************************************************************/
#ifdef TESTING_PARTICLE

int main(void)
{
#ifdef TEST_PARTICLE_PRINT
    {
        cout << "TEST_PARTICLE_PRINT\r\n";
        particle a(1.2, 2.5, 0.0);
        a.print();
    }
#endif

#ifdef TEST_PARTICLE_UPDATE
    {
        cout << "TEST_PARTICLE_UPDATE\r\n";
        particle a(1.2, 2.5, -1.125);
        a.set_mass(0.001);
        a.print();
        cout << "state (X):\r\n";
        a.get_state().print();

        /* Simulate a step response (an initial force impulse, and then take
         * the force away after 1 time step) */
        a.set_u(2000.0, 1000.0, 0.0, 0.0, 0.0, 0.0);
        for (unsigned int i = 0; i < 1000; i++)
        {
            if (i == 1)
            {
                a.set_u(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
            }
            a.update();
        }
        cout << "state (X):\r\n";
        a.get_state().print();
    }
#endif
    return 0;
}
#endif
