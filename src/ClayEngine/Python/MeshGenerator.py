import numpy as np
import matplotlib.pyplot as plt

N = 12
theta = np.linspace(0, 360, N)
x = np.sin(theta / 180 * np.pi)
y = np.cos(theta / 180 * np.pi)

fig = plt.figure(figsize=(10,10))
plt.plot(x,y,'ro')

f = open('../Assets/Meshes/Circle.pcd', '+w')
f.write('DATA ascii\n')

for i in range(N):
    f.write('{:.2f} {:.2f} {:.2f}\n'.format(y[i], 0, x[i]))

plt.show()



