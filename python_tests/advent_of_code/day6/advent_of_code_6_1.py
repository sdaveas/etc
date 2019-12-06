orbits = {}

with open('input.txt') as f:
    content = f.readlines()

distance = 0
distances = {}
for line in content:
    value, key = line.strip().split(")")
    orbits[key] = value
    if value not in distances:
        distances[key] = 1
    else:
        distances[key] = distances[value]+1
    distance+=distances[key]
print(distances)
print(orbits)

# links = 0
# for key in orbits:
#     for orbit in orbits:
#         try:
#             key = orbits[key]
#             links += 1
#         except KeyError:
#             break

print("sum:", distance)
