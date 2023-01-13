"""
Leg related processes and functions go here
Classes:
    Leg
"""

import numpy as np

# Simulation parameters
STARTING_HEIGHT = 0.3   # m
LENGTH = 0.075          # m
WIDTH = 0.005           # m
MASS = 0.05             # kg
TORQUE = 0.206          # Nm
G = 9.81                # gravity

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

    def get_torque_output(self, bearing:'degrees', delta_time:'seconds'):
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

        torque = error * self.p + self.integral * self.i + rate_of_change * self.d
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

        self.theta_one = theta[0]
        self.theta_two = theta[1]

        self.elapsed = 0

        # joint definitions
        self.hip_pos = [0.075, 0.17]
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
        self.elapsed += delta_time

        weight = MASS * G

        resultant_hip_global = [0, 0]
        resultant_hip_force = weight * np.cos((360 - self.theta_one)* np.pi/180)
        resultant_hip_global[0] = resultant_hip_force * np.sin((180-self.theta_one) * np.pi/180)
        resultant_hip_global[1] = resultant_hip_force * np.cos((180-self.theta_one) * np.pi/180)

        resultant_knee_global = [0, 0]
        resultant_knee_force = weight * np.sin((360 - self.theta_one)* np.pi/180)
        resultant_knee_global[0] = resultant_knee_force * np.sin((180-self.theta_two) * np.pi/180)
        resultant_knee_global[1] = resultant_knee_force * np.cos((180-self.theta_two) * np.pi/180)

        return [resultant_hip_global, resultant_knee_global]


    def update_position(self, delta_time:'seconds', forces:'Newtons'):
        """
        Calculates the position of the hip

        Args:
            delta_time (float): change in time

        Returns:
            list: the position of the hip
        """
        self.knee_pos = self.get_co_ordinate(self.hip_pos, LENGTH, self.theta_one)
        self.foot_pos = self.get_co_ordinate(self.knee_pos, LENGTH,self.theta_two)

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
