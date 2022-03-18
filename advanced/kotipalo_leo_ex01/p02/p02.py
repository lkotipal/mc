import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

(n, r_squared, sigma) = np.loadtxt('p02.tsv', unpack=True)

(a, cov) = curve_fit(lambda x, a, b : a * x**b, xdata = n[1:], ydata = r_squared[1:], p0 = (1, 1), sigma = sigma[1:])
perr = np.sqrt(np.diag(cov))

print(f'a = {a[0]} +- {perr[0]}')
print(f'b = {a[1]} +- {perr[1]}')

plt.errorbar(n, r_squared, sigma, capsize=2.0, fmt=' ', label='Simulation data')
plt.plot(n, a[0] * n**a[1], label=r'$a x^b$')
plt.xscale('log')
plt.yscale('log')
plt.xlabel(r'$N$')
plt.ylabel(r'$<r^2>$')
plt.legend()
plt.savefig('p02.png')