import argparse

def binary_search(sub_list, target):
    size = len(sub_list)
    if size == 1:
        return sub_list[0] == target

    middle = int(size/2)
    if target < sub_list[middle]:
        return binary_search(sub_list[:middle], target)
    else:
        return binary_search(sub_list[middle:], target)

def scan_input(input_file, delimiter):
    with open(input_file) as input:
        i = input.read().strip().split(delimiter)

    l = list(map(int, i))

    return l

def main():

    parser = argparse.ArgumentParser('Define a target to be found using binary search')
    parser.add_argument('--target', required=True, type=int, help='Element to be found')
    parser.add_argument('--input', required=True, type=str, help='Input file')
    parser.add_argument('--delimiter', required=True, type=str, help='File delimiter')
    args = parser.parse_args()
    target = args.target
    input_file = args.input
    delimiter = args.delimiter

    l = scan_input(input_file, delimiter)

    print(binary_search(l, target))

if __name__ == "__main__":
    main()
