import matplotlib.pyplot as plt
import numpy as np

N = 100000
(x, n) = np.loadtxt(f'distr1.dat', unpack=True)
cum_n = np.cumsum(n)
rng = np.random.default_rng(seed = 1)
means = np.zeros(N)

for i in range(N):
	new_n = np.zeros_like(x)
	for j in rng.integers(1, cum_n[-1], size=100, endpoint=True):
		idx = np.searchsorted(cum_n, j)
		new_n[idx] += 1
	means[i] = np.mean(x * new_n)

print(means)