import time
import serial
from serial.serialutil import EIGHTBITS, PARITY_NONE, STOPBITS_ONE


ser = serial.Serial('/dev/ttyUSB0', baudrate=115200, bytesize=EIGHTBITS, stopbits=STOPBITS_ONE, parity=PARITY_NONE)


while(1):
    data = ser.read().decode('ascii')
    print(data, end='')
