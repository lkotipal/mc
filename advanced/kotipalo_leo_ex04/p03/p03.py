import numpy as np
import matplotlib.pyplot as plt

v_300 = np.loadtxt('300.tsv')
v_2000 = np.loadtxt('2000.tsv')
v_10000 = np.loadtxt('10000.tsv')

E = np.linspace(1, 1000, 1000) * 0.01

plt.plot(E, v_300, label=r'$T = 300$ K')
plt.plot(E, v_2000, label=r'$T = 2\,000$ K')
plt.plot(E, v_10000, label=r'$T = 10\,000$ K')
plt.xlabel(r'$E$')
plt.ylabel(r'$v$')
plt.legend()
plt.savefig('p03.png')
