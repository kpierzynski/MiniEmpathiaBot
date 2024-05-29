import socket

SOCKET_PATH = "/tmp/neopixel_socket"


class Leds:
    RED = 0
    GREEN = 1
    BLUE = 2
    BLACK = 4

    def __init__(self):
        self.set_leds(self.BLACK)

    def send_led_data(self, led_data):
        with socket.socket(socket.AF_UNIX, socket.SOCK_STREAM) as s:
            s.connect(SOCKET_PATH)
            s.sendall(led_data)

    def set_leds(self, color):
        led_data = bytearray(8 * 3)
        for x in range(0,24):
            led_data[x] = 0

        for x in range(0,24):
            if color == Leds.BLACK:
                break
            if x % 3 == color:
                led_data[x] = 4

        self.send_led_data(led_data)