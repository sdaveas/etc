import matplotlib.pyplot as plt
import numpy as np
from math import log2, ceil

LOAD_GAS = 68
MEM_GAS = 3
SHA2_GAS = 600
SHA3_GAS = 30
SHA2_MEM = MEM_GAS
SHA3_MEM = 6
B = 128000


def load(b, l):
    return b * l


def hash(b, h, hm):
    return b * hm + h


def prove(b, h, hm):
    return 2 ** (ceil(log2(b) + 1)) * hash(1, h, hm)


def verify(b, h, hm):
    return ceil(log2(b)) * hash(1, h, hm)


def har(b_init, b, h, hm, l=LOAD_GAS, M=MEM_GAS):
    return load(b_init, l) + hash(b, h, hm) + load(b, l) + hash(b, h, hm)


def mhar(b_init, b, h, hm, l=LOAD_GAS, M=MEM_GAS):
    return load(b_init, l) + prove(b, h, hm) + load(ceil(log2(b)), l) + verify(b, h, hm)


x = np.linspace(0.01, 2, 1000)
har_matr2 = []
har_matr3 = []
mhar_matr2 = []
mhar_matr3 = []
for i in range(len(x)):
    har_matr2.append(har(B, x[i] * B, h=SHA2_GAS, hm=SHA2_MEM))
    har_matr3.append(har(B, x[i] * B, h=SHA3_GAS, hm=SHA3_MEM))
    mhar_matr2.append(mhar(B, x[i] * B, h=SHA2_GAS, hm=SHA2_MEM))
    mhar_matr3.append(mhar(B, x[i] * B, h=SHA3_GAS, hm=SHA3_MEM))

plt.rc("font", family="serif")
fig = plt.figure(figsize=(4, 3))
plt.axhline(y=10000000, color="red", linestyle="--", label="Block gas limit")
# plt.plot(i, arr, color="green", linestyle=":", label="arr")
# plt.text(1, 1, "text on plot")
plt.plot(x, har_matr2, label="plain hash-and-resubmit (sha256)")
plt.plot(x, har_matr3, label="plain hash-and-resubmit (keccak)")
plt.plot(x, mhar_matr2, label="merkle hash-and-resubmit (sha256)")
plt.plot(x, mhar_matr3, label="merkle hash-and-resubmit (keccak)")
plt.xlabel("$d/d_0$")
plt.ylabel("Gas consumption")
plt.yscale("log")
plt.legend(bbox_to_anchor=(1, 1.5))
plt.grid()
plt.show()
# plt.savefig('./har-vs-mhar.png', bbox_inches='tight')
# plt.savefig(
#     "/home/stelios/Projects/nipopow-verifier/paper/figures/har-vs-mhar.pdf",
#     bbox_inches="tight",
# )
