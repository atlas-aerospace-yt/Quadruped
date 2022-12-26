"""
A 2D simulation involving forces of a Quadruped's leg
"""

import pygame
from leg import LegImage

# GUI definitions
FPS = 60
WIDTH, HEIGHT = 900, 900
WIN = pygame.display.set_mode((WIDTH,HEIGHT))
pygame.display.set_caption("Dog leg simulation")

# Leg definitions
my_leg = LegImage()

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

        my_leg.display_leg(WIN)

        pygame.display.update()
        clock.tick(FPS)

    pygame.quit()

if __name__ == "__main__":
    show_gui()
