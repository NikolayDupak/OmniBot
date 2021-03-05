from lib import UartComm, Servo


class OmniBot:

    def __init__(self, connection: UartComm.UartComm):
        self.servo = {}
        self.connection = connection

    def move(self, vx, vy, w):
        """

        :param vx: x speed from -100 to 100
        1 - 100 Forward; -1 - -100 backward; 0 - stop
        :param vy: y speed from -100 to 100
        1 - 100 right; -1 - -100 left; 0 - stop
        :param w: w speed from -100 to 100
        1 - 100 clockwise -1 - -100 counter-clockwise; 0 - stop
        :return:
        """

        def min_max(val):
            val = min(val, 100)
            val = max(val, -100)
            return val

        vx = min_max(vx) + 128
        vy = min_max(vy) + 128
        w = min_max(w) + 128

        self._motor_send(vx, vy, w)

    def stop(self):
        self.move(0, 0, 0)

    def add_servo(self, servo: Servo):
        servo.subscribe_for_send(self._servo_send)
        self.servo.update({servo.name: servo})

    def _servo_send(self, pin: bytes, value: bytes):
        self.connection.send_package([40, pin, value, 0])

        pass

    def _motor_send(self, vx: bytes, vy: bytes, w: bytes):
        self.connection.send_package([55, vx, vy, w])
        pass
