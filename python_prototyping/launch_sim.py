"""
.. module:: launch_sim.py
	:platform: MacOS, Unix, Windows,
	:synopsis: Simulation of launching projectile with a rail accelerator to 
    orbit
.. moduleauthor:: Pavlo Vlastos <pvlastos@ucsc.edu>
"""


# from .accelerator import Accelerator as AR
import RailAcceleration.Projectile.Projectile as PR
import RailAcceleration.Constants.Constants as CN
import RailAcceleration.Utilities.Rotations as ROT
import numpy as np

import matplotlib
from matplotlib import cm
import matplotlib.pyplot as plt
from matplotlib import gridspec
from matplotlib.markers import MarkerStyle
import matplotlib.animation as animation

a = CN
##############################################################################
# print("Building accelerator (Amy)...")
# Amy = AR.Accelerator()
# print("Finished building accelerator (Amy)")

print("Building {} object".format(PR.Projectile.__name__))
Jack = PR.Projectile()
print("Finished building {} object".format(PR.Projectile.__name__))

##############################################################################
# Setup Graphing
fig = plt.figure(figsize=(10,8))

gs = gridspec.GridSpec(nrows=2, ncols=6)
ax0 = fig.add_subplot(gs[0:2, 0:3], projection='3d')
fig.tight_layout(pad=4.0)

plt.show(block=False)

# 3D Plot
ax0.set_title('Projectile Position Over Time')

ax0.set_xlim(CN.xmin, CN.xmax)
ax0.set_ylim(CN.ymin, CN.ymax)
ax0.set_zlim(CN.zmin, CN.zmax)

ax0.view_init(80, -122)

ax0.set_xlabel("X (meters)")
ax0.set_ylabel("Y (meters)")
ax0.set_zlabel("Z (meters)")

ax0.grid()

# Record Projectile Position, TODO: velocity, acceleration, etc...
# Should be Mx1 vectors
x = np.array([Jack.state.x]) 
y = np.array([Jack.state.y])
z = np.array([Jack.state.z])

position = ax0.plot(x, y, z, lw=2, marker='.', color='red')[0]

# Intial launch vector
r = np.array([[Jack.state.x],
              [Jack.state.y],
              [Jack.state.z]])

R = ROT.dcmFromEuler(np.pi/2.0, 0.0, 0.0)

p = np.matmul(R, r) + r

ilvx = np.array([r[0][0],
                 p[0][0]])
ilvy = np.array([r[1][0],
                 p[1][0]])
ilvz = np.array([r[2][0],
                 p[2][0]])

ilv = ax0.plot(ilvx[:], ilvy[:], ilvz[:], lw=3, marker='.', 
               color='black')

# Sphere
u, v = np.mgrid[0:2*np.pi:20j, 0:np.pi:10j]
sphx = np.cos(u)*np.sin(v)*CN.radiusEarth
sphy = np.sin(u)*np.sin(v)*CN.radiusEarth
sphz = np.cos(v)*CN.radiusEarth

sphere = ax0.plot_wireframe(sphx, sphy, sphz, color="blue")

# Final Setup Steps
fig.canvas.draw()

background0 = fig.canvas.copy_from_bbox(ax0.bbox)

##############################################################################
# Main Loop Setup

# Timing
t = np.arange(CN.t0, CN.tf, CN.dt)
maxStepNum = len(t)
steps = range(0, maxStepNum)

##############################################################################
# Main Loop
graphInterval = 200
for k in steps:

    r = np.array([[Jack.state.x],
                  [Jack.state.y],
                  [Jack.state.z]])
    
    rmag = np.linalg.norm(r)

    r2 = rmag**2.0

    FgMag = CN.G*CN.massEarth*CN.massProjectile/r2

    Fg = FgMag * r/rmag

    if t[k] < 12.0:
        # pmag = np.linalg.norm(p)
        # Fi = 100*(p-r)/pmag
        Fi = np.array([[100],
                       [0],
                       [0]])

    else:
        Fi = np.array([[0],
                       [0],
                       [0]])

    Fsum = Fi - Fg

    Fx = Fsum[0][0]
    Fy = Fsum[1][0]
    Fz = Fsum[2][0]

    Jack.state = Jack.model.update(Fx, Fy, Fz, Jack.state)

    # Graphing Update
    if np.mod(k, graphInterval) == 0:

        x = np.concatenate((x, np.array([Jack.state.x])), axis=0) 
        y = np.concatenate((y, np.array([Jack.state.y])), axis=0)
        z = np.concatenate((z, np.array([Jack.state.z])), axis=0)

        # print("k = {}, x = {}, y = {}, z = {}".format(k, x[-1], y[-1], z[-1]))
        print("k = {}, Fx = {}, Fy = {}, Fz = {}".format(k, Fx, Fy, Fz))

        position.set_data(x, y)
        position.set_3d_properties(z)

        fig.canvas.restore_region(background0)
        
        ax0.draw_artist(position)

        fig.canvas.blit(ax0.bbox)
        fig.canvas.flush_events()
