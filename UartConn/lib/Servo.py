class Servo:

    def __init__(self, name: str, pin: int, def_pos=90):
        self.name = name
        self._min_pos = 0
        self._max_pos = 180
        self._pin = pin
        self._default_position = def_pos
        self._position = self._default_position
        self._write = None

    def subscribe_for_send(self, write):
        self._write = write

    def _send_pos(self, position):
        if self._write is not None:
            self._write(self._pin, position)

    def set_pos(self, pos):
        self.position = pos
        self._send_pos(self._position)

    @property
    def position(self):
        return self._position

    @position.setter
    def position(self, new_pos):
        self._position = min(new_pos, self._max_pos)
        self._position = max(self._position, self._min_pos)

    @property
    def min_pos(self):
        return self._min_pos

    @min_pos.setter
    def min_pos(self, position):
        if 0 < position < 180 and position < self._max_pos:
            self._min_pos = position

    @property
    def max_pos(self):
        return self._max_pos

    @max_pos.setter
    def max_pos(self, position):
        if 0 < position < 180 and position > self._min_pos:
            self._max_pos = position
