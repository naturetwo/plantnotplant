#
# f, b
# 1, 2, 3
# w, W
from smbus import SMBus
from time import sleep

addr = 0x8 # bus address
bus = SMBus(1) # indicates /dev/ic2-1
# bus.write_byte(addr, 0x1) # switch it on
# input("Press return to exit")
# bus.write_byte(addr, 0x0) # switch it on
while True:
    val = input("Character byte:")
    val = str(val)
    print(val)
    # print(hex(val))
    for c in val: 
        print(hex(ord(c)))
        bus.write_byte(addr, ord(c)) # switch it on
        sleep(0.5)
