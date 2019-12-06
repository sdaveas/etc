class Visited():
    def __init__(self, visited={}, common=None):
            self.dict = visited
            self.common = common

def find_links(key, orbits):
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

def update_visited_till_existing(visited, _list):
    counter=0;
    for node in _list:
        if node in visited.dict:
            visited.common = node
            visited.dict[visited.common] += counter
            return True
        visited.dict[node] = counter;
        counter+=1;
    return False


orbits = read_orbits('input.txt')
santa_links = find_links('SAN', orbits)
my_links = find_links('YOU', orbits)
visited = Visited()
update_visited_till_existing(visited, santa_links)
update_visited_till_existing(visited, my_links)
print("Overall distance ", visited.dict[visited.common])
