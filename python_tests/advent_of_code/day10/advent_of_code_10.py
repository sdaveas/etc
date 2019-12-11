from pprint import pprint
import math
def det(a,b):
    a0 = a['x']
    a1 = a['y']
    b0 = b['x']
    b1 = b['y']
    return a0*b1 - a1*b0
def angle(a,b):
    a0 = a['x']
    a1 = a['y']
    b0 = b['x']
    b1 = b['y']
    if (b0-a0) == 0:
        return float('-inf')
    return (b1-a1)/(b0-a0)

def insert_or_update(d, key, value=1):
    if key in d:
        d[key].append(value)
    else:
        d[key] = [value]

def insert_at_left(origin, other):
    if origin['x'] > other['x']:
        return True;
    if origin['x'] == other['x']:
        return origin['y']<other['y']
    return False

points = []
with open('input') as f:
    content = f.readlines()

x=0;
y=0;
for line in content:
    x=0
    for c in line:
        if c == '#':
            points.append({'x':x, 'y':y})
        x+=1
    y+=1

lines = []
for origin in points:
    origin = {'x':8, 'y':16}
    right_coss={}
    left_coss={}
    for other in points:
        if origin == other:
            continue
        # if (det(origin, other)>=0):
        if (insert_at_left(origin, other)):
            insert_or_update(left_coss, angle(origin, other), other)
        else:
            insert_or_update(right_coss, angle(origin, other), other)
    lines.append(len(right_coss) + len(left_coss))
    if lines[-1]==214:
        print(origin)
print(max(lines))
print()

sorted_right = []
for key in right_coss.keys():
    sorted_right.append(key)
sorted_right.sort()

sorted_left = []
for key in left_coss.keys():
    sorted_left.append(key)
sorted_left.sort()

c = 0
for i in sorted_right:
    print(c, right_coss[i])
    c+=1

for i in sorted_left:
    print(c, left_coss[i])
    c+=1
