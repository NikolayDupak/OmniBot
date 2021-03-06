import time
from lib import Servo, OmniBot, UartComm


def main():
    # example to use robot and servos
    comm = UartComm.UartComm("COM4", 19200)
    robot = OmniBot.OmniBot(comm)

    robot.add_servo(Servo.Servo("first", 11))
    time.sleep(1)
    # robot.add_servo(Servo.Servo("second", 12))
    # servo.min_pos = 10
    # servo.max_pos = 100
    time.sleep(3)
    robot.servo["first"].set_pos(170)
    # robot.servo["second"].set_pos(20)

    robot.move(100, 20, 30)


if __name__ == '__main__':
    main()
