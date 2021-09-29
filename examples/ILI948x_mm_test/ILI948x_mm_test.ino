#include "ILI948x_t4_mm.h"
#include "flexio_teensy_mm.c"
ILI948x_t4_mm lcd = ILI948x_t4_mm(13,11,12); //(dc, cs, rst)

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.print(CrashReport);
  
  lcd.begin();
  lcd.setRotation(3);
}

void loop() {
  delay(1000);
  lcd.pushPixels16bit(flexio_teensy_mm,0,0,479,319); // 480x320
  delay(1000);
  lcd.pushPixels16bitDMA(flexio_teensy_mm,0,0,479,319); // 480x320
  delay(1000);
}
