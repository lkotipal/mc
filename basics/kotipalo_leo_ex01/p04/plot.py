import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit

tests = ['lcg', 'pm', 'mt']
trials = [100, 10000]

for i in tests:
	for j in trials:
		x, y = np.loadtxt(f'{i}_{j}.txt', unpack=True)
		plt.figure()
		plt.plot(x, y, 'x')
		plt.title(f'{i}, {j} trials')
		plt.xlabel('x')
		plt.ylabel('y')
		plt.xlim((-1, 1))
		plt.ylim((-1, 1))
		plt.savefig(f'{i}_{j}.png')
	i += '_small'
	j = 1000
	x, y = np.loadtxt(f'{i}_{j}.txt', unpack=True)
	plt.figure()
	plt.plot(x, y, 'x')
	plt.title(f'{i}, {j} trials')
	plt.xlabel('x')
	plt.ylabel('y')
	plt.xlim((-0.01, 0.01))
	plt.ylim((-0.01, 0.01))
	plt.savefig(f'{i}_{j}.png')
