import numpy as np
from scipy.stats import describe

for i in ('DS', 'SS', 'HM', 'PSS', 'IS'):
	print(i)
	data = np.loadtxt(f'{i}.txt')
	(_, _, mean, variance, _, _) = describe(data)
	print(f'{mean} +- {np.sqrt(variance)}')
	print()