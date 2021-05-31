"""
.. module:: Rotations.py
	:platform: MacOS, Unix, Windows,
	:synopsis: Rotation library
.. moduleauthor:: Pavlo Vlastos <pvlastos@ucsc.edu>
"""

import numpy as np

def dcmFromEuler(psi, theta, phi):
    cpsi = np.cos(psi)
    ctheta = np.cos(theta)
    cphi = np.cos(phi)

    spsi = np.sin(psi)
    stheta = np.sin(theta)
    sphi = np.sin(phi)

    R = np.zeros((3,3))

    R[0][0] = cpsi*ctheta
    R[0][1] = spsi*ctheta
    R[0][2] = -stheta

    R[1][0] = cpsi * stheta * sphi - spsi * cphi
    R[1][1] = spsi * stheta * sphi + cpsi * cphi
    R[1][2] = ctheta * sphi

    R[2][0] = cpsi * stheta * cphi + spsi * sphi
    R[2][1] = spsi * stheta * cphi - cpsi * sphi
    R[2][2] = ctheta * cphi

    return R

def EulerAnglesFromDCM(R):
    """
    :param R: A direction cosine matrix (DCM)
    :return: Euler angles: psi, theta, phi in radians
    """
    psi = np.arctan2(R[1][0], R[0][0])
    theta = np.arcsin(-R[2][0])
    phi = np.arctan2(R[2][1], R[2][2])

    return [psi, theta, phi]

def rotationAngleFrom2vectors(u, v):
    """
    :param u: A 3 x 1 numpy array
    :param v: A 3 x 1 numpy array
    :return: Relative angle between u and v in radians
    """
    return np.arccos(np.dot(u.T, v)/(np.linalg.norm(u)*np.linalg.norm(v)))

def dcmFromAngleAndVector(angle, v):
    """
    :param angle: The angle of rotatino about the axis of rotation unit vector
    :param v: The unit vector rpresenting the axis of rotation. 3 x 1 numpy 
    array
    :return: dcm The direction cosine matirx, a rotation matrix
    """

    ca = np.cos(angle)
    sa = np.sin(angle)
    print('v.shape={}'.format(v.shape))
    print('ca.shape={}'.format(ca.shape))
    print('sa.shape={}'.format(sa.shape))

    dcm = np.zeros((3,3))
    print('dcm[0][0]={}'.format( v[0] * v[0] + (v[1] * v[1] + v[2] * v[2]) * ca))

    dcm[0][0] = v[0] * v[0] + (v[1] * v[1] + v[2] * v[2]) * ca
    dcm[0][1] = v[0] * v[1]*(1 - ca) - v[2] * sa
    dcm[0][2] = v[0] * v[2]*(1 - ca) + v[1] * sa

    dcm[1][0] = v[0] * v[1]*(1 - ca) + v[2] * sa
    dcm[1][1] = v[1] * v[1] + (v[2] * v[2] + v[0] * v[0]) * ca
    dcm[1][2] = v[1] * v[2]*(1 - ca) - v[0] * sa

    dcm[2][0] = v[2] * v[0]*(1 - ca) - v[1] * sa
    dcm[2][1] = v[1] * v[2]*(1 - ca) + v[0] * sa
    dcm[2][2] = v[2] * v[2] + (v[0] * v[0] + v[1] * v[1]) * ca

    return dcm