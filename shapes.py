"""
A file to hold equations to show shapes
"""
import numpy as np

class Circle:
    """
    Uses X^2 + Y^2 = R^2
    """

    def __init__(self, radius, center, resolution=0.001):
        self.resolution = resolution
        self.radius = np.abs(radius)
        self.center = center

        self.x_list = list(np.arange(
            self.center[0] - radius,
            self.center[0] + radius,
            self.resolution))

        self.y_list = [self.get_positive_y_co_ordinate(i) for i in self.x_list]
        self.y_list.extend(reversed([self.get_negative_y_co_ordinate(i) for i in self.x_list]))
        self.x_list.extend(reversed(self.x_list))

    def __str__(self)->'str':
        return f"{self.x_list}\n{self.y_list}"

    def get_positive_y_co_ordinate(self, x_co_ordinate:'float')->'float':
        """
        Performs the calculation to graph the circle

        Args:
            x_co_ordinate (float): the x co ordinate

        Returns:
            float: the y co ordinate for the circle
        """
        return np.sqrt(self.radius ** 2 - (x_co_ordinate - self.center[0]) ** 2) + self.center[1]

    def get_negative_y_co_ordinate(self, x_co_ordinate:'float')->'float':
        """
        Performs the calculation to graph the circle

        Args:
            x_co_ordinate (float): the x co ordinate

        Returns:
            float: the y co ordinate for the circle
        """
        return -(np.sqrt(self.radius ** 2 - (x_co_ordinate - self.center[0]) ** 2)) + self.center[1]
