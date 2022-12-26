"""
Leg related processes and functions go here
Classes:
    Leg
"""

import numpy as np
import pygame

####################
# Size definitions #
####################
DIAMETER = 50
LENGTH = 200
WIDTH = 10

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

    def __init__(self, offset=0, theta_one=180, theta_two=180):
        self.hip_pos = (offset, offset)
        self.knee_pos = self.get_co_ordinate(self.hip_pos, LENGTH, theta_one)
        self.foot_pos = self.get_co_ordinate(self.knee_pos, LENGTH, theta_two)

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
        return (x_co_ord, y_co_ord)


class LegImage(Leg):
    """
    Generates and transforms the images to draw the leg

    Inheritance:
        Leg : The leg object that needs to be displayed
    """

    def __init__(self):
        super().__init__()

        # Pivot definitions
        self.hip_joint = pygame.transform.scale(CIRCLE, (DIAMETER, DIAMETER))
        self.thigh_joint = pygame.transform.scale(CIRCLE, (DIAMETER, DIAMETER))
        self.foot = pygame.transform.scale(CIRCLE, (DIAMETER, DIAMETER))

        # Connection definitions
        self.thigh = pygame.transform.scale(LINE, (
            WIDTH, self.get_length(self.hip_pos, self.knee_pos)))
        self.shin = pygame.transform.scale(LINE, (
            WIDTH, self.get_length(self.knee_pos, self.foot_pos)))

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

    def display_leg(self, window):
        """
        blits the leg onto the window

        Args:
            window (pygame.display): the gui
        """
        height = window.get_height()

        # TODO
        window.blit(self.hip_joint, (
            DIAMETER + self.hip_pos[0],
            height - DIAMETER - self.hip_pos[1]))

        window.blit(self.thigh_joint, (
            DIAMETER + self.knee_pos[0],
            height - DIAMETER - self.knee_pos[1]))

        window.blit(self.foot, (
            DIAMETER + self.foot_pos[0],
            height - DIAMETER - self.foot_pos[1]))
