"""
.. module:: launch_sim.py
	:platform: MacOS, Unix, Windows,
	:synopsis: Simulation of launching projectile with a rail accelerator to 
    orbit
.. moduleauthor:: Pavlo Vlastos <pvlastos@ucsc.edu>
"""

# from .accelerator import Accelerator as AR
import projectile.Projectile as PR


# print("Building accelerator (Amy)...")
# Amy = AR.Accelerator()
# print("Finished building accelerator (Amy)")

print("Building projectile...")
Jack = PR.Projectile()
print("Finished building projectile (Jack)")

# Main Loop
