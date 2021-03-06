import time
from lib import UartComm, OmniBot, Servo
import pygame


def main():
    pygame.init()
    window = pygame.display.set_mode((300, 300))
    comm = UartComm.UartComm("COM4", 19200)
    robot = OmniBot.OmniBot(comm)
    robot.add_servo(Servo.Servo("first", 11))
    robot.servo["first"].max_pos = 180
    time.sleep(1)
    # robot.add_servo(Servo.Servo("second", 12))
    s1 = 90
    robot.servo["first"].set_pos(s1)

    up = 0
    down = 0
    left = 0
    right = 0
    r = 0
    l = 0
    s1_up = 0
    s1_down = 0
    run = True
    while run:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                run = False
            if event.type == pygame.KEYDOWN:
                b_name = pygame.key.name(event.key)
                print(b_name)
                print("down")
                if b_name == 'w': up = 1
                if b_name == 's': down = 1
                if b_name == 'a': left = 1
                if b_name == 'd': right = 1

                if b_name == 'k': r = 1
                if b_name == 'l': l = 1

                if b_name == 'o': s1_up = 1
                if b_name == 'p': s1_down = 1

            if event.type == pygame.KEYUP:
                b_name = pygame.key.name(event.key)
                print("up")
                if b_name == 'w': up = 0
                if b_name == 's': down = 0
                if b_name == 'a': left = 0
                if b_name == 'd': right = 0

                if b_name == 'k': r = 0
                if b_name == 'l': l = 0

                if b_name == 'o': s1_up = 0
                if b_name == 'p': s1_down = 0
                break

        """keys = pygame.key.get_pressed()
        s1_up = keys[pygame.K_UP]
        s1_down = keys[pygame.K_DOWN]
        # left = keys[pygame.K_LEFT]
        # right = keys[pygame.K_RIGHT]

        up = keys[pygame.K_w]
        down = keys[pygame.K_s]
        left = keys[pygame.K_a]
        right = keys[pygame.K_d]

        r = keys[pygame.K_k]
        l = keys[pygame.K_l]"""

        vx = 100 * up + (-100) * down
        vw = (-100) * left + 100 * right

        vy = 100 * r + (-100) * l

        s1 += 10 * s1_up + (-10) * s1_down
        if s1 > 200:
            s1 = 200
        if s1 < 0:
            s1 = 0

        print(vx, vy, vw)
        robot.servo["first"].set_pos(s1)
        robot.move(vx, vy, vw)
        time.sleep(0.05)

    pygame.quit()


if __name__ == '__main__':
    main()
