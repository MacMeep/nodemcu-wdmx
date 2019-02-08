import pigpio
import binascii
import time
import thread
import socket
import array

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)

p = pigpio.pi()
h = p.i2c_open(1, 0x08)

data = []

lastdata = []

def read_bytes():
  global data
  while True:
    allbytes = []
    for i in range(0, 17):
      bytes = p.i2c_read_device(h, 32)[1]
      if len(bytes) == 32:
        package_num = bytes[-1]
          while package_num != i:
            print("Inkorrekte Paketausrichtung...")
            print("Versuche automatisch zu reparieren...")
            bytes = p.i2c_read_device(h, 32)[1]
            if len(bytes) == 32:
              package_num = bytes[-1]
          if package_num == 16:
            allbytes[package_num*31:(package_num*31+30)] += bytes[:-16]
          else:
            allbytes[package_num*31:(package_num*31+30)] += bytes[:-1]
    data = allbytes

thread.start_new_thread(read_bytes, ())

time.sleep(2)

try:
  print("Start!")
  while True:
    if lastdata != data:
      sock.sendto(array.array('B', data).tostring(), ("192.168.4.255", 6666))
    lastdata = data
    time.sleep(0.01)
except (KeyboardInterrupt, SystemExit):
  print("Stop!")

