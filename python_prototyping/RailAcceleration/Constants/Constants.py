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

massEarth = 5.972*(10.0**24.0) # Earth's mass in kg

G = 6.67408*(10.0**(-11.0))

scale = 2.0

xmin = -radiusEarth*scale
xmax =  radiusEarth*scale

ymin = -radiusEarth*scale
ymax =  radiusEarth*scale

zmin = -radiusEarth*scale
zmax =  radiusEarth*scale

###############################################################################
# Timing
dt = 0.05	  	# sample time in seconds
t0 = 0.0 		# Start time of simulation in seconds
tf = 4000.0 		# Stop time of simulation in seconds

###############################################################################
# Projectile Constants
massProjectile = 1252.0 	# projectile mass in kg

# Initial Earth-Centered Earth-Fixed (ECEF) coordinates 
# Santa Cruz, CA, USA
x0 = -2705678.0 # x-coordinate in m
y0 = -4325150.0 # y-coordinate in m
z0 = 3815106.0  # z-coordinate in m

# State size
stateSize = 19

###############################################################################
# Planet