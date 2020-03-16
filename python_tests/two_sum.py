
import argparse

def two_sum(nums, target):
    ret = []
    values_to_indices = {}
    for index in range(len(nums)):
        element = nums[index]
        if target-element in values_to_indices:
            ret.append([values_to_indices[target-element], index])
        values_to_indices[element] = index
    return ret

def read_file(filepath, delimiter):
    with open(filepath) as input_file:
        l = input_file.read().strip().split(delimiter)
    return list(map(int, l))

def main():
    parser = argparse.ArgumentParser('Solution to the two-sum problem')
    parser.add_argument('--target',    type=int, required=True, help='The target sum')
    parser.add_argument('--file',      type=str, required=True, help='Input file')
    parser.add_argument('--delimiter', type=str, default=' ',   help='Delimiter of input file (default is space)')
    args = parser.parse_args()

    target = args.target
    filepath = args.file
    delimiter = args.delimiter

    nums = read_file(filepath, delimiter)

    res = two_sum(nums, target)
    print(len(res))

if __name__ == "__main__":
    main()
