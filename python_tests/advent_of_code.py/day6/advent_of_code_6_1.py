orbits = {}

with open('input.txt') as f:
    content = f.readlines()

for line in content:
    pair = line.strip().split(")")
    orbits[pair[1]] = pair[0]

links = 0
for key in orbits:
    for orbit in orbits:
        try:
            key = orbits[key]
            links += 1
        except KeyError:
            break

print("sum:", links)
