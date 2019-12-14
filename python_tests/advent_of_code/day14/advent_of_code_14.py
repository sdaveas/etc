from pprint import pprint

class Chemical:
    def __init__(self, quantity, element):
        self.quantity = quantity
        self.element = element

def print_reactions(reactions):
    for r in reactions.keys():
        print("key:", r)
        print("quantity:", reactions[r]['quantity'])
        print("ingredients:")
        for i in reactions[r]['ingredients']:
            print("    ", i.element, i.quantity)


reactions = {}
# reactions['A1'] = {'quantity': 10, 'ingredients': [Chemical(10, 'ORE')]}
# reactions['B'] = {'quantity': 1, 'ingredients': [Chemical(1, 'ORE')]}
# reactions['C'] = {'quantity': 1, 'ingredients': [Chemical(7, 'A'), Chemical(1, 'B')]}
# reactions['D'] = {'quantity': 1, 'ingredients': [Chemical(7, 'A'), Chemical(1, 'C')]}
# reactions['E'] = {'quantity': 1, 'ingredients': [Chemical(7, 'A'), Chemical(1, 'D')]}
# reactions['FUEL'] = {'quantity': 1, 'ingredients': [Chemical(7, 'A'), Chemical(1, 'E')]}

f = open("input_3", "r")
lines = f.read().splitlines()
for l in lines:
    l1 = l.replace(',','').replace('=>','').replace('  ', ' ').split(' ')
    key = l1[-1]
    quantity = int(l1[-2])
    ingr = []
    for i in range(0, len(l1)-2, 2):
        ingr.append(Chemical(int(l1[i]), l1[i+1]))
    reactions[key] = {'quantity': int(quantity), 'ingredients': ingr}

print_reactions(reactions)

def ceiling(value1, value2):
    if value1 % value2 == 0:
        res = int(value1/value2)
    else:
        res = int(value1/value2) + 1
    return res

results = {}

def find_OREs(reactions, target_element, target_quantity, tabs):

    quantity = reactions[target_element]['quantity']
    ingredients = reactions[target_element]['ingredients']

    if ingredients[0].element == 'ORE':
        # res = ceiling(target_quantity, quantity) * ingredients[0].quantity
        if target_element in results:
            results[target_element]+=target_quantity
        else:
            results[target_element]=target_quantity
        t = " "*tabs
        print(t, end= ' ')
        print("element ", target_element, " is made of OREs. We need ", target_quantity)
        return target_quantity

    total = 0
    for i in ingredients:
        t = " "*tabs
        print(t, end= ' ')
        print("element ", target_element, " needed ", i.quantity, " ", i.element)
        total += find_OREs(reactions, i.element, i.quantity * target_quantity, tabs+2)
    return total

find_OREs(reactions, 'FUEL', 1, 0)

print()
pprint(results)


total = 0
for r in results.keys():
    element_needed_quantity = results[r]
    element_react_quantity = reactions[r]['quantity']
    ore_for_element = reactions[r]['ingredients'][0].quantity
    ore = ceiling(element_needed_quantity, element_react_quantity) * ore_for_element
    print("element ", r, " needed ", ore, " ORE")
    total+=ore

print("Total: ", total)
