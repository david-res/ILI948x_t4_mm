//#define ILI9481  
#define ILI9486
//#define ILI9488  
//#define R61529  

uint8_t Command;
uint8_t CommandValue[25];


#if defined (ILI9481)
    Command = 0x11; 
    CommandValue[0U] = 0x33;
    SglBeatWR_nPrm_8(Command, CommandValue, 1U);

    Command = 0x11; 
    SglBeatWR_nPrm_8(Command, 0, 0);
    delay(20);

    
    Command = 0xD0; 
    CommandValue[0U] = 0x07;
    CommandValue[1U] = 0x41;
    CommandValue[2U] = 0x1D;
    SglBeatWR_nPrm_8(Command, CommandValue, 3U);

    Command = 0xD1; 
    CommandValue[0U] = 0x00;
    CommandValue[1U] = 0x2B;
    CommandValue[2U] = 0x1F;
    SglBeatWR_nPrm_8(Command, CommandValue, 3U);

    Command = 0xD2; 
    CommandValue[0U] = 0x01;
    CommandValue[1U] = 0x11;
    SglBeatWR_nPrm_8(Command, CommandValue, 2U);

    Command = 0xC0; 
    CommandValue[0U] = 0x10;
    CommandValue[1U] = 0x3B;
    CommandValue[2U] = 0x00;
    CommandValue[3U] = 0x02;
    CommandValue[4U] = 0x11;
    CommandValue[5U] = 0x00;
    SglBeatWR_nPrm_8(Command, CommandValue, 6U);

    Command = 0xC5; 
    CommandValue[0U] = 0x03;
    SglBeatWR_nPrm_8(Command, CommandValue, 1U);

    Command = 0xC6; 
    CommandValue[0U] = 0x80;
    SglBeatWR_nPrm_8(Command, CommandValue, 1U);

    Command = 0xC8; 
    CommandValue[0U] = 0x00;
    CommandValue[1U] = 0x14;
    CommandValue[2U] = 0x33;
    CommandValue[3U] = 0x10;
    CommandValue[4U] = 0x00;
    CommandValue[5U] = 0x16;
    CommandValue[6U] = 0x44;
    CommandValue[7U] = 0x36;
    CommandValue[8U] = 0x77;
    CommandValue[9U] = 0x00;
    CommandValue[10U] = 0x0F;
    CommandValue[11U] = 0x00;
    SglBeatWR_nPrm_8(Command, CommandValue, 12U);

    Command = 0xB0; 
    CommandValue[0U] = 0x00;
    SglBeatWR_nPrm_8(Command, CommandValue, 1U);

    Command = 0xE4; 
    CommandValue[0U] = 0xA0;
    SglBeatWR_nPrm_8(Command, CommandValue, 1U);
    
    Command = 0xF0; 
    CommandValue[0U] = 0x08;
    SglBeatWR_nPrm_8(Command, CommandValue, 1U);

    Command = 0xF3; 
    CommandValue[0U] = 0x40;
    CommandValue[1U] = 0x0A;
    SglBeatWR_nPrm_8(Command, CommandValue, 2U);
    

    Command = 0xF6; 
    CommandValue[0U] = 0x84;
    SglBeatWR_nPrm_8(Command, CommandValue, 1U);

    Command = 0xF7; 
    CommandValue[0U] = 0x80;
    SglBeatWR_nPrm_8(Command, CommandValue, 1U);

    Command = 0xB3; 
    CommandValue[0U] = 0x00;
    CommandValue[1U] = 0x01;
    CommandValue[2U] = 0x06;
    CommandValue[3U] = 0x30;
    SglBeatWR_nPrm_8(Command, CommandValue, 4U);

    Command = 0xB4; 
    CommandValue[0U] = 0x00;
    SglBeatWR_nPrm_8(Command, CommandValue, 1U);

    Command = 0x0C; 
    CommandValue[0U] = 0x00;
    CommandValue[1U] = 0x55;
    SglBeatWR_nPrm_8(Command, CommandValue, 2U);
    

    Command = 0x36; // Memory Access Control
    CommandValue[0U] = 0x48;
    SglBeatWR_nPrm_8(Command, CommandValue, 1U);


    Command = 0x3A; // Set bit depth
    CommandValue[0U] = 0x55;
    SglBeatWR_nPrm_8(Command, CommandValue, 1U);
    
    Command = 0x21; // Display Inversion On
    SglBeatWR_nPrm_8(Command, 0, 0U);

    delay(120);
    Command = 0x29; // Display On
    SglBeatWR_nPrm_8(Command,0 ,0);

#elif defined (ILI9486)
    Command = 0x11; // Sleep out, also SW reset
    SglBeatWR_nPrm_8(Command, 0, 0);
    delay(120);

    Command = 0x3A; // Set bit depth
    CommandValue[0U] = 0x55;
    SglBeatWR_nPrm_8(Command, CommandValue, 1U);

    Command = 0xC2; // Power Control 3
    CommandValue[0U] = 0x44;
    SglBeatWR_nPrm_8(Command, CommandValue, 1U);

    
    Command = 0xC5; // VCOM control
    CommandValue[0U] = 0x00;
    CommandValue[1U] = 0x00;
    CommandValue[2U] = 0x00;
    CommandValue[3U] = 0x00;
    SglBeatWR_nPrm_8(Command, CommandValue, 4U);

    Command = 0xE0; // Gamma Setting  
    CommandValue[0U] = 0x0F;
    CommandValue[1U] = 0x1F;
    CommandValue[2U] = 0x1C;
    CommandValue[3U] = 0x0C;
    CommandValue[4U] = 0x0C;
    CommandValue[5U] = 0x08;
    CommandValue[6U] = 0x48;
    CommandValue[7U] = 0x98;
    CommandValue[8U] = 0x37;
    CommandValue[9U] = 0x0A;
    CommandValue[10U] = 0x13;
    CommandValue[11U] = 0x04;
    CommandValue[12U] = 0x11;
    CommandValue[13U] = 0x0D;
    CommandValue[14U] = 0x00;
    SglBeatWR_nPrm_8(Command, CommandValue, 15U);
 
    
    Command = 0xE1; // Negative Gamma Setting  
    CommandValue[0U] = 0x0F;
    CommandValue[1U] = 0x32;
    CommandValue[2U] = 0x2E;
    CommandValue[3U] = 0x0B;
    CommandValue[4U] = 0x0D;
    CommandValue[5U] = 0x05;
    CommandValue[6U] = 0x47;
    CommandValue[7U] = 0x75;
    CommandValue[8U] = 0x37;
    CommandValue[9U] = 0x06;
    CommandValue[10U] = 0x10;
    CommandValue[11U] = 0x03;
    CommandValue[12U] = 0x24;
    CommandValue[13U] = 0x20;
    CommandValue[14U] = 0x00;
    SglBeatWR_nPrm_8(Command, CommandValue, 15U);

    Command = 0x36; // Memory Access Control
    CommandValue[0U] = 0x48;
    SglBeatWR_nPrm_8(Command, CommandValue, 1U);
 
    Command = 0x20; // Display Inversion OFF
    SglBeatWR_nPrm_8(Command, 0, 0);
    
    Command = 0x29; // Display ON
    SglBeatWR_nPrm_8(Command, 0, 0); 
    delay(150);
    Serial.println("LCD Init");


#elif defined (ILI9488)

    Command = 0x01; //SW RST
    SglBeatWR_nPrm_8(Command,0 ,0);
    delay(120);
    
    Command = 0x11; //Exit sleep
    SglBeatWR_nPrm_8(Command ,0 ,0);
    delay(15);
    Command = 0x28; //Display Off
    SglBeatWR_nPrm_8(Command ,0 ,0);
    delay(15);
    
    Command = 0xC0; // Power Control 1
    CommandValue[0U] = 0x19;
    CommandValue[1U] = 0x1A;
    SglBeatWR_nPrm_8(Command, CommandValue, 2U);

    Command = 0xC1; // Power Control 2
    CommandValue[0U] = 0x45;
    CommandValue[1U] = 0x00;
    SglBeatWR_nPrm_8(Command, CommandValue, 2U);

    Command = 0xC2; // Power Control 3
    CommandValue[0U] = 0x33;
    SglBeatWR_nPrm_8(Command, CommandValue, 1U);

    Command = 0xC5; // VCOM control
    CommandValue[0U] = 0x00;
    CommandValue[1U] = 0x12;
    CommandValue[2U] = 0x80;
    SglBeatWR_nPrm_8(Command, CommandValue, 3U);

    Command = 0xB4; // Display Inversion Control
    CommandValue[0U] = 0x02;
    SglBeatWR_nPrm_8(Command, CommandValue, 1U);

    Command = 0xB6; // Display Function Control  RGB/MCU Interface Control
    CommandValue[0U] = 0x00;
    CommandValue[1U] = 0x02;
    CommandValue[2U] = 0x3B;
    SglBeatWR_nPrm_8(Command, CommandValue, 3U);

    Command = 0xB7; // Entry Mode Set
    CommandValue[0U] = 0x07;
    SglBeatWR_nPrm_8(Command, CommandValue, 1U);

    Command = 0xE0; // Gamma Setting  
    CommandValue[0U] = 0x00;
    CommandValue[1U] = 0x03;
    CommandValue[2U] = 0x09;
    CommandValue[3U] = 0x08;
    CommandValue[4U] = 0x16;
    CommandValue[5U] = 0x0A;
    CommandValue[6U] = 0x3F;
    CommandValue[7U] = 0x78;
    CommandValue[8U] = 0x4C;
    CommandValue[9U] = 0x09;
    CommandValue[10U] = 0x0A;
    CommandValue[11U] = 0x08;
    CommandValue[12U] = 0x16;
    CommandValue[13U] = 0x1A;
    CommandValue[14U] = 0x0F;
    SglBeatWR_nPrm_8(Command, CommandValue, 15U);

    Command = 0xE1; // Negative Gamma Setting  
    CommandValue[0U] = 0x00;
    CommandValue[1U] = 0x16;
    CommandValue[2U] = 0x19;
    CommandValue[3U] = 0x03;
    CommandValue[4U] = 0x0F;
    CommandValue[5U] = 0x05;
    CommandValue[6U] = 0x32;
    CommandValue[7U] = 0x45;
    CommandValue[8U] = 0x46;
    CommandValue[9U] = 0x04;
    CommandValue[10U] = 0x0E;
    CommandValue[11U] = 0x0D;
    CommandValue[12U] = 0x35;
    CommandValue[13U] = 0x37;
    CommandValue[14U] = 0x0F;
    SglBeatWR_nPrm_8(Command, CommandValue, 15U);

    Command = 0x36; // Memory Access Control
    CommandValue[0U] = 0x48;
    SglBeatWR_nPrm_8(Command, CommandValue, 1U);

    //delay(10);
    Command = 0x29; // Display On
    SglBeatWR_nPrm_8(Command,0 ,0);
    delay(15);

    Command = 0x3A; // Set bit depth
    CommandValue[0U] = 0x55;
    SglBeatWR_nPrm_8(Command, CommandValue, 1U);

    Command = 0x36; // Set rotation
    CommandValue[0U] = 0x40|0x80|0x20|0x08; //Landscape
    SglBeatWR_nPrm_8(Command, CommandValue, 1U);

    

#elif define(R61529)
    Command = 0x11; //TFT_SLPOUT
    delay(20);
    SglBeatWR_nPrm_8(Command, 0, 0);

    Command = 0xB0;
    CommandValue[0U] = 0x04;
    SglBeatWR_nPrm_8(Command, CommandValue, 1U);
    delay(2);

    Command = 0xB8; //lcd pwm
    CommandValue[0U] = 0x02;
    CommandValue[1U] = 0x00;
    CommandValue[2U] = 0x00;
    CommandValue[3U] = 0x00;
    CommandValue[4U] = 0x00;
    CommandValue[5U] = 0x00;
    CommandValue[6U] = 0x00;
    CommandValue[7U] = 0x00;
    CommandValue[8U] = 0x00;
    CommandValue[9U] = 0x00;
    CommandValue[10U] = 0x00;
    CommandValue[11U] = 0x00;
    CommandValue[12U] = 0x00;
    CommandValue[13U] = 0x00;
    CommandValue[14U] = 0x00;
    CommandValue[15U] = 0x00;
    CommandValue[16U] = 0x00;
    CommandValue[17U] = 0x00;
    CommandValue[18U] = 0x00;
    CommandValue[19U] = 0x00;
    SglBeatWR_nPrm_8(Command, CommandValue, 20U);

    Command = 0xB9; //lcd pwm
    CommandValue[0U] = 0x01; // PWMON = 1;
    CommandValue[1U] = 0x00; // BDCV = 255;
    CommandValue[2U] = 0xff; // pwm freq = 13.7 kHz
    CommandValue[3U] = 0x18; // PWMWM = 1; LEDPWME = 1;
    SglBeatWR_nPrm_8(Command, CommandValue, 4U);

    //additional commands:
    Command = 0xB3; //Frame Memory Access and Interface Setting
    CommandValue[0U] = 0x02; // reset start position of a window area address...
    CommandValue[1U] = 0x00; //TE pin is used. TE signal is output every frame.
    CommandValue[2U] = 0x00; // empty according to the datasheet - does nothing;
    CommandValue[3U] = 0x00; // convert 16/18 bits to 24bits data by writing zeroes to LSBs. Sets image data write/read format(?)
    CommandValue[4U] = 0x00;  // ???? (not needed?)
    SglBeatWR_nPrm_8(Command, CommandValue, 5U);
    delay(2);

    Command = 0xB4; //Display Mode
    CommandValue[0U] = 0x00; //Uses internal oscillator
    SglBeatWR_nPrm_8(Command, CommandValue, 1U);

    Command = 0xC0; // Panel Driving Setting;
    CommandValue[0U] = 0x03; // Output polarity is inverted. Left/right interchanging scan. Forward scan. BGR mode (depends on other settings). S960 → S1 (depends)
    CommandValue[1U] = 0xDF; // Number of lines for driver to drive - 480.
    CommandValue[2U] = 0x40; // Scan start position - Gate1. (depend on other param);
    CommandValue[3U] = 0x10; // Dot inversion. Dot inversion in not-lit display area. If 0x13 - both will be set to 'column inversion'.
    CommandValue[4U] = 0x00; // settings for non-lit display area...
    CommandValue[5U] = 0x01; // 3 frame scan interval in non-display area...
    CommandValue[6U] = 0x00; // Source output level in retrace period...
    CommandValue[7U] = 0x55;//54 . Internal clock divider = 5 (low and high periods).
    SglBeatWR_nPrm_8(Command, CommandValue, 8U);

    Command = 0xC1; //Display Timing Setting for Normal Mode
    CommandValue[0U] = 0x07; // Clock devider = 12. 14MHz/12. Used by display circuit and step-up circuit.
    CommandValue[1U] = 0x27; // These bits set the number of clocks in 1 line period. 0x27 - 39 clocks.
    CommandValue[2U] = 0x08; // Number of back porch lines. 0x08 - 8 lines.
    CommandValue[3U] = 0x08; // Number of front porch lines. 0x08 - 8lines.
    CommandValue[4U] = 0x00; // Spacial configuriation mode 1 (?). 1 line inversion mode (?).
    SglBeatWR_nPrm_8(Command, CommandValue, 5U);

    Command = 0xC4; // Source/Gate Driving Timing Setting
    CommandValue[0U] = 0x57; // falling position (stop) of gate driver - 4 clocks... gate start position - 8 clocks...
    CommandValue[1U] = 0x00; // nothing to set up according to the datasheet
    CommandValue[2U] = 0x05; // Source precharge period (GND) - 5 clocks.
    CommandValue[3U] = 0x03; // source precharge period (VCI) - 3 clocks.
    SglBeatWR_nPrm_8(Command, CommandValue, 4U);

    Command = 0xC6; //DPI polarity control
    CommandValue[0U] = 0x04; // VSYNC -Active Low. HSYNC - Active Low. DE pin enable data write in when DE=1. Reads data on the rising edge of the PCLK signal.
    SglBeatWR_nPrm_8(Command, CommandValue, 1U);

    //----Gamma setting start-----
    Command = 0xC8;
    CommandValue[0U] = 0x03;
    CommandValue[1U] = 0x12;
    CommandValue[2U] = 0x1A;
    CommandValue[3U] = 0x24;
    CommandValue[4U] = 0x32;
    CommandValue[5U] = 0x4B;
    CommandValue[6U] = 0x3B;
    CommandValue[7U] = 0x29;
    CommandValue[8U] = 0x1F;
    CommandValue[9U] = 0x18;
    CommandValue[10U] = 0x12;
    CommandValue[11U] = 0x04;

    CommandValue[12U] = 0x03;
    CommandValue[13U] = 0x12;
    CommandValue[14U] = 0x1A;
    CommandValue[15U] = 0x24;
    CommandValue[16U] = 0x32;
    CommandValue[17U] = 0x4B;
    CommandValue[18U] = 0x3B;
    CommandValue[19U] = 0x29;
    CommandValue[20U] = 0x1F;
    CommandValue[21U] = 0x18;
    CommandValue[22U] = 0x12;
    CommandValue[23U] = 0x04;
    SglBeatWR_nPrm_8(Command, CommandValue, 24);

    Command = 0xC9;
    CommandValue[0U] = 0x03;
    CommandValue[1U] = 0x12;
    CommandValue[2U] = 0x1A;
    CommandValue[3U] = 0x24;
    CommandValue[4U] = 0x32;
    CommandValue[5U] = 0x4B;
    CommandValue[6U] = 0x3B;
    CommandValue[7U] = 0x29;
    CommandValue[8U] = 0x1F;
    CommandValue[9U] = 0x18;
    CommandValue[10U] = 0x12;
    CommandValue[11U] = 0x04;

    CommandValue[12U] = 0x03;
    CommandValue[13U] = 0x12;
    CommandValue[14U] = 0x1A;
    CommandValue[15U] = 0x24;
    CommandValue[16U] = 0x32;
    CommandValue[17U] = 0x4B;
    CommandValue[18U] = 0x3B;
    CommandValue[19U] = 0x29;
    CommandValue[20U] = 0x1F;
    CommandValue[21U] = 0x18;
    CommandValue[22U] = 0x12;
    CommandValue[23U] = 0x04;
    SglBeatWR_nPrm_8(Command, CommandValue, 24);

    Command = 0xCA;
    CommandValue[0U] = 0x03;
    CommandValue[1U] = 0x12;
    CommandValue[2U] = 0x1A;
    CommandValue[3U] = 0x24;
    CommandValue[4U] = 0x32;
    CommandValue[5U] = 0x4B;
    CommandValue[6U] = 0x3B;
    CommandValue[7U] = 0x29;
    CommandValue[8U] = 0x1F;
    CommandValue[9U] = 0x18;
    CommandValue[10U] = 0x12;
    CommandValue[11U] = 0x04;

    CommandValue[12U] = 0x03;
    CommandValue[13U] = 0x12;
    CommandValue[14U] = 0x1A;
    CommandValue[15U] = 0x24;
    CommandValue[16U] = 0x32;
    CommandValue[17U] = 0x4B;
    CommandValue[18U] = 0x3B;
    CommandValue[19U] = 0x29;
    CommandValue[20U] = 0x1F;
    CommandValue[21U] = 0x18;
    CommandValue[22U] = 0x12;
    CommandValue[23U] = 0x04;
    SglBeatWR_nPrm_8(Command, CommandValue, 24);
//---Gamma setting end--------
    //old ones:
    Command = 0xD0;
    CommandValue[0U] = 0x99;//DC4~1//A5. Set up clock cycle of the internal step up controller.
    CommandValue[1U] = 0x06;//BT // Set Voltage step up factor.
    CommandValue[2U] = 0x08;// default according to the datasheet - does nothing.
    CommandValue[3U] = 0x20;// VCN step up cycles.
    CommandValue[4U] = 0x29;//VC1, VC2// VCI3 voltage = 2.70V;  VCI2 voltage = 3.8V.
    CommandValue[5U] = 0x04;// default 
    CommandValue[6U] = 0x01;// default 
    CommandValue[7U] = 0x00;// default 
    CommandValue[8U] = 0x08;// default
    CommandValue[9U] = 0x01;// default
    CommandValue[10U]= 0x00;// default
    CommandValue[11U]= 0x06;// default
    CommandValue[12U]= 0x01;// default
    CommandValue[13U]= 0x00;// default
    CommandValue[14U]= 0x00;// default
    CommandValue[15U]= 0x20;// default
    SglBeatWR_nPrm_8(Command, CommandValue, 16);

    Command = 0xD1;//VCOM setting
    CommandValue[0U] = 0x00;//disable write to VDC[7:0]
    CommandValue[1U] = 0x20;//45 38 VPLVL// voltage of γ correction registers for positive polarity
    CommandValue[2U] = 0x20;//45 38 VNLVL// voltage of γ correction registers for negative polarity
    CommandValue[3U] = 0x15;//32 2A VCOMDC// VNLVL x 0.063
    SglBeatWR_nPrm_8(Command, CommandValue, 4);

    Command = 0xE0;//NVM Access Control
    CommandValue[0U] = 0x00;//NVM access is disabled
    CommandValue[1U] = 0x00;//Erase operation (disabled).
    CommandValue[2U] = 0x00;//TE pin works as tearing effect pin. 
    // should be one more CommandValue[3U] = 0x00; according to the datasheet.
    SglBeatWR_nPrm_8(Command, CommandValue, 3);

    Command = 0xE1; //set_DDB_write_control
    CommandValue[0U] = 0x00; 
    CommandValue[1U] = 0x00;
    CommandValue[2U] = 0x00;
    CommandValue[3U] = 0x00;
    CommandValue[4U] = 0x00;
    CommandValue[5U] = 0x00;
    SglBeatWR_nPrm_8(Command, CommandValue, 6);

    Command = 0xE2; //NVM Load Control
    CommandValue[0U] = 0x00; // does not execute data load from the NVM to each command
    SglBeatWR_nPrm_8(Command, CommandValue, 1);

    Command = 0x36; //MADCTL
    CommandValue[0U] = 0x00;
    SglBeatWR_nPrm_8(Command, CommandValue, 1);

    Command = 0x3A; // set_pixel_format
    CommandValue[0U] = 0x55); // 16-Bit/pixel = 55h, 24-bit/pixel = 77h
    SglBeatWR_nPrm_8(Command, CommandValue, 1);

    Command = 0x2A; // TFT_CASET
    CommandValue[0U] = 0x00;
    CommandValue[1U] = 0x00;
    CommandValue[2U] = 0x01;
    CommandValue[3U] = 0x3F;
    SglBeatWR_nPrm_8(Command, CommandValue, 4);

    Command = 0x2B; //TFT_PASET
    CommandValue[0U] = 0x00;
    CommandValue[1U] = 0x00;
    CommandValue[2U] = 0x01;
    CommandValue[3U] = 0xDF;
    SglBeatWR_nPrm_8(Command, CommandValue, 4);

    delay(120);
    Command = 0x29; //TFT_DISPON
    SglBeatWR_nPrm_8(Command, CommandValue, 0);

    delay(250);
#endif