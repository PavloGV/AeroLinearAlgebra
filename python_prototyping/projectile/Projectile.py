"""
.. module:: Projectile.py
	:platform: MacOS, Unix, Windows,
	:synopsis: A class describing the projectile launched from the rail 
    accelerator
.. moduleauthor:: Pavlo Vlastos <pvlastos@ucsc.edu>
"""
from .models import Dynamics as DY
from .containers import State as ST

class Projectile():
	def __init__(self):
		"""
		Initialize projectile object
		"""
		self.state = ST.State()
		self.model = DY.Model()

