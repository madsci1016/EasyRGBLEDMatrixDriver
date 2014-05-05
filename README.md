EasyRGBLEDMatrixDriver
======================

Super Easy Arduino based serial backpack driver board for 16 x 32 RGB LED Matrix panels. 

The code and board  design will let you drive a 16x32 RGB LED matrix panel with a serial port, with some limitations. A example sketch for a master controller is included. 

Video Demo:  http://youtu.be/BNk5QkBuxNQ  

FEATURES:
Drive multiple panels off 1 serial port to create larger displays.

![Alt text](/Pics/0948.JPG "Optional title")
![Alt text](/Pics/0974.JPG "Optional title")
![Alt text](/Pics/0976.JPG "Optional title")

LIMITATIONS:
You only get half the resolution of the 16x32 pixel display, only 8x16 which is then scaled to 16x32
Refresh rate is limited by speed and number of displays on the Serial Port

This library is running off an Arduino is NOT powerful enough to display video, it's really meant for silly animations and Tetris. 

REQUIRES THE FOLLOWING LIBRARIES: 

https://github.com/adafruit/Adafruit-GFX-Library
https://github.com/adafruit/RGB-matrix-Panel
https://github.com/madsci1016/Arduino-EasyTransfer


To wire the display to the backpack arduino, see:
https://learn.adafruit.com/32x16-32x32-rgb-led-matrix/wiring-the-16x32-matrix 
