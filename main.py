"""
A 1D simulation of a quadrupeds leg
"""

import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

from leg import Leg
from shapes import Circle

# Constant joint radius
RADIUS = 0.01

fig, ax = plt.subplots(nrows=1, ncols=1, figsize=(10, 5))

ax.set_aspect('equal', adjustable='box')

class GraphLeg(Leg):
    """
    Graphs the leg
    """
    def __init__(self):
        self.delta_time = 0.001

        super().__init__((135, 225), (120, 240))

    def plot_joints(self, axes):
        """
        Plots the circles for the joints

        Args:
            axes (plt.subplots): the axis
        """

        hip_joint = Circle(RADIUS, self.hip_pos, 0.0001)
        knee_joint = Circle(RADIUS, self.knee_pos, 0.0001)
        foot = Circle(RADIUS, self.foot_pos, 0.0001)

        axes.plot(hip_joint.x_list, hip_joint.y_list, color="blue")
        axes.plot(knee_joint.x_list, knee_joint.y_list, color="blue")
        axes.plot(foot.x_list, foot.y_list, color="blue")

    def plot_leg(self, axes):
        """
        Plots the straight leg

        Args:
            axes (plt.subplots): the axis
        """
        x = [self.hip_pos[0], self.knee_pos[0], self.foot_pos[0]]
        y = [self.hip_pos[1], self.knee_pos[1], self.foot_pos[1]]

        axes.plot(x, y, color="black")

    def plot_forces(self, axes, forces):
        """
        Plots the forces acting on the leg

        Args:
        axes (plt.subplots): the axis
        forces (list): the resultant forces
        """
        x = [self.hip_pos[0], self.hip_pos[0] + forces[0]/50]
        y = [self.hip_pos[1], self.hip_pos[1] + forces[1]/50]

        axes.plot(x,y, color="green")

    def animate(self, _):
        """
        Displays the legs

        Args:
            _ (int): unused variable passed in from FuncAnimation
        """
        if _ == 1:
            self.__init__()
        ax.clear()
        ax.set_xlim([-0.05, 0.2])
        ax.set_ylim([0, 0.3])

        forces = self.update_position(self.delta_time)

        self.plot_joints(ax)
        self.plot_leg(ax)
        self.plot_forces(ax, forces)

        plt.text(-0.2, 0.15, f"time: {round(self.elapsed, 2)}s", fontsize=14)

my_leg = GraphLeg()
anim = FuncAnimation(fig, my_leg.animate, frames=1750, interval=0.01)

#anim.save('leg_under_free_fall.gif', writer='A. C. Armitage')
plt.show()
