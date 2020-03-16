


"""
Pow tests
"""
from sys import getsizeof
from tqdm import tqdm

def slow_pow(base, exponent, mod=1):
    """ Calculates base raised to the power exponent """

    result = 1

    for i in tqdm(range(exponent), desc='Calculating power slowly'):
        result *= base%mod

    return result%mod

def fast_pow(base, exponent, mod=1):
    """ Calculates power using square addition """

    result = 1
    binary_digits = str(exponent) * getsizeof(exponent)

    # for i in tqdm(range(len(binary_digits)), 'Calculating power fast'):
    #     if exponent == 0:
    #         continue
    while exponent != 0:
        if (exponent & 1) == 1:
            result *= (base)
        base *= base
        exponent >>= 1

    return result%mod


print(fast_pow(11235813, 11235813, 10000))
print(slow_pow(11235813, 112358, 10000))
print()
