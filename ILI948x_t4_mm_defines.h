//#define ILI9481  
#define ILI9486
//#define ILI9488  

uint8_t Command;
uint8_t CommandValue[15];


#if defined (ILI9481)
    Command = 0x11; 
    CommandValue[0U] = 0x33;
    FLEXIO_8080_SglBeatWR_nPrm(Command, CommandValue, 1U);

    Command = 0x11; 
    FLEXIO_8080_SglBeatWR_nPrm(Command, 0, 0);
    delay(20);

    
    Command = 0xD0; 
    CommandValue[0U] = 0x07;
    CommandValue[1U] = 0x41;
    CommandValue[2U] = 0x1D;
    FLEXIO_8080_SglBeatWR_nPrm(Command, CommandValue, 3U);

    Command = 0xD1; 
    CommandValue[0U] = 0x00;
    CommandValue[1U] = 0x2B;
    CommandValue[2U] = 0x1F;
    FLEXIO_8080_SglBeatWR_nPrm(Command, CommandValue, 3U);

    Command = 0xD2; 
    CommandValue[0U] = 0x01;
    CommandValue[1U] = 0x11;
    FLEXIO_8080_SglBeatWR_nPrm(Command, CommandValue, 2U);

    Command = 0xC0; 
    CommandValue[0U] = 0x10;
    CommandValue[1U] = 0x3B;
    CommandValue[2U] = 0x00;
    CommandValue[3U] = 0x02;
    CommandValue[4U] = 0x11;
    CommandValue[5U] = 0x00;
    FLEXIO_8080_SglBeatWR_nPrm(Command, CommandValue, 6U);

    Command = 0xC5; 
    CommandValue[0U] = 0x03;
    FLEXIO_8080_SglBeatWR_nPrm(Command, CommandValue, 1U);

    Command = 0xC6; 
    CommandValue[0U] = 0x80;
    FLEXIO_8080_SglBeatWR_nPrm(Command, CommandValue, 1U);

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
    FLEXIO_8080_SglBeatWR_nPrm(Command, CommandValue, 12U);

    Command = 0xB0; 
    CommandValue[0U] = 0x00;
    FLEXIO_8080_SglBeatWR_nPrm(Command, CommandValue, 1U);

    Command = 0xE4; 
    CommandValue[0U] = 0xA0;
    FLEXIO_8080_SglBeatWR_nPrm(Command, CommandValue, 1U);
    
    Command = 0xF0; 
    CommandValue[0U] = 0x08;
    FLEXIO_8080_SglBeatWR_nPrm(Command, CommandValue, 1U);

    Command = 0xF3; 
    CommandValue[0U] = 0x40;
    CommandValue[1U] = 0x0A;
    FLEXIO_8080_SglBeatWR_nPrm(Command, CommandValue, 2U);
    

    Command = 0xF6; 
    CommandValue[0U] = 0x84;
    FLEXIO_8080_SglBeatWR_nPrm(Command, CommandValue, 1U);

    Command = 0xF7; 
    CommandValue[0U] = 0x80;
    FLEXIO_8080_SglBeatWR_nPrm(Command, CommandValue, 1U);

    Command = 0xB3; 
    CommandValue[0U] = 0x00;
    CommandValue[1U] = 0x01;
    CommandValue[2U] = 0x06;
    CommandValue[3U] = 0x30;
    FLEXIO_8080_SglBeatWR_nPrm(Command, CommandValue, 4U);

    Command = 0xB4; 
    CommandValue[0U] = 0x00;
    FLEXIO_8080_SglBeatWR_nPrm(Command, CommandValue, 1U);

    Command = 0x0C; 
    CommandValue[0U] = 0x00;
    CommandValue[1U] = 0x55;
    FLEXIO_8080_SglBeatWR_nPrm(Command, CommandValue, 2U);
    

    ommand = 0x36; // Memory Access Control
    CommandValue[0U] = 0x48;
    FLEXIO_8080_SglBeatWR_nPrm(Command, CommandValue, 1U);


    Command = 0x3A; // Set bit depth
    CommandValue[0U] = 0x55;
    FLEXIO_8080_SglBeatWR_nPrm(Command, CommandValue, 1U);
    
    Command = 0x21; // Display Inversion On
    FLEXIO_8080_SglBeatWR_nPrm(Command, 0, 0U);

    delay(120);
    Command = 0x29; // Display On
    FLEXIO_8080_SglBeatWR_nPrm(Command,0 ,0);

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
 
    Command = 0x20; // Display Inversion Control
    SglBeatWR_nPrm_8(Command, 0, 0);
    
    Command = 0x36; // Set rotation
    CommandValue[0U] = 0x40|0x80|0x20|0x08; //Landscape
    SglBeatWR_nPrm_8(Command, CommandValue, 1U);
    

    Command = 0x29; // Display Inversion Control
    SglBeatWR_nPrm_8(Command, 0, 0); // display on
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
#endif