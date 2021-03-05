
class UartComm:
    import serial

    def __init__(self, port, baudrate=9600):
        self.receive_package = list()
        self._serial = self.serial.Serial(port=port, baudrate=baudrate)

    def send_package(self, package: list):
        if self._serial.is_open:
            data = [255,255]
            data.append(package[0])
            data.append(package[1])
            data.append(package[2])
            data.append(package[3])

            s = package[0] ^ package[1] ^ package[2] ^ package[3]
            data.append(s)
            data.append(238)
            data.append(238)
            self._serial.write(bytes(data))

    def __send_byte(self, b:bytes):
        self._serial.write(b)

    def __read_byte(self, size):
        return self._serial.read(size)

    def read_package(self):
        if self._serial.in_waiting >= 9:
            data = list(self.__read_byte(9))
            if data[0] == 255 and data[1] == 255 and data[7] == 238 and data[8] == 238:
                return data[2:6]
        return []
