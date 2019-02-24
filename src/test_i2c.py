#
from smbus import SMBus
from time import sleep

ADDR_TRACK_CNTRL = 0x8  # I2C bus address
ADDR_STEP_CTRL = 0x9  # I2C bus address

I2C_MAP = {8: ADDR_TRACK_CNTRL, 9: ADDR_STEP_CTRL}

bus = SMBus(1)  # indicates /dev/ic2-1
# bus.write_byte(addr, 0x1) # switch it on
# input("Press return to exit")
# bus.write_byte(addr, 0x0) # switch it on
while True:

    this_addr = input("Address (8 or 9):")
    this_addr = int(this_addr)
    print(this_addr, type(this_addr))
    if this_addr not in [8, 9]:
        continue
    print("Address selected:", this_addr)

    # this_pin = input("Pin? (1-13)")
    # if this_pin not in list(range(1,14)):
    #     continue

    this_val = input("Input character:")

#    print(hex(this_val))
    print(hex(ord(this_val)))
    bus.write_byte(this_addr, ord(val))
    bus.write_byte(this_addr, ord(this_val))


#    val = input("Character byte:")
#    val = str(val)
#    print(val)
#    # print(hex(val))
#    for c in val:
#        print(hex(ord(c)))
#        bus.write_byte(addr, ord(c)) # switch it on
#        sleep(0.5)
