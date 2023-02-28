import	serial
from 	pynput.mouse import Button, Controller
import	time
import	threading
import	struct
from	typing	import Final
from	math	import sin, cos, tan, radians

""" constant """
DATA_START:	Final = 0xAA
DATA_END:	Final = 0xDD
DATA_SIZE:	Final = 16
DEG_2_RAD:	Final =  0.01745329251994329576923690768489

class Coordinate:
	def __init__(self):
		self.euler_x = 0
		self.euler_y = 0
		self.euler_z = 0
		self.save_x = 0
		self.save_y = 0
		self.save_z = 0
		self.is_move = False
		self.button = 0

cd = Coordinate()

def read_data():
	if ser.readable():
		if (ser.in_waiting >= DATA_SIZE):
			data = ser.read()
			if data[0] != DATA_START:
				return
			data = ser.read(DATA_SIZE - 1)
			if data[-1] != DATA_END:
				return
			else:
				cd.euler_x = struct.unpack('f', data[0:4])[0]
				cd.euler_y = struct.unpack('f', data[4:8])[0]
				cd.euler_z = struct.unpack('f', data[8:12])[0]
				cd.save_x = cd.save_x * alpha + cd.euler_x * (1 - alpha)
				cd.save_y = cd.save_y * betha + cd.euler_y * (1 - betha)
				cd.save_z = cd.save_z * alpha + cd.euler_z * (1 - alpha)
				cd.is_move = data[12]
				cd.button = data[13]

init_ey = 0
init_ez = -0.06
width_s, height_s = 2560, 1440
print(width_s, height_s)
width_r = 173
d_r = 400
d_px = (d_r * width_s) / (width_r * 2)
mouse_x = 0
mouse_y = 0
x_scale = 10
y_scale = 10
f_mouse_x = 0
f_mouse_y = 0
alpha = 0.1
betha = 0.5
mouse = Controller()
mouse.position = (width_s / 2, height_s / 2)

ser = serial.Serial("/dev/ttyUSB0", 115200)

# thread1 = threading.Thread(target=read_data, daemon=True)
# thread1.start()
while True:
	read_data()
	# print(f"{cd.euler_x:.2f}, {cd.euler_y:.2f}, {cd.euler_z:.2f}")
	mouse_x = d_px * tan(cd.euler_z - init_ez) + (width_s / 2)
	mouse_y = d_px * tan(cd.euler_y - init_ey) + (height_s / 2)
	# f_mouse_x = f_mouse_x * alpha + mouse_x * (1 - alpha)
	# f_mouse_y = f_mouse_y  * alpha + mouse_y * (1 - alpha)
	f_mouse_x = mouse_x
	f_mouse_y = mouse_y
	# print(f"{f_mouse_x:.2f}, {f_mouse_y:.2f}")
	if (cd.is_move and 0 < f_mouse_x < width_s and 0 < f_mouse_y < height_s):
		mouse.position = (f_mouse_x, f_mouse_y)
	if (cd.button):
		init_ey = cd.euler_y
		init_ez = cd.euler_z

	# if (cd.button):
	# 	mouse.press(Button.left)
	# else:
	# 	mouse.release(Button.left)

