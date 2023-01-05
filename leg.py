"""
Leg related processes and functions go here
Classes:
    Leg
"""

import numpy as np

# Simulation parameters
STARTING_HEIGHT = 0.3  # m
LENGTH = 0.075          # m
WIDTH = 0.005           # m
MASS = 0.15             # kg
TORQUE = 0.206          # Nm

class Servo:
    """
    Models the servo
    """

    def __init__(self, setpoint):
        self.p = 0.00009
        self.i = 0.00007
        self.d = 0.00004

        self.integral = 0
        self.setpoint = setpoint
        self.prev_error = 0

    def get_torque_output(self, bearing, delta_time:'seconds'):
        """
        Gets the torque output from the servo

        Args:
            bearing (_type_): _description_
            dt (_type_): _description_

        Returns:
            _type_: _description_
        """
        error = self.setpoint - bearing

        rate_of_change = (error - self.prev_error) / delta_time

        self.integral += error * delta_time

        torque = error * self.i + self.integral + rate_of_change
        self.prev_error = error

        if torque > TORQUE:
            torque = TORQUE
        elif torque < -TORQUE:
            torque = - TORQUE
        return torque


class Leg:
    """
    Holds a leg which can be graphed
    ALL ANGLES ARE TO BE DEFINED AS BEARINGS POINTING NORTH (TOP
    OF THE SCREEN)
    """

    def __init__(self, theta=(180, 180), limits=(120,240)):
        # servo initialisation
        self.servo_one = Servo(theta[0])
        self.servo_two = Servo(theta[1])

        # hard mechanical limits
        self.limits = limits

        self.theta_one = 0
        self.theta_two = 0

        self.elapsed = 0

        # joint definitions
        self.hip_pos = [0, STARTING_HEIGHT]
        self.knee_pos = self.get_co_ordinate(self.hip_pos, LENGTH, theta[0])
        self.foot_pos = self.get_co_ordinate(self.knee_pos, LENGTH, theta[1])

        # physics definitions
        self.velocity = [0, 0]

    def get_resultant_forces(self, delta_time:'seconds'=0.005, on_floor:'bool'=True)->'Newtons':
        """
        Calculates the X and Y component of the resultant forces

        Args:
            theta_one (Degrees): the bearing of the knee from the foot
            theta_two (Degrees): the bearing of the hip from the knee

        Returns:
            Newtons: The force vector output
        """
        torque_one = self.servo_one.get_torque_output(self.theta_one, delta_time)
        torque_two = self.servo_two.get_torque_output(self.theta_two, delta_time)

        weight = -9.81 * MASS

        if on_floor:
            force_one_x = np.sin((self.theta_one-90)*np.pi/180) * torque_one / LENGTH
            force_one_y = np.cos((self.theta_one-90) * np.pi/180) * torque_one / LENGTH

            force_two_x = -np.sin((self.theta_two-90)*np.pi/180) * torque_two / LENGTH
            force_two_y = -np.cos((self.theta_two-90) * np.pi/180) * torque_two / LENGTH

            force_x = force_one_x + force_two_x
            force_y = force_one_y + force_two_y + weight
        else:
            force_x = 0
            force_y = weight

        return [force_x, force_y]

    def update_position(self, delta_time:'seconds')->'Newtons':
        """
        Calculates the position of the hip

        Args:
            delta_time (float): change in time

        Returns:
            list: the position of the hip
        """
        forces = self.get_resultant_forces(on_floor=self.foot_pos[1]==0)

        self.theta_one = self.get_bearing(self.hip_pos, self.knee_pos)
        self.theta_two = self.get_bearing(self.knee_pos, self.foot_pos)

        acceleration = [forces[0] / MASS, forces[1] / MASS]

        self.elapsed += delta_time
        self.velocity[1] += acceleration[1] * delta_time
        self.hip_pos[1] += self.velocity[1] * delta_time

        # checks if the floor has been hit
        if self.hip_pos[1] < 0:
            self.hip_pos[1] = 0
        if self.hip_pos[1] == 0:
            self.velocity[1] = 0

        self.knee_pos = self.get_co_ordinate(self.hip_pos, LENGTH, self.servo_one.setpoint)
        self.foot_pos = self.get_co_ordinate(self.knee_pos, LENGTH, self.servo_two.setpoint)

        if self.foot_pos[1] < 0:
            self.foot_pos[1] = 0
            mean_height = (self.hip_pos[1] + self.foot_pos[1]) / 2
            delta_height = self.hip_pos[1] - self.foot_pos[1]
            length = np.sqrt(LENGTH ** 2 - (delta_height/2) ** 2)

            self.knee_pos = [length, mean_height]

        if self.get_bearing(self.hip_pos, self.knee_pos) < self.limits[0] or self.get_bearing(
            self.knee_pos, self.foot_pos) > self.limits[1]:

            self.knee_pos = self.get_co_ordinate(self.foot_pos, LENGTH, self.limits[1]-180)
            self.hip_pos = self.get_co_ordinate(self.knee_pos, LENGTH, self.limits[0]+180)

            print(self.foot_pos, self.knee_pos, self.hip_pos)

        return forces

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
