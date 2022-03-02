import matplotlib.pyplot as plt

n = [100, 1000, 10000, 100000, 1000000]

d_mt = [4.4E-4, 1.2E-4, 2.0E-6, 9.1E-9, 6.7E-9]
d_vdc = [5.1E-3, 7.3E-5, 1.2E-6, 8.5E-9, 4.8E-12]

plt.loglog(n, d_mt, label='Mersenne twister')
plt.loglog(n, d_vdc, label='Van der Corput')
plt.legend()
plt.xlabel(r'$N$')
plt.ylabel(r'$\Delta\,I$')
plt.savefig('p04.png')