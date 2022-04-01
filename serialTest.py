#!/usr/bin/env python3
import serial
import time
import base64
lastKnownShoulderPos = 400
if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyACM0', 115200, timeout=1)
    ser.reset_input_buffer()

    f = open("shoulderLastPosition.txt", "r")
    print(f.read())
    lastKnownShoulderPos =  b'f.read()'
#    lastKnownShoulderPos = base64.b64encode(f.read().encode('utf-8',errors = 'strict'))
    while True:
       ser.write(b'"<ShoulderMove," + lastKnownShoulderPos + ",3.3>"')
       line = ser.readline().decode('utf-8').rstrip()
       print(line)
       time.sleep(1)
       f = open("shoulderLastPosition.txt", "w")
       f.write(line)
       f.close()
       ser.write(b"<ShoulderMove,700,3.3>")
       line = ser.readline().decode('utf-8').rstrip()
       print(line)
       time.sleep(1)
       f = open("shoulderLastPosition.txt", "w")
       f.write(line)
       f.close()
 
