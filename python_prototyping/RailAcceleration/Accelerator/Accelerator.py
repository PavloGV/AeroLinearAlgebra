"""
.. module:: Accelerator.py
	:platform: MacOS, Unix, Windows,
	:synopsis: Electromagnetic Rail Acceleration Object
.. moduleauthor:: Pavlo Vlastos <pvlastos@ucsc.edu>
"""

from ..Containers import State as ST
from ..Constants import Constants as CN

class Accelerator():
    def __init__(self, railLengh=CN, capVolt=CN.capVolt, capCap=CN.capCap):
        """
        :param railLength:
        :param capVolt: 
        :param capCap: 
        """
        # self.capacitor = 
        self.railLength = railLengh
        self.capVolt = capVolt
        self.capCap = capCap
        self.launchStartTime = CN.t0

    def runLaunchStateMachine(self, t):
        """
        :param t: The current time in seconds
        """
        