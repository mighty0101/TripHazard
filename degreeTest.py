#!/usr/bin/env python3
import serial
import time
import base64
if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyACM0', 115200, timeout=1)
    ser.reset_input_buffer()

#  ser.write(b'<ShoulderMove, + userInput + ,3.3>')
       #  lastKnownShoulderPos = base64.b64encode(f.read().encode('utf-8',errors = 'strict'))
    while True:
       userInput = input("enter command:  [command,interger,float] ")
       

       command = "<"+userInput+">"
#       userInputBytes = command
       ser.write(command.encode())
       line = ser.readline().decode("utf-8").rstrip()
       print(line)
       print("sent: " + command)
       time.sleep(1)
       
