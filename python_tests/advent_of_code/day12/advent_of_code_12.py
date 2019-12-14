import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D
from pprint import pprint

# <x= 5, y=13, z=-3>
# <x=18, y=-7, z=13>
# <x=16, y= 3, z= 4>
# <x= 0, y= 8, z= 8>

x = 'x'
y = 'y'
z = 'z'
vel = 'vel'

def apply_gravity(planet, others):
    for other in others:
        for dim in [x, y, z]:
            if planet[dim] < other[dim]:
                planet[vel][dim]+=1
            elif planet[dim] > other[dim]:
                planet[vel][dim]-=1

def apply_velocity(planet):
    planet[x]+=planet[vel][x]
    planet[y]+=planet[vel][y]
    planet[z]+=planet[vel][z]

planets = []
planets.append({x:  5, y: 13, z: -3, vel:{x: 0, y: 0, z: 0}})
planets.append({x: 18, y: -7, z: 13, vel:{x: 0, y: 0, z: 0}})
planets.append({x: 16, y:  3, z:  4, vel:{x: 0, y: 0, z: 0}})
planets.append({x:  0, y:  8, z:  8, vel:{x: 0, y: 0, z: 0}})

for i in range(1000):
    apply_gravity(planets[0], [planets[1], planets[2], planets[3]])
    apply_gravity(planets[1], [planets[0], planets[2], planets[3]])
    apply_gravity(planets[2], [planets[0], planets[1], planets[3]])
    apply_gravity(planets[3], [planets[0], planets[1], planets[2]])

    apply_velocity(planets[0])
    apply_velocity(planets[1])
    apply_velocity(planets[2])
    apply_velocity(planets[3])

pots = []
kins = []
totals = []
total = 0
for p in range(4):
    planet = planets[p]
    pots.append(abs(planet[x]) + abs(planet[y]) + abs(planet[z]))
    v=planet[vel]
    kins.append(abs(v[x]) + abs(v[y]) + abs(v[z]))
    totals.append(pots[p] * kins[p])
    total+=totals[p]

print("total:", total)



