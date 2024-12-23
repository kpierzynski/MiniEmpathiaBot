from libcamera import Transform
from picamera2 import Picamera2
import numpy as np
import cv2
from time import sleep
from http.server import BaseHTTPRequestHandler, HTTPServer

# Default resolution
# CAMERA_MATRIX = [
#	[3.49919727e+03, 0.00000000e+00, 2.28261885e+03],
#	[0.00000000e+00, 3.51718681e+03, 1.31486006e+03],
#	[0.00000000e+00, 0.00000000e+00, 1.00000000e+00]
# ]
# CAMERA_DISTORTION_COEFFS = [-0.01855175,  0.50081026, -0.00410595, -0.00310608, -0.9912813 ]

# 1280x720
CAMERA_MATRIX = [
    [1.44224077e+03, 0.00000000e+00, 6.26541734e+02],
    [0.00000000e+00, 1.44528226e+03, 3.49586242e+02],
    [0.00000000e+00, 0.00000000e+00, 1.00000000e+00]
]

CAMERA_DISTORTION_COEFFS = [0.07475182, 0.05229402, -0.00607912, -0.00159385, -0.0832443]

last_frame = None


class VideoStreamHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        if self.path == '/video_feed':
            self.send_response(200)
            self.send_header('Content-type', 'multipart/x-mixed-replace; boundary=frame')
            self.end_headers()
            while True:
                if last_frame is not None:
                    _, buffer = cv2.imencode('.jpg', last_frame)
                    frame_data = buffer.tobytes()
                    self.wfile.write(b'--frame\r\n')
                    self.wfile.write(b'Content-Type: image/jpeg\r\n\r\n')
                    self.wfile.write(frame_data)
                    self.wfile.write(b'\r\n')

                    # set max fps to 1
                    sleep(1)
        else:
            self.send_response(404)
            self.end_headers()


class Camera:
    def __init__(self):
        self.camera_matrix = np.array(CAMERA_MATRIX)
        self.dist_coeffs = np.array(CAMERA_DISTORTION_COEFFS)

        self.picam2 = Picamera2()

        self._config = self.picam2.create_video_configuration(transform=Transform(180))
        self.picam2.configure(self._config)

        self.picam2.start()

    def __call__(self):
        global last_frame
        last_frame = self.picam2.capture_array()
        return last_frame

    def __del__(self):
        print("Camera destroyed.")
        self.picam2.stop()

    def _run_camera_server(self, port=8080):
        server_address = ('', port)
        httpd = HTTPServer(server_address, VideoStreamHandler)
        httpd.serve_forever()

    def serve_camera_feed(self):
        import threading
        self()
        threading.Thread(target=self._run_camera_server, daemon=True).start()