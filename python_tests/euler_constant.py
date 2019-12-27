import argparse

parser = argparse.ArgumentParser(description='Computation of e')
parser.add_argument('--n', default=1, type=int, help='How often will you split?')
args = parser.parse_args()

n = args.n

e = (1 + 1/n)**n

print("e after ", str(n), " iterations:", e)

