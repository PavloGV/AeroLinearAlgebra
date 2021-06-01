"""
.. module:: Projectile.py
	:platform: MacOS, Unix, Windows,
	:synopsis: A class describing the projectile launched from the rail 
    accelerator
.. moduleauthor:: Pavlo Vlastos <pvlastos@ucsc.edu>
"""

from ..Models import Dynamics as DY
from ..Containers import State as ST
import numpy as np

class Projectile():
	def __init__(self):
		"""
		Initialize projectile object
		"""
		self.state = ST.State()
		self.model = DY.Model(self.state)


	def update(self,t,X,u):
		#run a step of the dynamic model and update the internal state
		self.model.update(t,X,u)
		self.state.setState(self.model.X)

		return self.model.X

	#form the update step as f(t,Y) for scipy Runge Kutta
	#the last 3 elements of X_combined are the input forces
	#this does not apparently work
	def RK_update(self,t,X_combined):
		length = X_combined.size
		x = X_combined[:length-3]
		u = X_combined[-3:]
		X_out = self.update(t,x,u)
		X_out = np.concatenate((X_out,u))
		return X_out



