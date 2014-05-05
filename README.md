EasyRGBLEDMatrixDriver
======================

Super Easy Arduino based serial backpack driver board for 16 x 32 RGB LED Matrix panels found here: http://www.adafruit.com/products/420

The code and board  design will let you drive a 16x32 RGB LED matrix panel with a serial port, with some limitations. A example sketch for a master controller is included. 

Video Demo:  http://youtu.be/BNk5QkBuxNQ  

FEATURES:
Drive multiple panels off 1 serial port to create larger displays.

LIMITATIONS:
You only get half the resolution of the 16x32 pixel display, only 8x16 which is then scaled to 16x32
Refresh rate is limited by speed and number of displays on the Serial Port

This library runs off of an Arduino Pro/Uno which is NOT powerful enough to display video. It's really meant for animations, text, and Tetris among other things.  

![Alt text](/Pics/0948.JPG "Optional title")
![Alt text](/Pics/0974.JPG "Optional title")
![Alt text](/Pics/0976.JPG "Optional title")
![Alt text](/Pics/PCB.png "Optional title")

In those pictures only 3 wires are shared by the 4 backpack Arduinos, 5V (Blue), GND (RED) and Data (Yellow) which is connected to the Serial RX of each Arduino (pin 1) the black wire (connected to TX of each Arduino) is not connected between each board. 

The 5th Arduino is the 'Master' and the Data line (Yellow) connects to it's Serial TX pin (Pin 0). 

Arduinos: https://www.sparkfun.com/products/11113
Wire and plug: https://www.sparkfun.com/products/9916

REQUIRES THE FOLLOWING LIBRARIES: 

https://github.com/adafruit/Adafruit-GFX-Library
https://github.com/adafruit/RGB-matrix-Panel
https://github.com/madsci1016/Arduino-EasyTransfer


To wire the display to the backpack arduino (Without my PCB), see:
https://learn.adafruit.com/32x16-32x32-rgb-led-matrix/wiring-the-16x32-matrix 
