/**
* @file particle.cpp
*
* @brief A class for a particle in various coordinate frames
*
* @author Pavlo Vlastos
*/

#ifndef PARTICLE_H
#define PARTICLE_H

#include "particle.h"
#include "tensor.h"

/******************************************************************************
 * CLASS DEFINITION AND FUNCTION DECLARATIONS
 *****************************************************************************/
class particle
{
private:
    uint8_t dimension = 3;

public:
    double radius = 1.0;
    double mass = 0.0;
    
    tensor position(dimension, 1);
    tensor velocity(dimension, 1);

    /* Class constructors */
    particle(double r, double m, double x, double y, double z, double dx,
             double dy, double dz)
    {
        radius = r; // radius
        mass = m;   // mass

        // Position
        position.content[0][0] = x; // x
        position.content[1][0] = y; // y
        position.content[2][0] = z; // z

        // Velocity
        velocity.content[0][0] = dx; // dx
        velocity.content[1][0] = dy; // dy
        velocity.content[2][0] = dz; // dz
    }
    particle(double r, double m, const vector<double> &a)
    {
        radius = r; // radius
        mass = m;   // mass

        if (a.size() == (3 * dimension))
        {
            // Position
            position.content[0][0] = a[0]; // x
            position.content[1][0] = a[1]; // y
            position.content[2][0] = a[2]; // z

            // Velocity
            velocity.content[0][0] = a[3]; // dx
            velocity.content[1][0] = a[4]; // dy
            velocity.content[2][0] = a[5]; // dz
        }
    }
    particle(double r, double m, const tensor &a)
    {
        radius = r; // radius
        mass = m;   // mass

        if (a.m_height == (3 * dimension))
        {
            // Position
            position.content[0][0] = a.content[0][0]; // x
            position.content[1][0] = a.content[1][0]; // y
            position.content[2][0] = a.content[2][0]; // z

            // Velocity
            velocity.content[0][0] = a.content[3][0]; // dx
            velocity.content[1][0] = a.content[4][0]; // dy
            velocity.content[2][0] = a.content[5][0]; // dz
        }
    }
}

#endif /* PARTICLE_H */
