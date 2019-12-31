def square(integer):
    return integer*integer

def even(integer):
    if (integer % 2) == 0:
        return True
    return False

numbers = [1, 2, 3, 4]

squared_numbers = list(map(square, numbers))
print(squared_numbers)

even_numbers = list(filter(even, numbers))
print(even_numbers)

x_coordinates = [1 ,2, 3, 4, 5]
y_coordinates = [1 ,2, 3, 4, 5]

xy_coordinates = list(zip(x_coordinates, y_coordinates))
print(xy_coordinates)
