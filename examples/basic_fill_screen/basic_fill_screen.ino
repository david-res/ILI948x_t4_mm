#define TFT_BL            5     // 5 - Backlight pin for TFT 
#define TFT_CS            8     // 8 - Chip select pin for TFT display
#define TFT_RST           9     // 9 - Hardware reset pin for TFT. Set to -1 for software reset
#define TFT_DC           10     //10 - Data/command pin for TFT

#define TFT_RD           37     //-1 - Read-strobe pin (-1 is disabled, tie to 3.3v) 
#define TFT_WR           30     //30 - Write-strobe pin 

//GPIO6_DR - bits 16..23, for 8 bit parallel
#define TFT_D0           19     //GIPO6-16  ->  19
#define TFT_D1           18     //GIPO6-17  ->  18
#define TFT_D2           14     //GIPO6-18  ->  14
#define TFT_D3           15     //GIPO6-19  ->  15
#define TFT_D4           40     //GIPO6-20  ->  40
#define TFT_D5           41     //GIPO6-21  ->  41
#define TFT_D6           17     //GIPO6-22  ->  17
#define TFT_D7           16     //GIPO6-23  ->  16

//GPIO6_DR - bits 24..31, for 16 bit parallel with D0-D7 above
#define TFT_D8           22     //GIPO6-24  ->  22
#define TFT_D9           23     //GIPO6-25  ->  23
#define TFT_D10          20     //GIPO6-26  ->  20
#define TFT_D11          21     //GIPO6-27  ->  21
#define TFT_D12          38     //GIPO6-28  ->  38
#define TFT_D13          39     //GIPO6-29  ->  39
#define TFT_D14          26     //GIPO6-30  ->  26
#define TFT_D15          27     //GIPO6-31  ->  27

#include "ILI9488_t4p.h"
ILI9488_t4p tft = ILI9488_t4p(TFT_D0, TFT_WR, TFT_DC, TFT_CS, TFT_RST, TFT_RD);

const uint16_t screenWidth = 480;
const uint16_t screenHeight = 320;

uint16_t dispBuffer[screenWidth * screenHeight];

void setup() 
{
  SerialUSB.begin(115200);
  
  tft.begin();
  tft.setBitDepth(16);  //Set TFT bitdepth to 16 bits per pixel
  tft.setRotation(3);   //Landscape rotation

  //Turn on backlight
  analogWrite(TFT_BL, 255);
}

void loop() 
{
  SerialUSB.print("Red - ");
  fillScreen(255, 0, 0);
  delay(1000);
  
  SerialUSB.print("Green - ");
  fillScreen(0, 255, 0);
  delay(1000);

  SerialUSB.print("Blue - ");
  fillScreen(0, 0, 255);
  delay(1000);

  SerialUSB.print("Random - ");
  fillScreen(random(255), random(255), random(255));
  delay(1000);
}

void fillScreen(uint8_t r, uint8_t g, uint8_t b) {

  //Munge 24 bit RGB into 16 bit colour
  uint16_t colour = ( (uint16_t)((r >> 3) << 11) | (uint16_t)((g >> 2) << 5) | (uint16_t)(b >> 3) );

  //Fill buffer with colour 
  for (uint16_t y=0; y<screenHeight; y++) {
    for (uint16_t x=0; x<screenWidth; x++) {
      dispBuffer[x + (y * screenWidth)] = colour;
    }
  }

  //Pointers to first and last entries in buffer to send
  uint16_t * bufStart = dispBuffer;
  uint16_t * bufEnd = dispBuffer + (screenWidth * screenHeight) - 1;

  uint32_t startTime = micros();
  tft.setAddrWindow(0, 0, screenWidth - 1, screenHeight - 1);
  tft.pushPixels16bit(bufStart, bufEnd, 0xFFFF);
  
  SerialUSB.printf("%luuS\n",micros()-startTime);
}