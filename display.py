import math
import matplotlib.pyplot as plt

ORIGIN = [4, 15]
LENGTH = 7.5

def get_alpha_theta(x, y):

    alpha = math.acos(0.5 * math.sqrt(x**2 + y**2)/LENGTH)
    theta = math.atan(x/y)

    return alpha, theta

def plot_leg(alpha, theta):

    knee_x = ORIGIN[0] + math.sin(alpha+theta) * LENGTH
    knee_y = ORIGIN[1] - math.cos(alpha+theta) * LENGTH

    print(f"P1 -> ({knee_x},{knee_y})")

    foot_x = knee_x - math.sin(alpha - theta) * LENGTH
    foot_y = knee_y - math.cos(alpha - theta) * LENGTH

    print(f"P2 -> ({foot_x},{foot_y})")

    return ([ORIGIN[0], knee_x, foot_x],[ORIGIN[1], knee_y, foot_y])

if __name__ == "__main__":

    alpha, theta = get_alpha_theta(-3, 10)

    leg = plot_leg(alpha, theta)

    plt.xlim(0, 16)
    plt.ylim(0, 16)
    plt.plot(leg[0], leg[1])
    plt.show()