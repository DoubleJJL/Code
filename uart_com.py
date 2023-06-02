import serial
import time

sp  = serial.Serial('COM5', 115200, timeout=1)

while True:
    value = input('pan value:')
    tx_dat = 'pan' + value + '\n'
    print(tx_dat)
    sp.write(tx_dat.encode())

    time.sleep(0.1)
