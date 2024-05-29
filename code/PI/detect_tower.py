import cv2
import numpy as np

hsv_ranges = {
    'lower_red_s': 102,
    'lower_red_v': 102,
    'upper_red1_h': 10,
    'lower_red2_h': 160,

    'lower_green_s': 114,
    'lower_green_v': 86,
    'lower_green_h': 41,
    'upper_green_h': 88,

    'lower_blue_s': 147,
    'lower_blue_v': 122,
    'lower_blue_h': 91,
    'upper_blue_h': 143
}

# Function to detect the LED towers in a frame and return their positions and colors
def detect_towers(frame, upper_red1_h, lower_red2_h, lower_green_h, upper_green_h, lower_blue_h, upper_blue_h, lower_red_s, lower_red_v, lower_green_s, lower_green_v, lower_blue_s, lower_blue_v):
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    lower_red1 = np.array([0, lower_red_s, lower_red_v])
    upper_red1 = np.array([upper_red1_h, 255, 255])
    lower_red2 = np.array([lower_red2_h, lower_red_s, lower_red_v])
    upper_red2 = np.array([180, 255, 255])

    lower_green = np.array([lower_green_h, lower_green_s, lower_green_v])
    upper_green = np.array([upper_green_h, 255, 255])

    lower_blue = np.array([lower_blue_h, lower_blue_s, lower_blue_v])
    upper_blue = np.array([upper_blue_h, 255, 255])

    mask_red1 = cv2.inRange(hsv, lower_red1, upper_red1)
    mask_red2 = cv2.inRange(hsv, lower_red2, upper_red2)
    mask_red = cv2.bitwise_or(mask_red1, mask_red2)
    mask_green = cv2.inRange(hsv, lower_green, upper_green)
    mask_blue = cv2.inRange(hsv, lower_blue, upper_blue)

    combined_mask = cv2.bitwise_or(mask_red, mask_green)
    combined_mask = cv2.bitwise_or(combined_mask, mask_blue)

    contours, _ = cv2.findContours(combined_mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    large_contours_mask = np.zeros_like(combined_mask)

    for contour in contours:
        area = cv2.contourArea(contour)
        if area > 500:
            cv2.drawContours(large_contours_mask, [contour], -1, 255, thickness=cv2.FILLED)

    # blend frame to connect nearby small rects to one
    kernel = np.ones((5, 5), np.uint8)
    dilated_mask = cv2.dilate(large_contours_mask, kernel, iterations=2)

    contours, _ = cv2.findContours(dilated_mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    detected_towers = []

    for contour in contours:
        x, y, w, h = cv2.boundingRect(contour)

        mask_roi_red = mask_red[y:y+h, x:x+w]
        mask_roi_green = mask_green[y:y+h, x:x+w]
        mask_roi_blue = mask_blue[y:y+h, x:x+w]

        red_count = cv2.countNonZero(mask_roi_red)
        green_count = cv2.countNonZero(mask_roi_green)
        blue_count = cv2.countNonZero(mask_roi_blue)

        if red_count > green_count and red_count > blue_count:
            color = 'red'
            color_rgb = (0, 0, 255)
        elif green_count > red_count and green_count > blue_count:
            color = 'green'
            color_rgb = (0, 255, 0)
        elif blue_count > red_count and blue_count > green_count:
            color = 'blue'
            color_rgb = (255, 0, 0)
        else:
            color = 'Unknown'
            continue

        font = cv2.FONT_HERSHEY_SIMPLEX
        font_scale = 1
        thickness = 2
        cv2.putText(frame, color, (x, y), font, font_scale, (255, 255, 255), thickness)
        cv2.rectangle(frame, (x, y), (x + w, y + h), color_rgb, 2)

        detected_towers.append(((x, y, w, h), color))

    return detected_towers

