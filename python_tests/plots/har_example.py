import matplotlib.pyplot as plt

storage = [
    [100, 2236363, 298085],
    [200, 4431624, 572546],
    [300, 6626936, 847058],
    [400, 8822275, 1121597],
    [500, 11017654, 1396176],
    [600, 13213071, 1670793],
    [700, 15408527, 1945449],
    [800, 17604022, 2220144],
    [900, 19799557, 2494879],
    [1000, 21982804, 2773930],
]

memory = [
    [100, 74642, 87874],
    [200, 106477, 151724],
    [300, 138676, 216223],
    [400, 171215, 281323],
    [500, 204105, 347048],
    [600, 237347, 413398],
    [700, 270940, 480373],
    [800, 304885, 547973],
    [900, 339182, 616198],
    [1000, 379002, 672922],
]

i = []
storage_submit = []
storage_contest = []
memory_submit = []
memory_contest = []

for s in storage:
    i.append(s[0])
    storage_submit.append(s[1])
    storage_contest.append(s[2])

for s in memory:
    memory_submit.append(s[1])
    memory_contest.append(s[2])

plt.rc("font", family="serif")
fig = plt.figure(figsize=(4, 3))
plt.axhline(y=10000000, color="red", linestyle="--", label="Block gas limit")
plt.plot(i, storage_submit, color="blue", linestyle="-", label="Submit")
plt.plot(i, storage_contest, color="blue", linestyle=":", label="Contest")
plt.plot(
    i,
    memory_submit,
    color="green",
    linestyle="-",
    label="Submit using hash-and-resubmit",
)
plt.plot(
    i,
    memory_contest,
    color="green",
    linestyle=":",
    label="Contest using hash-and-resubmit",
)
plt.xlabel("Array size")
plt.ylabel("Gas consumption")
plt.yscale("log")
plt.legend(bbox_to_anchor=(0.935, 1.55))
plt.grid()
# plt.show()

x = i[-1]
y = storage_submit[-1]
value = str(y // 1000000) + " mil"
plt.annotate(value, (x - 160, y - 500000))
plt.plot(x, y, "rx")

x = i[-1]
y = storage_contest[-1]
value = str(y // 1000000 + 1) + " mil"
plt.annotate(value, (x - 133, y + 100000))
plt.plot(x, y, "rx")

x = i[-1]
y = memory_contest[-1]
value = str(y // 1000) + "K"
plt.annotate("0.67 mil", (x - 200, y + 20000))
plt.plot(x, y, "rx")

x = i[-1]
y = memory_submit[-1]
value = str(y // 1000) + "K"
plt.annotate("0.38 mil", (x - 200, y + 20000))
plt.plot(x, y, "rx")

plt.savefig(
    "/home/stelios/Projects/nipopow-verifier/paper/figures/har-example.pdf",
    bbox_inches="tight",
)
