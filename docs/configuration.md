

## Raspberry Pi

```
hostname: plantbot
user: pi
pw: asdfasdf
```

## Get ready for I2C
`sudo apt-get install i2c-tools`

`ll /dev/i2c*`
- Shows only 1 device?

`sudo i2cdetect -y 1`

Python smbus package for *Python 3*
`sudo apt-get install python3-smbus`

Ensure user can access i2c
`sudo adduser pi i2c`


Upload the sketch test_i2c.ino

Disconnect USB, and connect Arduino to RPi GND and +5V

OR keep USB connected, and only connect the RPi GND to Arduino. This allows `Serial.print().`

Ensure i2cdetect finds the address 08