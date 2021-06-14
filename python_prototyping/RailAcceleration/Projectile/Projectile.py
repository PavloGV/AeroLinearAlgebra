"""
.. module:: Projectile.py
    :platform: MacOS, Unix, Windows,
    :synopsis: A class describing the projectile launched from the rail 
    accelerator
.. moduleauthor:: Pavlo Vlastos <pvlastos@ucsc.edu>
"""

from ..Modeling import ProjectileDynamics as PD
from ..Containers import State as ST

class Projectile():
    def __init__(self):
        """
        Initialize projectile object
        """
        self.state = ST.State()
        self.model = PD.Model(self.state)

    def update(self,t,X,u):
        """
        run a step of the dynamic model and update the internal state
        """
        self.model.update(t,X,u)
        self.state.setState(self.model.X)
        
        return self.model.X

