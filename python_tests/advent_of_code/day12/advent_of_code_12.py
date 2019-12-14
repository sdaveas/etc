from matplotlib import pyplot as plt
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

init_pots = []
init_kins = []
for p in range(4):
    planet = planets[p]
    init_pots.append(abs(planet[x]) + abs(planet[y]) + abs(planet[z]))
    v = planet[vel]
    init_kins.append(abs(v[x]) + abs(v[y]) + abs(v[z]))

pprint(init_pots)
pprint(init_kins)


pots = []
kins = []
totals = []
total = 0
rounds = []
r = 10000000

pot_periods = [0, 0, 0, 0]
kin_periods = [0, 0, 0, 0]

for i in range(r):
    rounds.append(i)

    apply_gravity(planets[0], [planets[1], planets[2], planets[3]])
    apply_gravity(planets[1], [planets[0], planets[2], planets[3]])
    apply_gravity(planets[2], [planets[0], planets[1], planets[3]])
    apply_gravity(planets[3], [planets[0], planets[1], planets[2]])

    apply_velocity(planets[0])
    apply_velocity(planets[1])
    apply_velocity(planets[2])
    apply_velocity(planets[3])

    total = 0
    for p in range(4):
        planet = planets[p]
        pots.append(abs(planet[x]) + abs(planet[y]) + abs(planet[z]))
        v=planet[vel]
        kins.append(abs(v[x]) + abs(v[y]) + abs(v[z]))
        totals.append(pots[-1] * kins[-1])
        total += totals[-1]

    if planets[0][x] == 5 and planets[0][y] == 13 and planets[0][z] == -3:
        print("Planet 0:", round)
    if planets[1][x] == 18 and planets[1][y] == -6 and planets[0][z] == 13:
        print("Planet 1:", round)
    if planets[2][x] == 16 and planets[2][y] == 3 and planets[2][z] == 4:
        print("Planet 2:", round)
    if planets[3][x] == 0 and planets[3][y] == 8 and planets[3][z] == 8:
        print("Planet 3:", round)

print("total:", total)

print("Sum of periods:", pot_periods[0]*pot_periods[1]*pot_periods[2]*pot_periods[3])
