

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

# Packages

CV2

### Simple method:

`pip install opencv-python`

Doesn't work. 

`sudo apt-get install libgstreamer-plugins-base0.10-0`

Doesn't work. 

`sudo apt install libqt4-test`

Doesn't work. 

```shell
sudo apt install libatlas3-base libsz2 libharfbuzz0b libtiff5 libjasper1 libilmbase12 libopenexr22 libilmbase12 libgstreamer1.0-0 libavcodec57 libavformat57 libavutil55 libswscale4 libqtgui4 libqt4-test libqtcore4
sudo pip3 install opencv-contrib-python libwebp6
```

WORKS ??

### Masochistic method:

https://www.pyimagesearch.com/2017/09/04/raspbian-stretch-install-opencv-3-python-on-your-raspberry-pi/

???

# Webcam UV4L

https://medium.com/home-wireless/headless-streaming-video-with-the-raspberry-pi-zero-w-and-raspberry-pi-camera-38bef1968e1

# Controller

See this [guide](https://pythonhosted.org/triangula/sixaxis.html), summarized here: 

You’ll need to install some packages on your Pi first, and enable the bluetooth services:

```shell
sudo apt-get install bluetooth libbluetooth3 libusb-dev
sudo systemctl enable bluetooth.service
```

You also need to add the default user to the `bluetooth` group:

```shell
sudo usermod -G bluetooth -a pi
```

This tool can help debug the connection

```bash
sudo apt-get install joystick
sudo jstest --normal js0
```

Get and build the command line pairing tool:

```shell
wget http://www.pabr.org/sixlinux/sixpair.c
gcc -o sixpair sixpair.c -lusb
```

Connect controller with USB. 

```shell
sudo ./sixpair
Current Bluetooth master: 00:00:00:00:00:00
Setting master bd_addr to b8:27:eb:97:fd:6f
```

Disconnect controller. 

Reboot the Pi.

Run the bluetooth service, (not as `sudo`!). 

```
bluetoothctl
```

```shell
[bluetooth]# agent on
Agent registered
[bluetooth]# trust 60:38:0E:CC:0C:E3
[CHG] Device 60:38:0E:CC:0C:E3 Trusted: yes
Changing 60:38:0E:CC:0C:E3 trust succeeded
[bluetooth]# quit
Agent unregistered
[DEL] Controller 5C:F3:70:66:5C:E2
```

Disconnect controller.

Press center button, check `/dev/input`.