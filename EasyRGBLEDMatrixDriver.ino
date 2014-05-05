// EasyRGBLEDMatrixDriver
// Super Easy Arduino based serial driver board for 16 x 32 RGB LED Matrix panels.
// Like:
// http://www.adafruit.com/products/420

// Written by Bill Porter
// www.billporter.info
// 
//  REQUIRES
//  https://github.com/adafruit/Adafruit-GFX-Library
//  https://github.com/adafruit/RGB-matrix-Panel
//  https://github.com/madsci1016/Arduino-EasyTransfer



// For multiple panel configurations, give each panel a unique address here
#define MYADDRESS 4

#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library
#include <EasyTransfer.h>

#define CLK 8  // MUST be on PORTB! (Use pin 11 on Mega)
#define LAT A3
#define OE  9
#define A   A0
#define B   A1 
#define C   A2
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);


//create COMMS object
EasyTransfer ET; 

struct RECEIVE_DATA_STRUCTURE{
  //put your variable definitions here for the data you want to send
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  byte address;
  byte displaydata[16][8];
} packet;

int color; //temp color variable

void setup() {

  matrix.begin();
  
  // draw a pixel in solid white
  matrix.drawPixel(0, 0, matrix.Color333(7, 7, 7)); 
  delay(500);
 
  // fix the screen with green
  matrix.fillRect(0, 0, 32, 16, matrix.Color333(0, 7, 0));
  delay(500);

  // draw a box in yellow
  matrix.drawRect(0, 0, 32, 16, matrix.Color333(7, 7, 0));
  delay(500);
  
  // draw an 'X' in red
  matrix.drawLine(0, 0, 31, 15, matrix.Color333(7, 0, 0));
  matrix.drawLine(31, 0, 0, 15, matrix.Color333(7, 0, 0));
  delay(500);
  
  // draw a blue circle
  matrix.drawCircle(7, 7, 7, matrix.Color333(0, 0, 7));
  delay(500);
  
  // fill a violet circle
  matrix.fillCircle(23, 7, 7, matrix.Color333(7, 0, 7));
  delay(500);
  
  // fill the screen with 'black'
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  
  // draw some text!
  matrix.setCursor(1, 0);   // start at top left, with one pixel of spacing
  matrix.setTextSize(1);    // size 1 == 8 pixels high
  
  // print each letter with a rainbow color
  matrix.setTextColor(matrix.Color333(7,0,0));
  matrix.print('1');
  matrix.setTextColor(matrix.Color333(7,4,0)); 
  matrix.print('6');
  matrix.setTextColor(matrix.Color333(7,7,0));
  matrix.print('x');
  matrix.setTextColor(matrix.Color333(4,7,0)); 
  matrix.print('3');
  matrix.setTextColor(matrix.Color333(0,7,0));  
  matrix.print('2');
  
  matrix.setCursor(1, 9);   // next line
  matrix.setTextColor(matrix.Color333(0,7,7)); 
  matrix.print('*');
  matrix.setTextColor(matrix.Color333(0,4,7)); 
  matrix.print('R');
  matrix.setTextColor(matrix.Color333(0,0,7));
  matrix.print('G');
  matrix.setTextColor(matrix.Color333(4,0,7)); 
  matrix.print("B");
  matrix.setTextColor(matrix.Color333(7,0,4)); 
  matrix.print("*");
  
  delay(500);
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  

 
 Serial.begin(57600);
 ET.begin(details(packet), &Serial);
 
  // whew!
}

void loop() {
  
  if(ET.receiveData()){
    //got packet, check address
    if(packet.address == 0) {
      //global address, listen to data
      //we have to scale up to our full resolution. 
      
       for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 8; j++) {
          //color needs to be promoted to Adafruit_GFX 5/6/5
          color = (((packet.displaydata[i][j] & 0b11100000) << 8) | ((packet.displaydata[i][j] & 0b00011100) << 6) | ((packet.displaydata[i][j] & 0b00000011) << 3));
            matrix.drawPixel(i*2, j*2, color);
            matrix.drawPixel(i*2+1, j*2, color);
            matrix.drawPixel(i*2, j*2+1, color);
            matrix.drawPixel(i*2+1, j*2+1, color);
          } 
       }
    }
    else if(packet.address == MYADDRESS){
      
      //ok, so we got data just for us. Let's shut the serial port down, and wait for a sync pulse. 
      Serial.end();
      pinMode(0, INPUT);
      
      //ttl idles high. Look for a sync pulse and timeout after 500ms. 
      long start = millis();
      
      while((millis() - start) < 500) {
       if(pulseIn(0, LOW) > 1000){
         //sync pulse received, put up data.
         for (int i = 0; i < 16; i++) {
          for (int j = 0; j < 8; j++) {
          //color needs to be promoted to Adafruit_GFX 5/6/5
            color = (((packet.displaydata[i][j] & 0b11100000) << 8) | ((packet.displaydata[i][j] & 0b00011100) << 6) | ((packet.displaydata[i][j] & 0b00000011) << 3));
            matrix.drawPixel(i*2, j*2, color);
            matrix.drawPixel(i*2+1, j*2, color);
            matrix.drawPixel(i*2, j*2+1, color);
            matrix.drawPixel(i*2+1, j*2+1, color);
          } 
         }
         
         //break out of while
         break;
       }
       
      }
      
      //restart serial
      Serial.begin(57600);
     
      
      
    }
  }
  
}
  
  



