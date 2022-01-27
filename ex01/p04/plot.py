import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit

tests = ['lcg', 'pm', 'mt', 'lcg_small', 'pm_small', 'mt_small']
trials = [100, 10000]

for i in tests:
	for j in trials:
		x, y = np.loadtxt(f'{i}_{j}.txt', unpack=True)
		plt.plot(x, y, 'x')
		plt.title(f'{i}, {j} trials')
		plt.xlabel('x')
		plt.ylabel('y')
		plt.savefig(f'{i}_{j}.png')

#n, sigma = np.loadtxt('buffon.txt', unpack=True)
## Don't fit exponent, in MC error should be ~ 1/sqrt(N)
#(a), _ = curve_fit(lambda x, a: a * x**(-1/2), n[np.isfinite(sigma)], sigma[np.isfinite(sigma)])
#
#print((0.0001/a)**(-2))
#
#x = np.logspace(1, 10)
#
#plt.loglog(n, sigma, 'x', label=r'Observed $\sigma$')
#plt.loglog(x, a * x**(-1/2), label=r'Fitted $\sigma$')
#plt.loglog(x, 0.0001 * np.ones_like(x), '--', label=r'$\sigma = 0.0001$')
#plt.xlabel(r'$\bar{\sigma}$')
#plt.ylabel(r'$N$')
#plt.legend()
#plt.show()
