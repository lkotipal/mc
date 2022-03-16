import math
import matplotlib.pyplot as plt
import numpy as np
from scipy.stats import describe

for i in ('discrete', 'poisson'):
	a = np.loadtxt(f'{i}.tsv')

	(_, _, mean, var, _, _) = describe(a)
	(low, high) = np.percentile(a, (16, 84))

	print(f'{i}')
	print(f'Mean {mean}')
	print(f'Lower error {mean - low}, upper error {high - mean}')
	print(f'Standard deviation {math.sqrt(var)}')
	
	plt.figure()
	plt.hist(a, bins=math.ceil(math.log2(np.size(a))) + 1)
	plt.xlabel(r'$\mu$')
	plt.ylabel(r'$N$')
	plt.savefig(f'{i}.png')