"""
======================
3D surface (color map)
======================

Demonstrates plotting a 3D surface colored with the coolwarm color map.
The surface is made opaque by using antialiased=False.

Also demonstrates using the LinearLocator and custom formatting for the
z axis tick labels.
"""

from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
from matplotlib import cm
from matplotlib.ticker import LinearLocator, FormatStrFormatter
import numpy as np

ether_in_usd = 210.39


def cost_in_fiat(gas):
    return gas * ether_in_usd


gas_prices = [0, 9, 15, 18, 19, 20, 23, 26]
perc_in_last_200 = [0, 5.4900, 28.57, 31.860, 42.85, 80.220, 98.900, 100.00]
prob_in_last_200 = [x / 100 for x in perc_in_last_200]
submit_cost = [0, 0.0198, 0.033, 0.034, 0.042, 0.0440, 0.0506, 0.057]
contest_cost_100 = [0, 0.0131, 0.022, 0.026, 0.027, 0.0293, 0.0337, 0.038]
contest_cost_100K = [0, 0.0360, 0.060, 0.072, 0.076, 0.0800, 0.0920, 0.104]
contest_cost_650K = [0, 0.0531, 0.088, 0.106, 0.112, 0.1181, 0.1358, 0.153]
contest_cost = contest_cost_100
z = 0.01
collateral = [x + z for x in contest_cost]
overall_submit_cost_6 = [x + submit_cost[1] for x in collateral]
overall_submit_cost_42 = [x + submit_cost[4] for x in collateral]
overall_submit_cost_80 = [x + submit_cost[5] for x in collateral]
overall_submit_cost_99 = [x + submit_cost[6] for x in collateral]
overall_submit_cost_100 = [x + submit_cost[7] for x in collateral]

plt.rc("font", family="serif")
fig = plt.figure(figsize=(4, 3))

ax1 = plt.gca()
ax2 = ax1.secondary_yaxis("right", functions=(cost_in_fiat, cost_in_fiat))
ax2.set_ylabel("USD")

plt.plot(
    prob_in_last_200, submit_cost, label="transaction cost of submit", color="green"
)
plt.plot(
    prob_in_last_200, contest_cost, label="transaction cost of contest", color="blue"
)
plt.plot(prob_in_last_200, collateral, label="collateral (z=0.01 Gwei)", color="red")
plt.plot(
    prob_in_last_200,
    overall_submit_cost_6,
    label="submit cost: P(incl. in next 200) = 6%",
    linestyle=":",
)
plt.plot(
    prob_in_last_200,
    overall_submit_cost_42,
    label="submit cost: P(incl. in next 200) = 42%",
    linestyle=":",
)
plt.plot(
    prob_in_last_200,
    overall_submit_cost_80,
    label="submit cost: P(incl. in next 200) = 80%",
    linestyle=":",
)
plt.plot(
    prob_in_last_200,
    overall_submit_cost_99,
    label="submit cost: P(incl. in next 200) = 99%",
    linestyle=":",
)
plt.plot(
    prob_in_last_200,
    overall_submit_cost_100,
    label="submit cost: P(incl. in next 200) = 100%",
    linestyle=":",
)

plt.xlabel("Probability of next 200 blocks accepting this gas price")
plt.ylabel("Gas in Gwei")

plt.legend(bbox_to_anchor=(1, 1.8))
plt.grid()
# plt.legend()
# plt.show()
plt.savefig(
    "/home/stelios/Projects/nipopow-verifier/paper/figures/cryptoeconomics-100.pdf",
    bbox_inches="tight",
)
