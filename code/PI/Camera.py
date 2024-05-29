from libcamera import Transform
from picamera2 import Picamera2
import numpy as np

# Default resolution
#CAMERA_MATRIX = [
#	[3.49919727e+03, 0.00000000e+00, 2.28261885e+03],
#	[0.00000000e+00, 3.51718681e+03, 1.31486006e+03],
#	[0.00000000e+00, 0.00000000e+00, 1.00000000e+00]
#]
#CAMERA_DISTORTION_COEFFS = [-0.01855175,  0.50081026, -0.00410595, -0.00310608, -0.9912813 ]

#1280x720
CAMERA_MATRIX = [
	[1.44224077e+03, 0.00000000e+00, 6.26541734e+02],
	[0.00000000e+00, 1.44528226e+03, 3.49586242e+02],
	[0.00000000e+00, 0.00000000e+00, 1.00000000e+00]
]

CAMERA_DISTORTION_COEFFS = [ 0.07475182,  0.05229402, -0.00607912, -0.00159385, -0.0832443 ]

class Camera:
    def __init__(self):
        self.camera_matrix = np.array(CAMERA_MATRIX)
        self.dist_coeffs = np.array(CAMERA_DISTORTION_COEFFS)

        self.picam2 = Picamera2()

        self._config = self.picam2.create_video_configuration(transform=Transform(180))
        self.picam2.configure(self._config)

        self.picam2.start()

    def __call__(self):
        return self.picam2.capture_array()

    def __del__(self):
        print("Camera destroyed.")
        self.picam2.stop()