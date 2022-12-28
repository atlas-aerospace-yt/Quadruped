"""
Leg related processes and functions go here
Classes:
    Leg
"""

import numpy as np

# Simulation parameters
STARTING_HEIGHT = 0.25  # m
LENGTH = 0.075          # m
WIDTH = 0.005           # m
MASS = 0.1              # kg
TORQUE = 0.206          # Nm

class Leg():
    """
    Legs objects
    ALL ANGLES ARE TO BE DEFINED AS BEARINGS POINTING NORTH
    """

    def __init__(self, theta_one=180, theta_two=180):

        self.theta_one = 180
        self.theta_two = 180

        self.elapsed = 0

        # joint definitions
        self.hip_pos = [0, STARTING_HEIGHT]
        self.knee_pos = self.get_co_ordinate(self.hip_pos, LENGTH, theta_one)
        self.foot_pos = self.get_co_ordinate(self.knee_pos, LENGTH, theta_two)

        # physics definitions
        self.velocity = [0, 0]
        self.acceleration = [0, -9.81]

    def get_resultant_forces(self)->'Newtons':
        """
        Calculates the X and Y component of the resultant forces

        Args:
            theta_one (Degrees): the bearing of the knee from the foot
            theta_two (Degrees): the bearing of the hip from the knee

        Returns:
            Newtons: The force vector output
        """
        weight = 9.81 * MASS
        force_one_x = np.abs(np.sin((self.theta_one-90)*np.pi/180) * TORQUE / LENGTH)
        force_one_y = np.abs(np.cos((self.theta_one-90) * np.pi/180) * TORQUE / LENGTH)

        force_two_x = np.abs(np.sin((self.theta_two-90)*np.pi/180) * TORQUE / LENGTH)
        force_two_y = np.abs(np.cos((self.theta_two-90) * np.pi/180) * TORQUE / LENGTH)

        force_x = force_one_x + force_two_x
        force_y = force_one_y + force_two_y - weight

        return [force_x, force_y]

    def update_position(self, delta_time:'seconds')->'meters':
        """
        Calculates the position of the hip

        Args:
            delta_time (float): change in time

        Returns:
            list: the position of the hip
        """
        forces = self.get_resultant_forces()

        self.acceleration = [forces[0] / MASS, forces[1] / MASS]
        print(self.acceleration)
        self.elapsed += delta_time
        self.velocity[1] += self.acceleration[1] * delta_time
        self.hip_pos[1] += self.velocity[1] * delta_time

        # checks if the floor has been hipt
        if self.hip_pos[1] < 0:
            self.hip_pos[1] = 0
        if self.hip_pos[1] == 0:
            self.velocity[1] = 0

        self.knee_pos = self.get_co_ordinate(self.hip_pos, LENGTH, self.theta_one)
        self.foot_pos = self.get_co_ordinate(self.knee_pos, LENGTH, self.theta_two)

        if self.foot_pos[1] < 0:
            self.foot_pos[1] = 0
            mean_height = (self.hip_pos[1] + self.foot_pos[1]) / 2
            delta_height = self.hip_pos[1] - self.foot_pos[1]
            length = np.sqrt(LENGTH ** 2 - (delta_height/2) ** 2)

            self.knee_pos = [length, mean_height]

        self.theta_one = self.get_bearing(self.hip_pos, self.knee_pos)
        self.theta_two = self.get_bearing(self.knee_pos, self.foot_pos)

    def set_leg_angles(self, theta_one, theta_two):
        """
        Sets the angle leg and re calculates the coordinates

        Args:
            theta_one (int): the bearing of the knee from the hip
            theta_two (int): the bearing of the foot from the knee
        """
        self.knee_pos = self.get_co_ordinate(self.hip_pos, LENGTH, theta_one)
        self.foot_pos = self.get_co_ordinate(self.knee_pos, LENGTH, theta_two)

    def set_hip_pos(self, hip_pos):
        """
        Sets the hip position using x and y coordinates

        Args:
            hip_pos (list): the coordinates of the hip
        """
        self.hip_pos = [hip_pos[0], hip_pos[1]]

    def get_co_ordinate(self, origin, distance, bearing):
        """
        Calculates the position coordinates from the origin, distance and bearing

        Args:
            origin (tuple): the origin coordinates
            distance (int): the distance between the two points
            bearing (int): the bearing from oriding to the point

        Returns:
            tuple: the position vector
        """
        x_co_ord = origin[0] + np.sin(bearing * np.pi/180) * distance
        y_co_ord = origin[1] + np.cos(bearing * np.pi/180) * distance
        return [x_co_ord, y_co_ord]

    def get_bearing(self, co_ord_one, co_ord_two):
        """
        Calculates the bearing from co_ord_one to co_ord_two

        Args:
            co_ord_one (list): starting point
            cor_ord_two (list): end point

        Returns:
            int: the bearing
        """
        x = co_ord_two[0] - co_ord_one[0]
        y = co_ord_two[1] - co_ord_one[1]

        bearing = np.arctan2([x], [y]) * 180 / np.pi
        return bearing[0]

    def get_length(self, co_ord_one, co_ord_two):
        """
        calculates the distance between two points

        Args:
            co_ord_one (tuple): the first coordinate
            cor_ord_two (tuple): the second coordinate

        Returns:
            int: the distance between the two points
        """
        x_distance = co_ord_one[0] - co_ord_two[0]
        y_distance = co_ord_one[1] - co_ord_two[1]

        return np.sqrt(x_distance ** 2 + y_distance ** 2)
