import math
import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit

(_, a, _, _) = np.loadtxt(f'statistics.dat', skiprows=1, unpack=True)
a = a[a > 0]
bins = np.geomspace(np.min(a), np.max(a), math.ceil(math.log2(np.size(a))) + 1, True)
(n, _, _) = plt.hist(a, bins, label=r'Data')
x = (bins[1:] + bins[:-1]) / 2
(a, b), pcov = curve_fit(lambda x, a, b: a * x**b, xdata=x[np.logical_and(x > 20, x < 3E3)], ydata=n[np.logical_and(x > 20, x < 3E3)])
(a_err, b_err) = np.sqrt(np.diag(pcov))
plt.plot(x, a * x**b, label=r'$a \cdot x^b$')
plt.xlabel(r'$s$')
plt.ylabel(r'$N$')
plt.xscale('log')
plt.yscale('log')
plt.legend()
plt.savefig('sand.png')
print(f'a = {a} +- {a_err}')
print(f'b = {b} +- {b_err}')
#plt.show()
