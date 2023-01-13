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

        super().__init__((150, 210), (120, 240))

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
        x_one_hip = [self.hip_pos[0], self.hip_pos[0] + forces[0][0]/10]
        y_one_hip = [self.hip_pos[1], self.hip_pos[1]]

        x_two_hip = [self.hip_pos[0], self.hip_pos[0]]
        y_two_hip = [self.hip_pos[1], self.hip_pos[1] + forces[0][1]/10]

        x_one_knee = [self.knee_pos[0], self.knee_pos[0] + forces[1][0]/10]
        y_one_knee = [self.knee_pos[1], self.knee_pos[1]]

        x_two_knee = [self.knee_pos[0], self.knee_pos[0]]
        y_two_knee = [self.knee_pos[1], self.knee_pos[1] + forces[1][1]/10]

        axes.plot(x_one_hip, y_one_hip, color="green")
        axes.plot(x_two_hip, y_two_hip, color="green")

        axes.plot(x_one_knee, y_one_knee, color="green")
        axes.plot(x_two_knee, y_two_knee, color="green")

    def animate(self, _):
        """
        Displays the legs

        Args:
            _ (int): unused variable passed in from FuncAnimation
        """
        if _ == 1:
            self.__init__()
        ax.clear()
        ax.set_xlim([0, 0.2])
        ax.set_ylim([0, 0.2])

        forces = self.get_resultant_forces(self.delta_time)
        self.update_position(self.delta_time, forces)

        self.plot_joints(ax)
        self.plot_leg(ax)
        self.plot_forces(ax, forces)

        plt.text(-0.1, 0.1, f"time: {round(self.elapsed, 2)}s", fontsize=14)

my_leg = GraphLeg()
anim = FuncAnimation(fig, my_leg.animate, frames=10, interval=0.01)

anim.save('force_analysis_stand.gif', writer='A. C. Armitage')
#plt.show()
