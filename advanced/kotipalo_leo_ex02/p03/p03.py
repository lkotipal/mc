import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

(n, p_1, sigma_1, p_2, sigma_2) = np.loadtxt('p03.tsv', skiprows=1, unpack=True)

(a1, cov1) = curve_fit(lambda x, a, b : a * x**b, xdata = n, ydata = sigma_1)
perr1 = np.sqrt(np.diag(cov1))
(a2, cov2) = curve_fit(lambda x, a, b : a * x**b, xdata = n, ydata = sigma_2)
perr2 = np.sqrt(np.diag(cov1))

print(f'a1 = {a1[0]} +- {perr1[0]}')
print(f'b1 = {a1[1]} +- {perr1[1]}')

print(f'a2 = {a2[0]} +- {perr2[0]}')
print(f'b2 = {a2[1]} +- {perr2[1]}')

plt.loglog(n, sigma_1, 'x', label='Standard error')
plt.loglog(n, sigma_2, 'x', label='Standard error, optimized')
plt.loglog(n, a1[0] * n**a1[1], color='#1f77b4')
plt.loglog(n, a2[0] * n**a2[1], color='#ff7f0e')
plt.xlabel(r'$N$')
plt.ylabel(r'$\sigma$')
plt.legend()
plt.savefig('p03.png')
