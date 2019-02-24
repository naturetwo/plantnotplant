#
from smbus import SMBus

ADDR_TRACK_CNTRL = 0x8  # I2C bus address
ADDR_STEP_CTRL = 0x9  # I2C bus address

I2C_MAP = {8: ADDR_TRACK_CNTRL, 9: ADDR_STEP_CTRL}

bus = SMBus(1)  # indicates /dev/ic2-1
# bus.write_byte(addr, 0x1) # switch it on
# input("Press return to exit")
# bus.write_byte(addr, 0x0) # switch it on
while True:
    this_addr = input("Address (8 or 9)")
    if this_addr not in [8, 9]:
        continue
    print("Address selected:", val)
    this_pin = input("Pin? (1-13)")
    if this_pin not in list(range(1,14)):
        continue

    print(hex(val))
    print(hex(ord(val)))
    bus.write_byte(addr, ord(val))  # switch it on
