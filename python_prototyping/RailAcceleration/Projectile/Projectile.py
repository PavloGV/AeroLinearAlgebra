"""
.. module:: Projectile.py
	:platform: MacOS, Unix, Windows,
	:synopsis: A class describing the projectile launched from the rail 
    accelerator
.. moduleauthor:: Pavlo Vlastos <pvlastos@ucsc.edu>
"""

from ..Models import Dynamics as DY
from ..Containers import State as ST

class Projectile():
	def __init__(self):
		"""
		Initialize projectile object
		"""
		self.state = ST.State()
		self.model = DY.Model()

