"""
.. module:: Constants.py
	:platform: MacOS, Unix, Windows,
	:synopsis: Constants
.. moduleauthor:: Pavlo Vlastos <pvlastos@ucsc.edu>
"""

###############################################################################
# Accelerator Constants

###############################################################################
# Planet and General Plotting Constants
radiusEarth = 6371000 # Earth's radius in meters

xmin = -radiusEarth*3.0
xmax =  radiusEarth*3.0

ymin = -radiusEarth*3.0
ymax =  radiusEarth*3.0

zmin = -radiusEarth*3.0
zmax =  radiusEarth*3.0

###############################################################################
# Timing
dt = 0.05	  	# sample time in seconds
t0 = 0.0 		# Start time of simulation in seconds
tf = 100.0 		# Stop time of simulation in seconds

###############################################################################
# Projectile Constants
mass = 1252.0 	# projectile mass in kg

# Initial Earth-Centered Earth-Fixed (ECEF) coordinates
x0 = -2705678.0 # x-coordinate in m
y0 = -4325150.0 # y-coordinate in m
z0 = 3815106.0  # z-coordinate in m

# State size
stateSize = 18

###############################################################################
# Planet