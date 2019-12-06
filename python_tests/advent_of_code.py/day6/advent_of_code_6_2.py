def find_links(key):
    links = []
    for orbit in orbits:
        try:
            key = orbits[key]
            links.append(key)
        except KeyError:
            break
    return links

def read_orbits(filename='input.txt'):
    orbits = {}
    with open(filename) as f:
        content = f.readlines()

    for line in content:
        pair = line.strip().split(")")
        orbits[pair[1]] = pair[0]

    return orbits

orbits = read_orbits('input.txt')
santa_links = find_links(orbits['SAN'])
my_links = find_links(orbits['YOU'])

santa_distance=0
my_distance=0
found_common = False

for santa_orbit in santa_links:
    if found_common == True:
        break
    santa_distance+=1
    my_distance=0
    for my_orbit in my_links:
        my_distance+=1
        if santa_orbit == my_orbit:
            found_common = True
            # print("Common orbit:", my_orbit)
            break

# print("Santa links:", santa_links)
# print("My links:", my_links)
#
# print("Santa distance:", santa_distance)
# print("My distance:", my_distance)
print("Sum:", santa_distance + my_distance)
