import numpy

x=25
y=6

with open('input.txt') as f:
    line = f.readline()
z=int(len(line)/x/y)

layers = numpy.zeros((z, y, x))

i=0
for p in line.strip():
    layer=int(i/(x*y))
    layers[layer][int(i/x)%y][i%x]=p
    i+=1

colors=numpy.zeros((x, y))

for _x in range(x):
    for _y in range(y):
        for _z in range(z):
            color=layers[_z][_y][_x]
            if color!=2:
                break
        colors[_x][_y] = color

for _y in range(y):
    for _x in range(x):
        if colors[_x][_y]==0:
            print("   ", end='')
        elif colors[_x][_y]==1:
            print(" O ", end='')
        else:
            print(" . ", end='')
    print()
