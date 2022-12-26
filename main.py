"""
A 2D simulation involving forces of a Quadruped's leg
"""

import pygame
from leg import Leg

####################
# Size definitions #
####################
DIAMETER = 50
LENGTH = 200

###################
# GUI definitions #
###################
FPS = 60
WIDTH, HEIGHT = 900, 900
WIN = pygame.display.set_mode((WIDTH,HEIGHT))
pygame.display.set_caption("Dog leg simulation")

#####################
# Shape definitions #
#####################
ARROW = pygame.image.load("./Assets/arrow.png")
LINE = pygame.image.load("./Assets/line.png")
CIRCLE = pygame.image.load("./Assets/circle.png")

my_leg = Leg()

def show_gui():
    """
    Show the gui and perform each frame updates
    """
    clock = pygame.time.Clock()

    run = True

    while run:
        WIN.fill("white")

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                run = False

        pygame.display.update()
        clock.tick(FPS)

    pygame.quit()

if __name__ == "__main__":
    show_gui()
