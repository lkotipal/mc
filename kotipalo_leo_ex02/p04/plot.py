import matplotlib.pyplot as plt
import numpy as np

def test(filename):
	x = np.loadtxt(f'{filename}.txt')
	n = np.size(x)
	C = np.zeros_like(x)
	for k in range(1, n - 1):
		C[k] = (np.mean(x[k:] * x[:-k]) - np.mean(x[:-k])**2) / (np.mean(x[:-k]**2) - np.mean(x[:-k])**2)
	plt.figure()
	plt.plot(C, 'x') if filename == 'lcg' else plt.plot(C)
	plt.title(f'{filename}')
	plt.xlabel('$k$')
	plt.ylabel('$C$')
	plt.ylim((-1, 1))
	plt.savefig(f'{filename}.png')
#plt.figure()
#plt.plot(x, y, 'x')
#plt.title(f'{i}')
#plt.xlabel('x')
#plt.ylabel('y')
#plt.xlim((0, 1))
#plt.ylim((0, 1))
#plt.show()

for i in ('lcg', 'pm', 'shuffler'):
	test(i)