from tqdm import tqdm
from random import seed, random

superblocks = []
levels = {}
difficulty = 1

def init(s):
    seed(s)

def update_levels(superblock):
    level = get_level(superblock)
    if level not in levels:
        levels[level] = 1
    else:
        levels[level] += 1

def get_level(number):
    zeros = 0
    while(number!=0 and number%2 == 0):
        zeros += 1
        number>>=1
    return zeros

def qualified_supedblock(candidate, difficulty):
    return candidate%pow(2, difficulty) == 0

def create_superblock(difficulty):
    block_lenght = pow(10, 5)
    candidate = int(random() * block_lenght)
    while(candidate==0 or not qualified_supedblock(candidate, difficulty)):
        candidate = int(random() * block_lenght)
    update_levels(candidate)
    return candidate

def create_superblocks(chain_size, difficulty):
    for i in tqdm(range(chain_size)):
        superblocks.append(create_superblock(difficulty))
    return superblocks

def print_superblocks(superblocks):
    superblocks_num = len(superblocks)
    percentage = 0
    superblocks_of_this_level = 0
    level_percentage = 0

    for d in sorted(levels.keys(), reverse=True):
        superblocks_of_this_level+=levels[d]

        level_percentage = levels[d]/superblocks_num * 100

        print('There were', '%6d'%levels[d], 'blocks with difficulty', '%2d'%d, end='')
        print(' -', '%6.3f'%level_percentage, '%', end='')
        print('- Holding ',  '%10d'%(levels[d]*pow(2,d)), 'PoW score')


for s in range(100):
    init(s)
    superblocks = create_superblocks(10000, 1)
    print_superblocks(superblocks)
    print()
