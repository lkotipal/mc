import matplotlib.pyplot as plt
import numpy as np

tests = ['inversion', 'sampling']

for i in tests:
	data = np.loadtxt(f'{i}.txt')
	plt.figure()
	plt.hist(data, bins=1000, range=(-10, 10), density=True, label='Generated data')

	x = np.linspace(-10, 10, 1000)
	y = 1/(x**2 + 4) / np.arctan(5)
	plt.plot(x, y, label='Theoretical distribution')
	plt.xlabel(r'$x$')
	plt.ylabel(r'$y$')
	plt.xlim((-10, 10))
	plt.legend()
	
	plt.savefig(f'{i}.png')