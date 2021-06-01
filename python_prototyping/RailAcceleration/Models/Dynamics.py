"""
.. module:: Dynamics.py
	:platform: MacOS, Unix, Windows,
	:synopsis: Projectile dynamics model in Earth-Centered Earth-Fixed (ECEF)
    coordinates
.. moduleauthor:: Pavlo Vlastos <pvlastos@ucsc.edu>
"""

import numpy as np
from ..Constants import Constants as CN
from ..Containers import State as ST

class Model():
    def __init__(self, state=ST.State):
        """
        Initialize the model with constants for the appropriate model 
        parameters. Using discrete state space notation
        """

        # State vector to carry around
        self.X = np.zeros(CN.stateSize)
        self.setX(state)

        # Discrete dynamics matrix (state transition matrix) 
        dt1 = CN.dt
        dt2 = (CN.dt**2.0)/2.0
        # self.Phi = np.array([
        #     [1.0, 0.0, 0.0, dt1, 0.0, 0.0, dt2, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
        #     [0.0, 1.0, 0.0, 0.0, dt1, 0.0, 0.0, dt2, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
        #     [0.0, 0.0, 1.0, 0.0, 0.0, dt1, 0.0, 0.0, dt2, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
        #     [0.0, 0.0, 0.0, 1.0, 0.0, 0.0, dt1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
        #     [0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, dt1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
        #     [0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, dt1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
        #     [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
        #     [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
        #     [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
        #     [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, dt1, 0.0, 0.0, dt2, 0.0, 0.0, 0.0],
        #     [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, dt1, 0.0, 0.0, dt2, 0.0, 0.0],
        #     [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, dt1, 0.0, 0.0, dt2, 0.0],
        #     [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, dt1, 0.0, 0.0, 0.0],
        #     [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, dt1, 0.0, 0.0],
        #     [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, dt1, 0.0],
        #     [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0],
        #     [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0],
        #     [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0],
        #     [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0]])
        # self.Phi = np.array([
        #     [1.0, 0.0, 0.0, dt1, 0.0, 0.0, dt2, 0.0, 0.0, 0.0],
        #     [0.0, 1.0, 0.0, 0.0, dt1, 0.0, 0.0, dt2, 0.0, 0.0],
        #     [0.0, 0.0, 1.0, 0.0, 0.0, dt1, 0.0, 0.0, dt2, 0.0],
        #     [0.0, 0.0, 0.0, 1.0, 0.0, 0.0, dt1, 0.0, 0.0, 0.0],
        #     [0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, dt1, 0.0, 0.0],
        #     [0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, dt1, 0.0],
        #     [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0],
        #     [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0],
        #     [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0],
        #     [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0]])
        self.Phi = np.array([
            [1.0, 0.0, 0.0, dt1, 0.0, 0.0, 0.0],
            [0.0, 1.0, 0.0, 0.0, dt1, 0.0, 0.0],
            [0.0, 0.0, 1.0, 0.0, 0.0, dt1, 0.0],
            [0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0],
            [0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0],
            [0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0],
            [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0]])

        # Discrete input matrix
        # self.Gamma = np.array([[dt2/CN.massProjectile, 0.0, 0.0],
        #                         [0.0, dt2/CN.massProjectile, 0.0],
        #                         [0.0, 0.0, dt2/CN.massProjectile],
        #                         [dt1/CN.massProjectile, 0.0, 0.0],
        #                         [0.0, dt1/CN.massProjectile, 0.0],
        #                         [0.0, 0.0, dt1/CN.massProjectile],
        #                         [1.0/CN.massProjectile, 0.0, 0.0],
        #                         [0.0, 1.0/CN.massProjectile, 0.0],
        #                         [0.0, 0.0, 1.0/CN.massProjectile],
        #                         [0.0, 0.0, 0.0],
        #                         [0.0, 0.0, 0.0],
        #                         [0.0, 0.0, 0.0],
        #                         [0.0, 0.0, 0.0],
        #                         [0.0, 0.0, 0.0],
        #                         [0.0, 0.0, 0.0],
        #                         [0.0, 0.0, 0.0],
        #                         [0.0, 0.0, 0.0],
        #                         [0.0, 0.0, 0.0],
        #                         [0.0, 0.0, 0.0]])
        # self.Gamma = np.array([[dt2/CN.massProjectile, 0.0, 0.0],
        #                         [0.0, dt2/CN.massProjectile, 0.0],
        #                         [0.0, 0.0, dt2/CN.massProjectile],
        #                         [dt1/CN.massProjectile, 0.0, 0.0],
        #                         [0.0, dt1/CN.massProjectile, 0.0],
        #                         [0.0, 0.0, dt1/CN.massProjectile],
        #                         [1.0/CN.massProjectile, 0.0, 0.0],
        #                         [0.0, 1.0/CN.massProjectile, 0.0],
        #                         [0.0, 0.0, 1.0/CN.massProjectile],
        #                         [0.0, 0.0, 0.0]])
        self.Gamma = np.array([[dt2/CN.massProjectile, 0.0, 0.0],
                                [0.0, dt2/CN.massProjectile, 0.0],
                                [0.0, 0.0, dt2/CN.massProjectile],
                                [dt1/CN.massProjectile, 0.0, 0.0],
                                [0.0, dt1/CN.massProjectile, 0.0],
                                [0.0, 0.0, dt1/CN.massProjectile],
                                [0.0, 0.0, 0.0]])

        # Discrete observation matrix
        self.H = np.eye(CN.stateSize)

        # Measurement vector
        self.Y = np.matmul(self.H, self.X)

    def update(self, t, X):
        """
        :param t: a time scalar value
        :param F: The net force acting upon the projectile
        :param X: A projectile state vector and the force vector concatenated 
        together
        :return: A projectile state vector and the force vector concatenated 
        together
        """

        # print('X={}'.format(X))
        # print('X.shape={}'.format(X.shape))

        # Set the state vector
        self.X = X[0:CN.stateSize]
        
        # Input
        u = X[CN.stateSize:]

        # print('u.shape={}'.format(u.shape))
        # print('self.X.shape={}'.format(self.X.shape))
        # print('self.Phi.shape={}'.format(self.Phi.shape))
        # print('self.Gamma.shape={}'.format(self.Gamma.shape))

        # Apply the famous state space formulation
        self.X = (self.Phi @ self.X) + (self.Gamma @ u)

        # state = ST.State
        # state.setState(self.X)

        # Update Measurement vector
        # TODO: Limit the observation matrix so that some states are hidden
        self.Y = self.H @ self.X

        Yi = np.concatenate((self.X, u))
        # print('Yi={}'.format(Yi))

        return Yi
        
    def setX(self, state=ST.State()):
        """
        Set the state vector, which is the X attribute for the dynamics object
        :param state: A state object
        :return: None
        """

        # Linear
        self.X[0] = state.x
        self.X[1] = state.y
        self.X[2] = state.z
        self.X[3] = state.dx
        self.X[4] = state.dy
        self.X[5] = state.dz
        # self.X[6] = state.ddx
        # self.X[7] = state.ddy
        # self.X[8] = state.ddz
        
        # # Angular
        # self.X[9] = state.roll
        # self.X[10] = state.pitch
        # self.X[11] = state.yaw
        # self.X[12] = state.p
        # self.X[13] = state.q
        # self.X[14] = state.r
        # self.X[15] = state.dp
        # self.X[16] = state.dq
        # self.X[17] = state.dr

        # # Propellant
        # self.X[18] = state.mass

        self.X[6] = state.mass
        
    def getX(self):
        return self.X



