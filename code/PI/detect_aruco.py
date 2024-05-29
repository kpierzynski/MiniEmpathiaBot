import cv2
import numpy as np

# Load the predefined dictionary
dict_aruco = cv2.aruco.getPredefinedDictionary(cv2.aruco.DICT_4X4_250)

# Initialize the detector parameters
parameters = cv2.aruco.DetectorParameters()
parameters.polygonalApproxAccuracyRate = 0.01
detector = cv2.aruco.ArucoDetector(dict_aruco, parameters)

# Define the marker length in !meters!
marker_length = 0.0355

def detect_aruco(frame, camera, draw_on_frame = False) -> list:
    markers = []

    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    corners, ids, _ = detector.detectMarkers(gray)

    if ids is None:
        return markers

    for i in range(len(ids)):
        retval, rvec, tvec = cv2.solvePnP(
            np.array([
                [0,0,0],
                [marker_length, 0, 0],
                [marker_length, marker_length, 0],
                [0, marker_length, 0]
            ]),
            corners[i][0],
            camera.camera_matrix,
            camera.dist_coeffs
        )

        tvec = np.array(tvec).reshape((3,1)).astype(np.float32)
        distance = np.linalg.norm(tvec)

        if draw_on_frame:
            rvec = np.array(rvec).reshape((3,1)).astype(np.float32)
            cv2.drawFrameAxes(frame, camera.camera_matrix, camera.dist_coeffs, rvec, tvec, 0.1, thickness=2)
            cv2.aruco.drawDetectedMarkers(frame, corners, ids)

            cv2.putText(
					frame,
					f"Dist: {distance:.2f}m",
					(int(corners[i][0][0][0]), int(corners[i][0][0][1]) - 10),
					cv2.FONT_HERSHEY_SIMPLEX,
					0.5,
					(0, 255, 0),
					2
				)

        markers.append({
            "id": ids[i],
            "distance": distance,
            "corners": corners[i]
        })

    return markers