import numpy as np
from math import sqrt
from scipy.stats import describe

medians = []
for a in np.array_split(np.loadtxt('p03.tsv'), 10):
	medians.append(np.median(a))

(_, _, mean, var, _, _) = describe(medians)

print(f"Average of medians: {mean} +- {sqrt(mean)}")