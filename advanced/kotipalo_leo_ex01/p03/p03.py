import numpy as np
import matplotlib.pyplot as plt
from math import sqrt, log2
from scipy.stats import describe

data = np.loadtxt('p03.tsv')

medians = []
for a in np.array_split(data, 10):
	medians.append(np.median(a))

(_, _, mean, var, _, _) = describe(medians)
sigma = sqrt(var)

print(f"Average of medians: {mean} +- {sigma}")

nbins = int(round(log2(np.size(data)))) + 1
bins = np.geomspace(np.min(data), np.max(data), nbins)
plt.hist(data, bins, label='Simulation data')
plt.xscale('log')
plt.yscale('log')
plt.xlabel('Steps')
plt.ylabel('Occurrences')
plt.axvline(x=mean, color='#ff7f0e', ls='--', label='Median')
plt.legend()
plt.savefig('p03.png')