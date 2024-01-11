#!/bin/python3

import RPi.GPIO as GPIO
import time
RED_PIN = 33
GREEN_PIN = 12
BLUE_PIN = 32

PINS=[33,12,32]

print ("*****TRIPHAZARD***** rgbRed.py\n")

GPIO.setmode(GPIO.BOARD)
GPIO.setup(PINS, GPIO.OUT, initial=GPIO.LOW)

#GPIO.cleanup(33)
#GPIO.cleanup(12)
#GPIO.cleanup(23)



GPIO.setmode(GPIO.BCM)
GPIO.setup(RED_PIN, GPIO.OUT)
GPIO.output(RED_PIN, GPIO.LOW)
GPIO.setup(GREEN_PIN, GPIO.OUT)
GPIO.output(GREEN_PIN, GPIO.LOW)
GPIO.setup(BLUE_PIN, GPIO.OUT)
GPIO.output(BLUE_PIN, GPIO.LOW)


time.sleep(15)
#GPIO.output(LED_PIN, GPIO.LOW)
GPIO.cleanup()
