#!/usr/bin/python3

################################
### Begin i2c keyboard input ###
################################
from smbus import SMBus
from time import sleep

addr = 0x8 # bus address
bus = SMBus(1) # indicates /dev/ic2-1

numb = 1

print ("Enter Command:")
while numb == 1:

	ledstate = input(">>>>   ")

#	if ledstate == "1":
#		sleep(0.5)
		bus.write_byte(addr, 0x1) # switch it on
#	elif ledstate == "0":
#		sleep(0.5)
#		bus.write_byte(addr, 0x0) # switch it on
#	else:
		numb = 0
##############################
### End i2c keyboard input ###
##############################





