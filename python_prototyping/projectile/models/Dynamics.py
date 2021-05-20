"""
.. module:: Dynamics.py
	:platform: MacOS, Unix, Windows,
	:synopsis: Projectile dynamics model in Earth-Centered Earth-Fixed (ECEF)
    coordinates
.. moduleauthor:: Pavlo Vlastos <pvlastos@ucsc.edu>
"""

import numpy as np
from ..constants import Constants as CN
from ..containers import State as ST

class Model():
    def __init__(self):
        """
        Initialize the model with constants for the appropriate model 
        parameters. Using discrete state space notation
        """

        # State vector to carry around
        self.X = np.zeros((CN.stateSize, 1))

        # Discrete dynamics matrix (state transition matrix) 
        self.Phi = np.array([
            [1.0, 0.0, 0.0, CN.dt, 0.0, 0.0, CN.dt**2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
            [0.0, 1.0, 0.0, 0.0, CN.dt, 0.0, 0.0, CN.dt**2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
            [0.0, 0.0, 1.0, 0.0, 0.0, CN.dt, 0.0, 0.0, CN.dt**2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
            [0.0, 0.0, 0.0, 1.0, 0.0, 0.0, CN.dt, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
            [0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, CN.dt, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
            [0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, CN.dt, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
            [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
            [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
            [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
            [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, CN.dt, 0.0, 0.0, CN.dt**2.0, 0.0, 0.0],
            [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, CN.dt, 0.0, 0.0, CN.dt**2.0, 0.0],
            [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, CN.dt, 0.0, 0.0, CN.dt**2.0],
            [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, CN.dt, 0.0, 0.0],
            [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, CN.dt, 0.0],
            [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, CN.dt],
            [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0],
            [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0],
            [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0]])

        # Discrete input matrix
        self.Gamma = np.array([[0.0],
                                [0.0],
                                [0.0],
                                [0.0],
                                [0.0],
                                [0.0],
                                [1.0/CN.mass],
                                [1.0/CN.mass],
                                [1.0/CN.mass],
                                [0.0],
                                [0.0],
                                [0.0],
                                [0.0],
                                [0.0],
                                [0.0],
                                [0.0],
                                [0.0],
                                [0.0]])

        # Discrete observation matrix
        self.H = np.eye(CN.stateSize)

        # Measurement vector
        self.Y = np.matmul(self.H, self.X)

    def update(self, Fx, Fy, Fz, state=ST.State()):
        """
        :param Fx: The net force acting upon the projectile in the body x-axis
        :param Fy: The net force acting upon the projectile in the body y-axis
        :param Fz: The net force acting upon the projectile in the body z-axis
        :param state: A projectile state vector
        """

        # input
        u = np.array([[Fx],
                      [Fy],
                      [Fz]])

        # Set the state vector
        self.setX(state)

        # Apply the famous state space formulation
        self.X = np.matmul(self.Phi, self.X) + np.matmul(self.Gamma, u)

        # Update Measurement vector
        # TODO: Limit the observation matrix so that some states are hidden
        self.Y = np.matmul(self.H, self.X)
        
    def setX(self, state=ST.State()):
        """
        Set the state vector, which is the X attribute for the dynamics object
        :param state: A state object
        :return: None
        """

        # Linear
        self.X[0][0] = state.x
        self.X[1][0] = state.y
        self.X[2][0] = state.z
        self.X[3][0] = state.dx
        self.X[4][0] = state.dy
        self.X[5][0] = state.dz
        self.X[6][0] = state.ddx
        self.X[7][0] = state.ddy
        self.X[8][0] = state.ddz
        
        # Angular
        self.X[9][0] = state.roll
        self.X[10][0] = state.pitch
        self.X[11][0] = state.yaw
        self.X[12][0] = state.p
        self.X[13][0] = state.q
        self.X[14][0] = state.r
        self.X[15][0] = state.dp
        self.X[16][0] = state.dq
        self.X[17][0] = state.dr
        



