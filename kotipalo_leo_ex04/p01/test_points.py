import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit

(N, R) = np.loadtxt('points.tsv', unpack=True)

(a, b), pcov = curve_fit(lambda x, a, b: a * x**b, xdata=N, ydata=R)
(a_err, b_err) = np.sqrt(np.diag(pcov))
print(f'a = {a} +- {a_err}')
print(f'b = {b} +- {b_err}')

plt.loglog(N, R, '.', label=f'Data')
plt.plot(N, a * N**b, label=r'$a \cdot N^b$')
plt.xlabel(r'$N$')
plt.ylabel(r'$R_{\mathrm{rms}}$')
plt.legend()
plt.savefig(f'test_points.png')