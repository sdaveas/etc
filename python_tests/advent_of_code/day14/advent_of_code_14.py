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

f = open("input_5", "r")
lines = f.read().splitlines()
for l in lines:
    l1 = l.replace(',','').replace('=>','').replace('  ', ' ').split(' ')
    key = l1[-1]
    quantity = int(l1[-2])
    ingr = []
    for i in range(0, len(l1)-2, 2):
        ingr.append(Chemical(int(l1[i]), l1[i+1]))
    reactions[key] = {'quantity': int(quantity), 'ingredients': ingr}

# print_reactions(reactions)

def ceiling(value1, value2):
    if value1 % value2 == 0:
        res = int(value1/value2)
    else:
        res = int(value1/value2) + 1
    return res

results = {}
leftovers= {}

def retrieve_leftovers(element, target_quantity):
    if element not in leftovers:
        leftovers[element] = 0
    else:
        if leftovers[element] >= target_quantity:
            leftovers[element] -= target_quantity
            return target_quantity
        else:
            leftover = leftovers[element]
            leftovers[element] = 0
            return leftover
    return 0

def add_leftovers(element, produced, target_quantity):
    if element not in leftovers:
        leftovers[element] = produced - target_quantity
    else:
        leftovers[element] += produced - target_quantity

def find_OREs(reactions, target_element, target_quantity, tabs):

    ingredients = reactions[target_element]['ingredients']
    reaction_quantity = reactions[target_element]['quantity']

    leftover = retrieve_leftovers(target_element, target_quantity)
    print(tabs, "We need", target_quantity, "of", target_element, "and we already have", leftover)
    target_quantity -= leftover

    if target_quantity == 0:
        print(tabs, "returning 0")
        return 0

    produced = ceiling(target_quantity, reaction_quantity) * reaction_quantity
    total = 0
    for i in ingredients:
        print(tabs, "Element", target_element, "needs", ceiling(produced, reaction_quantity)*i.quantity, i.element)
        if i.element == 'ORE':
            ore = ceiling(produced, reaction_quantity) * i.quantity
            print(target_quantity, target_quantity, produced)
            add_leftovers(target_element, produced, target_quantity)
            pprint(leftovers)
            print(tabs, ore, "ORE was used")
            return ore
        total += find_OREs(reactions, i.element, i.quantity*target_quantity, tabs + "  ")
    add_leftovers(target_element, produced, target_quantity)
    pprint(leftovers)
    return total

# def find_OREs(reactions, target_element, target_quantity, tabs):
#
#     t = " "*tabs
#     quantity = reactions[target_element]['quantity']
#     ingredients = reactions[target_element]['ingredients']
#
#     print(t, end=' ')
#     print(target_element, quantity)
#
#
#
#     if ingredients[0].element == 'ORE':
#         if target_element in results:
#             results[target_element]+=target_quantity
#         else:
#             results[target_element]=target_quantity
#         print(t, end= ' ')
#         print("element ", target_element, " is made of OREs. We need ", target_quantity)
#         print(t, end= ' ')
#         print("We already have ", see_leftovers(target_element))
#         return target_quantity
#
#     total = 0
#     for i in ingredients:
#         t = " "*tabs
#         print(t, end= ' ')
#         print("element ", target_element, " needed ", i.quantity, " ", i.element)
#         total += find_OREs(reactions, i.element, i.quantity * target_quantity, tabs+2)
#     return total

total = find_OREs(reactions, 'FUEL', 1, "")

print()
print(total)
