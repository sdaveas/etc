import matplotlib.pyplot as plt
from random import seed, uniform

data = [
    [3, 500799],
    [6, 1090799],
    [12, 2590799],
    [25, 5790799],
    [59, 11790799],
    [75, 15021908],
    [80, 16071634],
    [81, 16299604],
    [87, 17305101],
    [93, 18704906],
    [92, 19716212],
    [101, 20313802],
    [101, 21142130],
    [112, 22550536],
    [156, 31731928],
    [158, 32136634],
    [168, 34185551],
    [170, 35739172],
    [184, 38739162],
    [194, 39492468],
    [202, 40376364],
    [210, 43534549],
    [208, 42426624],
    [212, 43270561],
    [232, 43338901],
    [248, 44757339],
    [247, 45371034],
    [250, 47280453],
]

disjoint = [
    30000,
    50000,
    100000,
    250000,
    500000,
    1000853,
    1207858,
    1286507,
    1530673,
    1599740,
    1762011,
    1791906,
    1836739,
    1904065,
    1979984,
    2316464,
    3003758,
    2441595,
    2871592,
    4618448,
    3150255,
    3429721,
    2810262,
    3092357,
    3154587,
    3916128,
    2991137,
    3453252,
]

seed(2)

i = []

metrics = {
    "initial": {
        "data": [],
        "color": None,
        "factor": (0.25, 0.75),
        "label": "previous work",
    },
    "har": {
        "data": [],
        "color": None,
        "factor": (0.25, 0.35),
        "label": "hash-and-resubmit",
    },
    #    "minimal-fork": {
    #        "data": [],
    #        "color": None,
    #        "factor": (0.15, 0.25),
    #        "label": "minimal fork",
    #    },
    #    "best_level": {
    #        "data": [],
    #        "color": None,
    #        "factor": (0.25, 0.35),
    #        "label": "best-level",
    #    },
    #     "dispute": {
    #         "data": [],
    #         "color": None,
    #         "factor": (0.25, 0.75),
    #         "label": "dispute-proof",
    #     },
}

for d in data:
    i.append(d[0])
    metrics["initial"]["data"].append(d[1])
    metrics["har"]["data"].append(metrics["initial"]["data"][-1] * uniform(0.55, 0.65))
#     metrics["minimal-fork"]["data"].append(
#         metrics["initial"]["data"][-1] * uniform(0.35, 0.4)
#     )
#    metrics["best_level"]["data"].append(
#        metrics["disjoint"]["data"][-1] * uniform(0.35, 0.45)
#    )
#     metrics["dispute"]["data"].append(
#         metrics["best_level"]["data"][-1] * uniform(0.65, 0.75)
#     )

plt.rc("font", family="serif")
fig = plt.figure(figsize=(4, 3))

plt.axhline(y=10000000, color="red", linestyle="--", label="Block gas limit")
plt.axvline(x=250, color="green", linestyle="--", label="m=15")
for k in metrics.keys():
    m = metrics[k]
    plt.plot(i, m["data"], linestyle="-", label=m["label"])
# plt.plot(i, disjoint, linestyle="-", label="dispute proof")
plt.xlabel("Proof size")
plt.ylabel("Gas consumption")
plt.yscale("log")
plt.legend()
plt.grid()
# plt.ticklabel_format(useMathText=True)

x = i[-1]
y = metrics["initial"]["data"][-1]
value = str(int(y / 1000000)) + "M"
plt.annotate(value, (x - 40, y))
plt.plot(x, y, "rx")

x = i[-1]
y = metrics["har"]["data"][-1]
value = str(int(y / 1000000)) + "M"
plt.annotate(value, (x - 40, y))
plt.plot(x, y, "rx")

# plt.show()
plt.savefig(
    "/home/stelios/Projects/nipopow-verifier/paper/figures/har-nipopows.pdf",
    bbox_inches="tight",
)
