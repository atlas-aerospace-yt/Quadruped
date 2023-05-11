import math
import matplotlib.pyplot as plt

ORIGIN = [4, 15]
LENGTH = 7.5

def plot_leg(alpha, theta):
    alpha *= math.pi/180
    theta *= math.pi/180

    knee_x = ORIGIN[0] + math.sin(alpha+theta) * LENGTH
    knee_y = ORIGIN[1] - math.cos(alpha+theta) * LENGTH

    print(f"P1 -> ({knee_x},{knee_y})")

    foot_x = knee_x - math.sin(alpha - theta) * LENGTH
    foot_y = knee_y - math.cos(alpha - theta) * LENGTH
    print((math.pi/2 - alpha + theta) * 180 / math.pi)
    print(f"P2 -> ({foot_x},{foot_y})")

    return ([ORIGIN[0], knee_x, foot_x],[ORIGIN[1], knee_y, foot_y])

if __name__ == "__main__":
    leg = plot_leg(45,0)
    plt.xlim(0, 16)
    plt.ylim(0, 16)
    plt.plot(leg[0], leg[1])
    plt.show()