"""
A PID simulator for my quadruped
"""

import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib.widgets import Slider


class PID:
    """
    PID class as a controller
    """

    def __init__(self, kp, ki, kd, setpoint=0):
        self.kp = kp
        self.ki = ki
        self.kd = kd

        self.int_error = 0
        self.prev_error = 0

        self.setpoint = setpoint

        self.lims = False
        self.min_lim = 0
        self.max_lim = 0

    def set_lims(self, min_lim, max_lim):
        """
        Sets the limits of the controller
        """
        self.lims=True
        self.min_lim = min_lim
        self.max_lim = max_lim

    def update(self, error, dt):
        """
        Runs a PID loop
        """

        self.int_error += error * dt
        derivative = (error - self.prev_error) / dt

        output = self.kp * error + self.ki * self.int_error + self.kd * derivative

        self.prev_error = error

        if self.lims:
            if output > self.max_lim:
                return self.max_lim
            if output < self.min_lim:
                return self.min_lim
        return output

class DisplaySim:
    """
    Displays the simulation on a graph
    """

    def __init__(self):
        self.height = [0.13, 0.13]
        self.pid = PID(0.075, 0.005, 0.025)
        self.pid.set_lims(-0.02, 0.02)
        self.val = 0

        self.fig, self.ax = plt.subplots()

        self.fig.subplots_adjust(left=0.25, bottom=0.25)

        axfreq = self.fig.add_axes([0.25, 0.1, 0.65, 0.03])

        angle_slider = Slider(ax=axfreq,
                              valmin=-45,
                              valmax=45,
                              label="Degrees")

        angle_slider.on_changed(self.update)

        ani = animation.FuncAnimation(self.fig, self.animate, interval=50)

        plt.show()

    def animate(self, _):
        """
        Change whats on the screen
        """
        rot_mat = np.matrix([[np.cos(self.val), -np.sin(self.val)],
                             [np.sin(self.val), np.cos(self.val)]])

        ground_points = np.matrix([[-0.5, 0.5],
                                   [0, 0]])

        leg_points = np.matrix([[-0.15, 0.15, -0.15, 0.15],
                                [0, 0, self.height[0], self.height[1]]])

        new_ground_points = rot_mat * ground_points
        x = [new_ground_points.item(0), new_ground_points.item(1)]
        y = [new_ground_points.item(2), new_ground_points.item(3)]

        self.ax.clear()
        self.ax.plot(x, y)

        new_leg_points = rot_mat * leg_points

        error = np.arctan((new_leg_points.item(7)-new_leg_points.item(6)) / (new_leg_points.item(3)-new_leg_points.item(2))) * 180 / np.pi
        change = self.pid.update(error, DT)

        print(error)
        self.height = [0.13 + change, 0.13 - change]

        x = [[new_leg_points.item(0), new_leg_points.item(2)],
             [new_leg_points.item(1), new_leg_points.item(3)]]
        y = [[new_leg_points.item(4), new_leg_points.item(6)],
             [new_leg_points.item(5), new_leg_points.item(7)]]

        self.ax.plot(x[0], y[0])
        self.ax.plot(x[1], y[1])

        self.ax.set_xlim([-0.5, 0.5])
        self.ax.set_ylim([-0.5, 0.5])

    def update(self, val):
        """
        Update the value of the slider
        """
        self.val = val * np.pi / 180

if __name__ == "__main__":

    DT = 0.01

    sim = DisplaySim()
