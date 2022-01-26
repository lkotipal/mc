import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit

n, sigma = np.loadtxt('out.txt', unpack=True)
(a), _ = curve_fit(lambda x, a: a * x**(-1/2), n[1:], sigma[1:])

print((0.0001/a)**(-2))

x = np.logspace(1, 10)

plt.loglog(n, sigma, 'x', label=r'Observed $\sigma$')
plt.loglog(x, a * x**(-1/2), label=r'Fitted $\sigma$')
plt.loglog(x, 0.0001 * np.ones_like(x), '--', label=r'$\sigma = 0.0001')
plt.xlabel(r'$\bar{\sigma}$')
plt.ylabel(r'$N$')
plt.legend()
plt.show()
