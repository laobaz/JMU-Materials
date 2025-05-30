from pynq.overlays.base import BaseOverlay
from pynq_peripherals import ArduinoSEEEDGroveAdapter, PmodGroveAdapter
from time import sleep
import os#用import引用函数

base = BaseOverlay('base.bit')
adapter = ArduinoSEEEDGroveAdapter(base.ARDUINO, D5='grove_usranger')
usranger = adapter.D5
rgbleds = [base.rgbleds[i] for i in range(4, 6)]
leds = [base.leds[i] for i in range(4)]

while 1:
	length = int(usranger.get_distance())
	os.system("clear")
	if length==500:
		print('寄！')
		[led.off() for led in leds]
		[rgbled.on(4) for rgbled in rgbleds]
	else:
		print(f'所以结果为{length}cm')
		rgbleds[1].off()
		rgbleds[0].on(int(length/100)+1)
		temp = length-100*int(length/100)
		[led.off() for led in leds]
		if temp<=25:
			leds[0].on()
		elif temp>25 and temp<=50:
			leds[0].on()
			leds[1].on()
		elif temp>50 and temp<=75:
			leds[0].on()
			leds[1].on()
			leds[2].on()
		else:
			leds[0].on()
			leds[1].on()
			leds[2].on()
			leds[3].on()
	sleep(0.1)

