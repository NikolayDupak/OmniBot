import serial
import time
import UartComm
import pygame
import OmniBot
import Servo


def main():
    comm = UartComm.UartComm("COM1", 9600)
    robot = OmniBot.OmniBot(comm)

    servo = Servo.Servo("first", 12)
    servo2 = Servo.Servo("second", 12)
    # servo.min_pos = 10
    # servo.max_pos = 100

    robot.add_servo(servo)
    robot.add_servo(servo2)

    robot.servo["first"].set_pos(100)
    robot.servo["second"].set_pos(20)

    robot.move(10, 20, 30)


if __name__ == '__main__':
    main()
