import matplotlib.pyplot as plt
import numpy as np

(delta_max, R) = np.loadtxt('deltas.tsv', unpack=True)
print(f'Optimal delta_max: {delta_max[np.argmin(R)]}')

plt.plot(delta_max, R)
plt.xlabel(r'$\Delta\,E_{\mathrm{max}}$')
plt.ylabel(r'$R_{\mathrm{rms}}$')
plt.savefig(f'test_delta.png')