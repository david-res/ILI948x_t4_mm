# ILI948x_t4_mm
## A basic display driver for ILI948X series on a Teensy Micromod

**Disclaimer: This is an experimental library, currently a WIP. I cannot guarantee that all functions will work nor can I guarantee that this library will work with other libraries. Use at your own risk**  

This library can communicate (TX only at the moment) with an ILI9488/9486/9481 TFT LCD via an 8 bit parallel interface (8080)
It utilizes FlexIO and DMA to write data to the screen while offloading the task from the CPU.
It can only write an image array at the moment with defined start/end coordinates.
The default bus speed is set to 12Mhz and can be lowered or raised with a simple function call.

First include the library and create a constructor:
```
#include "ILI948x_t4_mm.h"
#define CS 11
#define DC 13
#define RST 12
ILI948x_t4_mm lcd = ILI948x_t4_mm(DC,CS,RST);
```
You can use and GPIO pins for CS, DC and RST

Next, wire up your LCD - use Teensy pins:
* pin 10 - WR
* pin 40 - D0
* pin 41 - D1
* pin 42 - D2
* pin 43 - D3
* pin 44 - D4
* pin 45 - D5
* pin 6 - D6
* pin 9 - D7
   
Wire the RD pin on the LCD to 3.3v

in the setup function call:
```
ILI948x_t4_mm::begin();
```
The default baud rate is 20Mhz

In the begin(n) function you can pass 2,4,8,12,20,24, 30 and 40 to lower or raise the baud rate.


Call the following function for a polling method write:
```
ILI948x_t4_mm::pushPixels16bit(flexio_teensy_mm,0,0,480,320);
```
or call the following function for an async DMA write
```
ILI948x_t4_mm::pushPixels16bitDMA(flexio_teensy_mm,0,0,480,320);
```
to push the image data, the arguments are as follows:
* uint16_t color array (RGB565)
* uint16_t x1
* uint16_t y1
* uint16_t x2
* uint16_t y2

Additional API's:


Set rotation: 1,2,3,4
```
ILI948x_t4_mm::setRotation(n);
```

Invert display color (true/false)
```
ILI948x_t4_mm::invertDisplay(bool);
```

Register a callback to trigger when the DMA transfer completes - ONLY ON DMA METHOD
```
ILI948x_t4_mm::onCompleteCB(CBF callback);
```
![Image of TFT with Teensy MM image](https://github.com/david-res/ILI948x_t4_mm/blob/master/mm_flexio_example.jpg)

