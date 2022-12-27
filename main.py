"""
A 1D simulation of a quadrupeds leg
"""

import matplotlib.pyplot as plt

from shapes import Circle

fig = plt.figure()
ax = fig.add_subplot()
ax.set_aspect('equal', adjustable='box')

my_circle = Circle(1, (0,0), 0.00001)

plt.xlim([-1, 1])
plt.ylim([-1, 1])

plt.plot(my_circle.x_list, my_circle.y_list)
plt.show()
