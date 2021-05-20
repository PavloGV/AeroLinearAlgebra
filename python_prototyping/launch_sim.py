"""
.. module:: launch_sim.py
	:platform: MacOS, Unix, Windows,
	:synopsis: Simulation of launching projectile with a rail accelerator to 
    orbit
.. moduleauthor:: Pavlo Vlastos <pvlastos@ucsc.edu>
"""


# from .accelerator import Accelerator as AR
import RailAcceleration.Projectile.Projectile as PR

# print("Building accelerator (Amy)...")
# Amy = AR.Accelerator()
# print("Finished building accelerator (Amy)")



print("Building {} object".format(PR.Projectile.__name__))
Jack = PR.Projectile()
print("Finished building {} object".format(PR.Projectile.__name__))

# Main Loop
