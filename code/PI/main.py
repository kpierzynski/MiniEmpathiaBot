from time import sleep, time
from random import randint as rnd
from math import inf

from Leds import Leds
from Serial import UART
from Camera import Camera

from detect_aruco import detect_aruco
from detect_tower import detect_towers, hsv_ranges

"""
GOAL VECTOR description:
1) do robot see target? 0 if not, else 1
2) distance to ARUCO (in meters), 1 as max distance
3) do robot see any green robot?
4) do robot see any blue robot?
5) is robot green now?

"""
GOALS = {
	"aruco": [1, 0.2, 0.5, 0.5, 1],
	"teamwork": [0, 1, 0.8, 0.8, 0]
}
THRESHOLD = 0.8

def fuzzy_similarity(vec1, vec2):
	assert len(vec1) == len(vec2)

	n = len(vec1)
	vec_sum = sum([ (x1-x2)*(x1-x2) for x1,x2 in zip(vec1, vec2)])

	return 1 - vec_sum**(1/2) / n


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
	# print(f"MOTORS RUNNING AT: {left_speed}, {right_speed}")

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
	sleep(0.1)	# Throttle loop a bit

	actual_robot_state = [0, 1, 0, 0, 0]

	frame = camera()
	if data := uart.read():
		vl_distance = parse_distance(data)
		if vl_distance:
			vl = vl_distance
			# print(f"vl sensor distance: {vl_distance}")

	markers = detect_aruco(frame, camera)
	marker_corners = None
	for marker in markers:
		id = marker['id']
		distance = marker['distance']
		marker_corners = marker['corners']

		actual_robot_state[0] = 1	# robot sees target
		actual_robot_state[1] = min(1, distance) # cap distance at 1m
		actual_robot_state[4] = 1	# robot sees target, so should be green, therefore 1
		# print(f"First marker distance is {distance}m.")
		break

	towers = detect_towers(frame, **hsv_ranges)
	tower_corners = None
	for (x,y,w,h), color in towers:
		if color == 'green' or color == 'blue':
			if color == 'green':
				actual_robot_state[2] = 1
			if color == 'blue':
				actual_robot_state[3] = 1

			tower_corners = [[
				[x,y], [x+w,y], [x+w,y+h], [x,y+h]
			]]
			# print(f"Detected tower on x:{x}, y:{y}, width:{w}, height:{h} in {color} color." )
			break

	evaluated_goals = {}
	for key, vector in GOALS.items():
		evaluated_goals[key] = fuzzy_similarity(vector, actual_robot_state)

	best_action = max(evaluated_goals, key=evaluated_goals.get)

	if evaluated_goals[best_action] < THRESHOLD:
		best_action = None

	match best_action:
		case "aruco":
			leds.set_leds(Leds.GREEN)
			if marker_corners is not None:
				steer_robot(marker_corners, actual_robot_state[1])
		case "teamwork":
			leds.set_leds(Leds.BLUE)
			if tower_corners is not None:
				steer_robot(tower_corners, 0.3)
		case _:
			leds.set_leds(Leds.RED)
			if vl < 50:
				uart.send_motor_config(0,0) # stop robot if too close
			else:
				spin()
