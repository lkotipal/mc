import numpy as np
from scipy.stats import chi2

M = 100

def test (filename):
	a = np.loadtxt(filename)
	print(filename)

	print(f'Mean {np.mean(a)}')
	print(f'Median {np.median(a)}')
	print(f'{np.sum(a < chi2.ppf(0.1,  M-1)) / np.size(a)} values below lower confidence interval at 0.1')
	print(f'{np.sum(a < chi2.ppf(0.05, M-1)) / np.size(a)} values below lower confidence interval at 0.05')
	print(f'{np.sum(a > chi2.ppf(0.9,  M-1)) / np.size(a)} values above upper confidence interval at 0.1')
	print(f'{np.sum(a > chi2.ppf(0.95, M-1)) / np.size(a)} values above upper confidence interval at 0.05')
	print()

print(f'Expected mean for {M} bins is {chi2.mean(M - 1)}')
print(f'Expected median for {M} bins is {chi2.median(M - 1)}')
print()

for i in ('lcg.txt', 'pm.txt', 'mt.txt', 'qcg.txt'):
	test(i)