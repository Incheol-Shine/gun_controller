import serial
from pynput.mouse import Button, Controller
import time
import threading

from math import sin, cos, tan, radians

class ReadLine:
	def __init__(self, s):
		self.buf = bytearray()
		self.s = s

	def readline(self):
		i = self.buf.find(b"\n")
		if i >= 0:
			r = self.buf[:i+1]
			self.buf = self.buf[i+1:]
			return r
		while True:
			i = max(1, min(2048, self.s.in_waiting))
			data = self.s.read(i)
			i = data.find(b"\n")
			if i >= 0:
				r = self.buf + data[:i+1]
				self.buf[0:] = data[i+1:]
				return r
			else:
				self.buf.extend(data)


# def read_from_arduino():
# 	global euler_x
# 	global euler_y
# 	global euler_z

# 	while (not ser.readable()):
# 		continue
# 	for _ in range(10):
# 		reader.readline()

# 	while True:
# 		data = reader.readline().decode()
# 		# print(serial_x_y)
# 		euler_x, euler_y, euler_z = map(float, data.split())
# 		print(f"{euler_x:.2f}, {euler_y:.2f}, {euler_z:.2f}")

def read_from_arduino():
	global mouse_x
	global mouse_y
	global button

	while (not ser.readable()):
		continue
	for _ in range(10):
		reader.readline()

	while True:
		data = reader.readline().decode()
		# print(serial_x_y)
		mouse_x, mouse_y, button = map(float, data.split())
		mouse_x /= 100
		mouse_y /= 100
		mouse.move(mouse_x, mouse_y)
		if (button):
			mouse.press(Button.left)
		else:
			mouse.release(Button.left)
		print(f"{mouse_x:.2f}, {mouse_y:.2f}")


ser = serial.Serial("/dev/ttyUSB0", 115200)
reader = ReadLine(ser)

init_ex = 0
# init_ey = 7
# init_ez = 5
width_s, height_s = 2560, 1440
width_r = 173
d_r = 200
d_px = (d_r * width_s) / (width_r * 2)
euler_x = 0
euler_y = 0
euler_z = 0
mouse_x = 0
mouse_y = 0
button = 0
x_scale = 10
y_scale = 10
f_mouse_x = 0
f_mouse_y = 0
alpha = 0.3
mouse = Controller()
mouse.position = (width_s / 2, height_s / 2)


# thread1 = threading.Thread(target=read_from_arduino, daemon=True)
# thread1.start()
while True:
	read_from_arduino()
# 	f_mouse_x = f_mouse_x * alpha + mouse_x * (1 - alpha)
# 	f_mouse_y = f_mouse_y  * alpha + mouse_y * (1 - alpha)
# 	mouse.move(mouse_x, mouse_y)
