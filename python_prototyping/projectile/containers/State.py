"""
.. module:: State.py
	:platform: MacOS, Unix, Windows,
	:synopsis: Projectile state based in Earth-Centered Earth-Fixed (ECEF) 
    coordinates. The projectile is assumed to be initially at rest with respect
    to Earth
.. moduleauthor:: Pavlo Vlastos <pvlastos@ucsc.edu>
"""

import numpy as np
from ..constants import Constants

class State():
    def __init__(self, x0=Constants.x0, y0=Constants.y0, z0=Constants.z0):
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

    def setState(self, stateVector):
        """
        :param stateVector: An 18x1 np.array([[]]) vector
        :return: None
        """
        
        # Linear
        self.x = self.stateVector[0][0] 
        self.y = self.stateVector[1][0] 
        self.z = self.stateVector[2][0] 
        self.dx = self.stateVector[3][0] 
        self.dy = self.stateVector[4][0] 
        self.dz = self.stateVector[5][0] 
        self.ddx = self.stateVector[6][0] 
        self.ddy = self.stateVector[7][0] 
        self.ddz = self.stateVector[8][0] 
        
        # Angular
        self.roll  = self.stateVector[9][0] 
        self.pitch = self.stateVector[10][0]
        self.yaw = self.stateVector[11][0]
        self.p = self.stateVector[12][0]
        self.q = self.stateVector[13][0]
        self.r = self.stateVector[14][0]
        self.dp = self.stateVector[15][0]
        self.dq = self.stateVector[16][0]
        self.dr = self.stateVector[17][0]
