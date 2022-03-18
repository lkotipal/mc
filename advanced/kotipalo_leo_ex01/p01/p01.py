import numpy as np
import matplotlib.pyplot as plt

(n, r_squared, sigma) = np.loadtxt('p01.tsv', unpack=True)
plt.errorbar(n, r_squared, sigma, capsize=0.0, fmt=' ')
plt.xscale('log')
plt.yscale('log')
plt.show()