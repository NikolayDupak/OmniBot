import time
from lib import UartComm
import pygame


def main():
    pygame.init()
    window = pygame.display.set_mode((300, 300))
    comm = UartComm.UartComm("COM4", 9600)
    comm.send_package([55, 128, 128, 128])
    clock = pygame.time.Clock()

    # rect = pygame.Rect(0, 0, 20, 20)
    # rect.center = window.get_rect().center
    # vel = 5

    run = True
    while run:
        # clock.tick(60)
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                run = False
            if event.type == pygame.KEYDOWN:
                print(pygame.key.name(event.key))

        keys = pygame.key.get_pressed()
        # up = keys[pygame.K_UP]
        # down = keys[pygame.K_DOWN]
        # left = keys[pygame.K_LEFT]
        # right = keys[pygame.K_RIGHT]

        up = keys[pygame.K_w]
        down = keys[pygame.K_s]
        left = keys[pygame.K_a]
        right = keys[pygame.K_d]

        r = keys[pygame.K_k]
        l = keys[pygame.K_l]
        vx = 100 * up + (-100) * down
        vw = (-100) * left + 100 * right

        vy = 100 * r + (-100) * l

        print(vx, vy)
        comm.send_package([55, vx + 128, vy + 128, vw + 128])
        time.sleep(0.1)

    pygame.quit()
    exit()


if __name__ == '__main__':
    main()
