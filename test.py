from time import time
import numpy as np
m = 2048
k = 1024 
n = 2048 
a = np.random.random((m, k))
b = np.random.random((k, n))
c = np.zeros((m, n))
start = time()
c = np.dot(a, b)
end = time()
print(f"Time: {(end - start) * 1000} ms")
