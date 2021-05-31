"""
.. module:: State.py
	:platform: MacOS, Unix, Windows,
	:synopsis: Projectile state based in Earth-Centered Earth-Fixed (ECEF) 
    coordinates. The projectile is assumed to be initially at rest with respect
    to Earth
.. moduleauthor:: Pavlo Vlastos <pvlastos@ucsc.edu>
"""

import numpy as np
from ..Constants import Constants as CN

class State():
    def __init__(self, x0=CN.x0, y0=CN.y0, z0=CN.z0, 
                 mass0=CN.massProjectile):
        """
        Initialize projectile state
        """

        self.x = x0         # x position in meters
        self.y = y0         # y position in meters
        self.z = z0         # z position in meters
        self.dx = 0.0       # velocity x in meters per second
        self.dy = 0.0       # velocity y in meters per second
        self.dz = 0.0       # velocity z in meters per second
        self.ddx = 0.0      # acceleration x in meters per second^2
        self.ddy = 0.0      # acceleration y in meters per second^2
        self.ddz = 0.0      # acceleration z in meters per second^2
        self.roll = 0.0     # roll angle in radians
        self.pitch = 0.0    # pitch angle in radians
        self.yaw = 0.0      # yaw angle in radians
        self.p = 0.0        # angular velocity about x-axis in rad/s
        self.q = 0.0        # angular velocity about y-axis in rad/s
        self.r = 0.0        # angular velocity about z-axis in rad/s
        self.dp = 0.0       # angular acceleration x-axis in rad/s^2
        self.dq = 0.0       # angular acceleration y-axis in rad/s^2
        self.dr = 0.0       # angular acceleration z-axis in rad/s^2
        self.mass = mass0

    def setState(self, stateVector):
        """
        :param stateVector: An 19x1 np.array([[]]) vector
        :return: None
        """
        
        # Linear
        self.x = stateVector[0] 
        self.y = stateVector[1] 
        self.z = stateVector[2] 

        self.dx = stateVector[3] 
        self.dy = stateVector[4] 
        self.dz = stateVector[5] 

        self.ddx = stateVector[6] 
        self.ddy = stateVector[7] 
        self.ddz = stateVector[8] 
        
        # Angular
        self.roll  = stateVector[9] 
        self.pitch = stateVector[10]
        self.yaw = stateVector[11]

        self.p = stateVector[12]
        self.q = stateVector[13]
        self.r = stateVector[14]

        self.dp = stateVector[15]
        self.dq = stateVector[16]
        self.dr = stateVector[17]
        
        self.mass = stateVector[18]

    def setOrientation(self, phi, theta, psi):
        """
        :param phi: Roll ange in radians
        :param theta: Pitch ange in radians
        :param psi: Yaw ange in radians
        """
        self.roll = phi
        self.pitch = theta
        self.yaw = psi
