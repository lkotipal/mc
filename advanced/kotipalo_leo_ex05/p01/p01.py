import numpy as np
import matplotlib.pyplot as plt

l_cities = np.loadtxt('cities_lengths.tsv')
for i in ('square', 'circle', 'cities'):
    l = np.loadtxt(f'{i}_lengths.tsv')
    if (i == 'square'):
        print(f'With {np.size(i)} trials:')
    print(f'Shortest path in {i} {np.min(l)} with {np.sum(l == np.min(l))} hits')

    path = np.loadtxt(f'{i}_route.tsv', unpack=True)
    x = path[0]
    y = path[1]
    plt.figure()
    plt.plot(np.append(x, x[0]), np.append(y, y[0]))
    plt.savefig(f'{i}.png')

#E = np.linspace(1, 1000, 1000) * 0.01
#
#plt.plot(E, v_300, label=r'$T = 300$ K')
#plt.plot(E, v_2000, label=r'$T = 2\,000$ K')
#plt.plot(E, v_10000, label=r'$T = 10\,000$ K')
#plt.xlabel(r'$E$')
#plt.ylabel(r'$v$')
#plt.legend()
#plt.savefig('p03.png')
