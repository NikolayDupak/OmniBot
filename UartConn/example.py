import serial
import time
import UartComm
import pygame


def test():
    s = serial.Serial(port="COM4", baudrate=9600)
    while True:

        size = s.in_waiting
        # print(size)
        if size >= 1:
            data = s.read(size)
            l = list(data)
            print(l)

        m = [255, 255, 99, 34, 10, 50, 0, 238, 238]
        print(m)
        s.write(bytes(m))
        s.flush()

        time.sleep(1)


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

            # else:
            #    comm.send_package([55, 128, 128, 128])
            #    time.sleep(0.1)
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

        # rect.y += ( - ) * vel

    pygame.quit()
    exit()

    while True:

        data = comm.read_package()
        print(data)
        if len(data) > 0:
            print(data)

        comm.send_package([56, 0, 0, 0])
        time.sleep(1)


if __name__ == '__main__':
    # test()
    main()
    # comm = UartComm.UartComm("COM4", 9600)
    # vx = 100
    # vy = 0
    # vw = 0
    # comm.send_package([55, vx + 128, vy + 128, vw + 128])
    # time.sleep(3)
    # scomm.send_package([55, 128, 128, 128])
