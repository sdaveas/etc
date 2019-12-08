x=25
y=6

with open('input.txt') as f:
    line = f.readline()
z=int(len(line)/x/y)

layers=[]
for h in range(z):
    layers.append({})

min_zero_layers=[0]*z

i=0;
for p in line.strip():
    p=int(p)
    layer=int(i/(x*y))
    if p not in layers[layer]:
        layers[layer][p]=1
    else:
        layers[layer][p]+=1
    if p==0:
        min_zero_layers[layer]+=1
    i+=1

min_zero_layer=min_zero_layers.index(min(min_zero_layers))
print(layers[min_zero_layer][1]*layers[min_zero_layer][2])
