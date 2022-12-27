"""
Leg related processes and functions go here
Classes:
    Leg
"""

import numpy as np
import pygame

##############
# Conversion #
##############
METERS_TO_PIXELS = 3_000

####################
# Size definitions #
####################
LENGTH = 0.075
WIDTH = 0.005
MASS = 1
TORQUE = 0.137


#####################
# Shape definitions #
#####################
ARROW = pygame.image.load("./Assets/arrow.png")
LINE = pygame.image.load("./Assets/line.png")
CIRCLE = pygame.image.load("./Assets/circle.png")


class Leg():
    """
    Legs objects
    ALL ANGLES ARE TO BE DEFINED AS BEARINGS POINTING NORTH
    """

    def __init__(self, theta_one=180, theta_two=180):

        # joint definitions
        self.hip_pos = (0, 0)
        self.knee_pos = self.get_co_ordinate(self.hip_pos, LENGTH, theta_one)
        self.foot_pos = self.get_co_ordinate(self.knee_pos, LENGTH, theta_two)

        # physics definitions
        self.position = [0, 0]
        self.velocity = [0, 0]
        self.acceleration = [0, 9.81]

    def get_resultant_forces(self, theta_one:'Degrees', theta_two:'Degrees')->'Newtons':
        """
        Calculates the X and Y component of the resultant forces

        Args:
            theta_one (Degrees): the bearing of the knee from the foot
            theta_two (Degrees): the bearing of the hip from the knee

        Returns:
            Newtons: The force vector output
        """
        weight = 9.81 * MASS
        force_one_x = np.sin((theta_one-90)*np.pi/180) * TORQUE / LENGTH
        force_one_y = np.cos((theta_one-90) * np.pi/180) * TORQUE / LENGTH

        force_y = force_one_y - weight

        return (force_one_x, force_y)

    def get_position(self, delta_time):
        """
        Calculates the position of the hip

        Args:
            delta_time (float): change in time

        Returns:
            list: the position of the hip
        """
        self.velocity[1] += self.acceleration[1] * delta_time
        self.position[1] += self.velocity[1] * delta_time

        # checks if the floor has been hipt
        if self.position[1] > 0.2:
            self.position[1] = 0.2
        if self.position[1] == 0.2:
            self.velocity[1] = 0

        return self.position

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
        self.hip_pos = (hip_pos[0], hip_pos[1])

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
        return (int(x_co_ord), int(y_co_ord))

    def get_length(self, co_ord_one, cor_ord_two):
        """
        calculates the distance between two points

        Args:
            co_ord_one (tuple): the first coordinate
            cor_ord_two (tuple): the second coordinate

        Returns:
            int: the distance between the two points
        """
        x_distance = co_ord_one[0] - cor_ord_two[0]
        y_distance = co_ord_one[1] - cor_ord_two[1]

        return int(np.sqrt(x_distance ** 2 + y_distance ** 2))
