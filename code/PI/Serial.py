import serial

BAUDRATE_DEFAULT = 115200
PORT_DEFAULT = '/dev/serial0'

class UART:
    def __init__(self, baudrate: int = BAUDRATE_DEFAULT, port: str = PORT_DEFAULT):
        self.baudrate = baudrate
        self.port = port

        self.ser = serial.Serial(self.port, self.baudrate)

    def __del__(self):
        print("UART port destroyed.")
        self.ser.close()

    def write(self, msg: str) -> None:
        data = msg.encode('ascii')
        print("CMD:", data)
        self.ser.write(data)

    def _prepare_int(self, number: int) -> str:
        if number > 999 or number < -999:
            raise Exception("Number out of range")

        sign = '+' if number >= 0 else '-'
        result = f"{sign}{abs(number):03d}"

        if len(result) != 4:
            raise Exception("Converting number failed")

        return result

    def send_motor_config(self, left_speed: int, right_speed: int) -> None:
        left_speed = int(left_speed / 1.5)
        right_speed = int(right_speed / 1.5)
        cmd = f"L{self._prepare_int(left_speed)}R{self._prepare_int(right_speed)}"
        self.write(cmd)

    def read(self) -> str | None:
        if self.ser.in_waiting > 0:
            data = self.ser.read(self.ser.in_waiting)
            return data.decode('ascii') 

        return None
