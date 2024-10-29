from time import sleep, time
from random import randint as rnd

from Leds import Leds
from Serial import UART
from Camera import Camera

from detect_aruco import detect_aruco
from detect_tower import detect_towers, hsv_ranges

camera = Camera()
uart = UART(baudrate=115200, port="/dev/serial0")
leds = Leds()

def send_motor(left,right, override=False):
	if vl < 80 and not override:
		uart.send_motor_config(0,0)
	else:
		uart.send_motor_config(left, right)

def steer_robot(corners, distance):
	if distance < 0.2:
		send_motor(0, 0)
		print("STOPPED MOTOR")
		exit()
		return

	center_x = sum(corner[0] for corner in corners[0]) / 4
	image_center_x = 1280 / 2

	if center_x < image_center_x - 100:
		left_speed = 100
		right_speed = 110
	elif center_x > image_center_x + 100:
		left_speed = 110
		right_speed = 100
	else:
		left_speed = right_speed = 110 if distance > 0.75 else 80

	send_motor(left_speed, right_speed)
	print(f"MOTORS RUNNING AT: {left_speed}, {right_speed}")

def spin():
	if vl > 500:
		send_motor(50,50)
		return

	#if vl < 200 and 0 == 1:
	#	return

	if rnd(0,4):
		send_motor(35,0, override = vl < 250)
	else:
		send_motor(0,25, override = vl < 250)

def parse_distance(buf):
	try:
		parsed_distance = int( [ x.split(': ')[1] for x in buf.split("\n\r") if x ][-1] )
	except:
		return None

	return parsed_distance

vl = 1

timeout = 1.5
start_time = time()

while True:
	sleep(0.2)	# Throttle loop a bit

	frame = camera()
	if data := uart.read():
		vl_distance = parse_distance(data)
		if vl_distance:
			vl = vl_distance
			print(f"vl sensor distance: {vl_distance}")

	markers = detect_aruco(frame, camera)
	for marker in markers:
		id = marker['id']
		distance = marker['distance']
		corners = marker['corners']

		steer_robot(corners, distance)

		print(f"First marker distance is {distance}m.")
		break

	if len(markers):
		leds.set_leds(Leds.GREEN)
		continue

	towers = detect_towers(frame, **hsv_ranges)
	for (x,y,w,h), color in towers:
		if color == 'green' or color == 'blue':
			leds.set_leds(Leds.BLUE)
			corners = [[
				[x,y], [x+w,y], [x+w,y+h], [x,y+h]
			]]
			steer_robot(corners, 0.3)
			print(f"Detected tower on x:{x}, y:{y}, width:{w}, height:{h} in {color} color." )
			break

	if not len(markers) and not any(rect[1] == 'green' or rect[1] == 'blue' for rect in towers):
		print("EMPTY")
		if time() - start_time > timeout:
			leds.set_leds(Leds.RED)
			spin()
			start_time = time()
	else:
		print("NOT EMPTY")

