// scrolltext demo for Adafruit RGBmatrixPanel library.
// Demonstrates double-buffered animation on our 16x32 RGB LED matrix:
// http://www.adafruit.com/products/420

// Written by Limor Fried/Ladyada & Phil Burgess/PaintYourDragon
// for Adafruit Industries.
// BSD license, all text above must be included in any redistribution.

#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library

// Similar to F(), but for PROGMEM string pointers rather than literals
#define F2(progmem_ptr) (const __FlashStringHelper *)progmem_ptr

#define CLK 11  // MUST be on PORTB! (Use pin 11 on Mega)
#define LAT A3
#define OE  9
#define A   A0
#define B   A1
#define C   A2
// Last parameter = 'true' enables double-buffering, for flicker-free,
// buttery smooth animation.  Note that NOTHING WILL SHOW ON THE DISPLAY
// until the first call to swapBuffers().  This is normal.
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, true);
// Double-buffered mode consumes nearly all the RAM available on the
// Arduino Uno -- only a handful of free bytes remain.  Even the
// following string needs to go in PROGMEM:

//char str[] PROGMEM = "Adafruit 16x32 RGB LED Matrix";
int  textX   = matrix.width();
int  textMin = 0 * -12;
int  hue     = 0;

char string0[20];
char string1[8];
int posicion=0;
int posicion2=0;
int borrar=0;
int fila=0;

int velocity=1;

void setup() {  
  matrix.begin();
  matrix.setTextWrap(false); // Allow text to run off right edge
  matrix.setTextSize(2);
  Serial.begin(14400);
}

void loop() {
    
  matrix.fillScreen(0);
  
  if (Serial.available()){
    int incomingByte = Serial.read();

    if(incomingByte == '\n') {  
        // ------
    }else if(incomingByte == '#') { 
      matrix.fillScreen(0);
      borrar=1;
      posicion=0;
    }else{
      borrar=0;     
      string0[posicion++]=(char)incomingByte;   
    }
  }
    
 if(borrar==1){
   matrix.fillScreen(0);
 }
 
 for(int j=0;j<posicion;j++){
   matrix.print(string0[j]);
 }
 
  textMin =  posicion * -12;
  Serial.print(textX);
  Serial.print(" <=> ");
  Serial.println(textMin);

  if((--textX) < textMin) textX = matrix.width();

  matrix.setCursor(textX, 1);
  matrix.setTextColor(matrix.ColorHSV(hue, 255, 255, true));
  hue += 7;
  if(hue >= 1536) hue -= 1536;
  delay(100);

  
  // Update display
  matrix.swapBuffers(false);
}
