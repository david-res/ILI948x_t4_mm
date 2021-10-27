#include "ILI948x_t4_mm.h"
//DMAMEM uint32_t framebuff[DATABUFBYTES];

#if !defined(ARDUINO_TEENSY_MICROMOD)
#error This library only supports the Teensy Micromod!
#endif

FLASHMEM ILI948x_t4_mm::ILI948x_t4_mm(int8_t dc, int8_t cs, int8_t rst) 
{
  
  _dc = dc;
  _cs = cs;
  _rst = rst;
  
}

FLASHMEM void ILI948x_t4_mm::begin(uint8_t buad_div) 
{
  //Serial.printf("Bus speed: %d Mhz \n", buad_div);
  switch (buad_div) {
    case 2:  _buad_div = 120;
              break;
    case 4:  _buad_div = 60;
              break;
    case 8:  _buad_div = 30;
              break;
    case 12: _buad_div = 20;
              break;
    case 20: _buad_div = 12;
              break;
    case 24: _buad_div = 10;
              break;
    case 40: _buad_div = 6;
              break;
    default: _buad_div = 20; // 12Mhz
              break;           
  }
  pinMode(_cs, OUTPUT); // CS
  pinMode(_dc, OUTPUT); // DC
  pinMode(_rst, OUTPUT); // RST
  *(portControlRegister(_cs)) = 0xFF;
  *(portControlRegister(_dc)) = 0xFF;
  *(portControlRegister(_rst)) = 0xFF;
  digitalWriteFast(_rst, HIGH);
  digitalWriteFast(_cs, HIGH);
  digitalWriteFast(_dc, HIGH);

  delay(15);
  digitalWrite(_rst, LOW);
  delay(15);
  digitalWriteFast(_rst, HIGH);
  delay(100);

  FlexIO_Init();

  displayInit();
  /*
  setBitDepth(_bitDepth);

  setTearingEffect(_bTearingOn);
  if (_bTearingOn == true) {
    setTearingScanLine(_tearingScanLine);
  }  
  setFrameRate(_frameRate);
  */
 
  _width  = _TFTWIDTH;
  _height = _TFTHEIGHT;

  
}


FLASHMEM uint8_t ILI948x_t4_mm::setBitDepth(uint8_t bitDepth)  
{
  uint8_t bd;

  switch (bitDepth) {
    case 16:  _bitDepth = 16;
              bd = 0x55;
              break;
    case 18:  _bitDepth = 18;
              bd = 0x66;
              break;
    case 24:  //Unsupported
              return _bitDepth;
              break;
    default:  //Unsupported
              return _bitDepth;
              break;
  }
 
  SglBeatWR_nPrm_8(ILI9488_COLMOD, &bd, 1);

  //Insert small delay here as rapid calls appear to fail
  delay(10);

  return _bitDepth;
}

FLASHMEM uint8_t ILI948x_t4_mm::getBitDepth()
{
  return _bitDepth;
}

FLASHMEM void ILI948x_t4_mm::setFrameRate(uint8_t frRate) 
{
  _frameRate = frRate;

  uint8_t fr28Hz[2] = {0x00, 0x11}; // 28.78fps, 17 clocks
  uint8_t fr30Hz[2] = {0x10, 0x11}; // 30.38fps, 17 clocks
  uint8_t fr60Hz[2] = {0xA0, 0x11}; // 60.76fps, 17 clocks
  uint8_t fr68Hz[2] = {0xB0, 0x11}; // 68.36fps, 17 clocks (ILI9488 default)
  uint8_t fr78Hz[2] = {0xC0, 0x11}; // 78.13fps, 17 clocks
  uint8_t fr91Hz[2] = {0xD0, 0x11}; // 91.15fps, 17 clocks

  uint8_t frData[2];
  //Select parameters for frame rate
  switch (frRate) {
    case 28: memcpy(frData, fr28Hz, sizeof fr28Hz); break;
    case 30: memcpy(frData, fr30Hz, sizeof fr30Hz); break;
    case 60: memcpy(frData, fr60Hz, sizeof fr60Hz); break;
    case 68: memcpy(frData, fr68Hz, sizeof fr68Hz); break;
    case 78: memcpy(frData, fr78Hz, sizeof fr78Hz); break;
    case 91: memcpy(frData, fr91Hz, sizeof fr91Hz); break;
    default: memcpy(frData, fr60Hz, sizeof fr60Hz); _frameRate = 60; break;
  }

  SglBeatWR_nPrm_8(ILI9488_FRMCTR1, frData, 2);
  
}

FLASHMEM uint8_t ILI948x_t4_mm::getFrameRate()
{
  return _frameRate;
}

FLASHMEM void ILI948x_t4_mm::setTearingEffect(bool tearingOn)
{

  _bTearingOn = tearingOn;
  uint8_t mode = 0x00;
  
  CSLow();
  if (_bTearingOn == true) {
    SglBeatWR_nPrm_8(ILI9488_TEON, &mode, 1);        //Tearing effect line on, mode 0 (V-Blanking)
  } else {
    SglBeatWR_nPrm_8(ILI9488_TEOFF,0,0);
  }
  CSHigh();

}

FLASHMEM bool ILI948x_t4_mm::getTearingEffect()
{
  return _bTearingOn;
}

FLASHMEM void ILI948x_t4_mm::setTearingScanLine(uint16_t scanLine)
{
  _tearingScanLine = scanLine;
  
  uint8_t params[2] = {(uint8_t)(_tearingScanLine << 8), (uint8_t)(_tearingScanLine & 0xFF)};
  SglBeatWR_nPrm_8(ILI9488_TESLWR, params, 2);      //Tearing effect write scan line : 0x00 0x00 = line 0 (default), 0x00 0xA0 = line 160, 0x00 0xF0 = line 240

}

FLASHMEM uint16_t ILI948x_t4_mm::getTearingScanLine()
{
  return _tearingScanLine;
}

FLASHMEM void ILI948x_t4_mm::setRotation(uint8_t r) 
{ 
  _rotation = r & 3;

  switch (_rotation) {
    case 0:	
    case 2: _width  = _TFTWIDTH;
            _height = _TFTHEIGHT;
            break;
    case 1: 
    case 3: _width  = _TFTHEIGHT;
            _height = _TFTWIDTH;
            break;
	}

  SglBeatWR_nPrm_8(ILI9488_MADCTL, &MADCTL[_rotation], 1);
}

FLASHMEM void ILI948x_t4_mm::invertDisplay(bool invert) 
{
  SglBeatWR_nPrm_8(invert ? ILI9488_INVON : ILI9488_INVOFF,0,0);
}

FLASHMEM void ILI948x_t4_mm::onCompleteCB(CBF callback)
{
  _callback = callback;
  isCB = true;
}

FASTRUN void ILI948x_t4_mm::setAddrWindow(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) 
{
  uint8_t Command;
  uint8_t CommandValue[4];

  Command = 0x2A;
  CommandValue[0U] = x1 >> 8U;
  CommandValue[1U] = x1 & 0xFF;
  CommandValue[2U] = x2 >> 8U;
  CommandValue[3U] = x2 & 0xFF;
  SglBeatWR_nPrm_8(Command, CommandValue, 4U);

  Command = 0x2B;
  CommandValue[0U] = y1 >> 8U;
  CommandValue[1U] = y1 & 0xFF;
  CommandValue[2U] = y2 >> 8U;
  CommandValue[3U] = y2 & 0xFF;
  SglBeatWR_nPrm_8(Command, CommandValue, 4U);

  //SglBeatWR_nPrm_8(ILI9488_RAMWR); //Set ILI9488 to expect RAM data for pixels, resets column and page regs

  CSHigh();
}

FASTRUN void ILI948x_t4_mm::pushPixels16bit(const uint16_t * pcolors, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
  while(WR_DMATransferDone == false)
  {
    //Wait for any DMA transfers to complete
  }
  uint32_t area = (x2-x1+1)*(y2-y1+1);
  if (!((_lastx1 == x1) && (_lastx2 == x2) && (_lasty1 == y1) && (_lasty2 == y2))) {
  setAddrWindow( x1, y1, x2, y2);
     _lastx1 = x1;  _lastx2 = x2;  _lasty1 = y1;  _lasty2 = y2;
  }
  SglBeatWR_nPrm_16(ILI9488_RAMWR, pcolors, area);
}

FASTRUN void ILI948x_t4_mm::pushPixels16bitDMA(const uint16_t * pcolors, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2){
  while(WR_DMATransferDone == false)
  {
    //Wait for any DMA transfers to complete
  }
  uint32_t area = (x2-x1+1)*(y2-y1+1);
  if (!((_lastx1 == x1) && (_lastx2 == x2) && (_lasty1 == y1) && (_lasty2 == y2))) {
  setAddrWindow(x1, y1, x2, y2);
     _lastx1 = x1;  _lastx2 = x2;  _lasty1 = y1;  _lasty2 = y2;
  }

  MulBeatWR_nPrm_DMA(ILI9488_RAMWR, pcolors, area);
}





///////////////////
//Private functions
///////////////////
FLASHMEM void ILI948x_t4_mm::displayInit() 
{
  #include "ILI948x_t4_mm_defines.h"
}

FASTRUN void ILI948x_t4_mm::CSLow() 
{
  digitalWriteFast(_cs, LOW);       //Select TFT
}

FASTRUN void ILI948x_t4_mm::CSHigh() 
{
  digitalWriteFast(_cs, HIGH);       //Deselect TFT
}

FASTRUN void ILI948x_t4_mm::DCLow() 
{
  digitalWriteFast(_dc, LOW);       //Writing command to TFT
}

FASTRUN void ILI948x_t4_mm::DCHigh() 
{
  digitalWriteFast(_dc, HIGH);       //Writing data to TFT
}

FASTRUN void ILI948x_t4_mm::microSecondDelay()
{
  for (uint32_t i=0; i<99; i++) __asm__("nop\n\t");
}


FASTRUN void ILI948x_t4_mm::FlexIO_Init()
{
  /* Get a FlexIO channel */
    pFlex = FlexIOHandler::flexIOHandler_list[1]; // use FlexIO2
    /* Pointer to the port structure in the FlexIO channel */
    p = &pFlex->port();
    /* Pointer to the hardware structure in the FlexIO channel */
    hw = &pFlex->hardware();
    /* Basic pin setup */
    pinMode(10, OUTPUT); // FlexIO2:0 //10
    pinMode(40, OUTPUT); // FlexIO2:4
    pinMode(41, OUTPUT); // FlexIO2:5
    pinMode(42, OUTPUT); // FlexIO2:6
    pinMode(43, OUTPUT); // FlexIO2:7
    pinMode(44, OUTPUT); // FlexIO2:8
    pinMode(45, OUTPUT); // FlexIO2:9
    pinMode(6, OUTPUT); // FlexIO2:10
    pinMode(9, OUTPUT); // FlexIO2:11

    digitalWriteFast(10,HIGH);

    /* High speed and drive strength configuration */
    *(portControlRegister(0)) = 0xFF; //10 
    *(portControlRegister(40)) = 0xFF;
    *(portControlRegister(41)) = 0xFF;
    *(portControlRegister(42)) = 0xFF;
    *(portControlRegister(43)) = 0xFF;
    *(portControlRegister(44)) = 0xFF;
    *(portControlRegister(45)) = 0xFF;
    *(portControlRegister(6)) = 0xFF;
    *(portControlRegister(9)) = 0xFF;

    /* Set clock */
    pFlex->setClockSettings(3, 1, 0); // (480 MHz source, 1+1, 1+0) >> 480/2/1 >> 240Mhz

    /* Set up pin mux */
    pFlex->setIOPinToFlexMode(10);
    pFlex->setIOPinToFlexMode(40);
    pFlex->setIOPinToFlexMode(41);
    pFlex->setIOPinToFlexMode(42);
    pFlex->setIOPinToFlexMode(43);
    pFlex->setIOPinToFlexMode(44);
    pFlex->setIOPinToFlexMode(45);
    pFlex->setIOPinToFlexMode(6);
    pFlex->setIOPinToFlexMode(9);

    /* Enable the clock */
    hw->clock_gate_register |= hw->clock_gate_mask  ;
    /* Enable the FlexIO with fast access */
    p->CTRL = FLEXIO_CTRL_FLEXEN | FLEXIO_CTRL_FASTACC;
}

FASTRUN void ILI948x_t4_mm::FlexIO_Config_SnglBeat()
{
  
    p->CTRL &= ~FLEXIO_CTRL_FLEXEN;
    p->CTRL |= FLEXIO_CTRL_SWRST;
    p->CTRL &= ~FLEXIO_CTRL_SWRST;

    /* Configure the shifters */
    p->SHIFTCFG[0] = 
       FLEXIO_SHIFTCFG_INSRC*(1)                                               /* Shifter input */
       |FLEXIO_SHIFTCFG_SSTOP(0)                                               /* Shifter stop bit disabled */
       | FLEXIO_SHIFTCFG_SSTART(0)                                             /* Shifter start bit disabled and loading data on enabled */
       | FLEXIO_SHIFTCFG_PWIDTH(7);                                            /* Bus width */
     
    p->SHIFTCTL[0] = 
        FLEXIO_SHIFTCTL_TIMSEL(0)                                              /* Shifter's assigned timer index */
      | FLEXIO_SHIFTCTL_TIMPOL*(0)                                             /* Shift on posedge of shift clock */
      | FLEXIO_SHIFTCTL_PINCFG(3)                                              /* Shifter's pin configured as output */
      | FLEXIO_SHIFTCTL_PINSEL(4)                                              /* Shifter's pin start index */
      | FLEXIO_SHIFTCTL_PINPOL*(0)                                             /* Shifter's pin active high */
      | FLEXIO_SHIFTCTL_SMOD(2);                                               /* Shifter mode as transmit */

    /* Configure the timer for shift clock */
    p->TIMCMP[0] = 
        (((1 * 2) - 1) << 8)                                                   /* TIMCMP[15:8] = number of beats x 2 – 1 */
      | ((_buad_div/2) - 1);                                                    /* TIMCMP[7:0] = baud rate divider / 2 – 1 */
    
    p->TIMCFG[0] = 
        FLEXIO_TIMCFG_TIMOUT(0)                                                /* Timer output logic one when enabled and not affected by reset */
      | FLEXIO_TIMCFG_TIMDEC(0)                                                /* Timer decrement on FlexIO clock, shift clock equals timer output */
      | FLEXIO_TIMCFG_TIMRST(0)                                                /* Timer never reset */
      | FLEXIO_TIMCFG_TIMDIS(2)                                                /* Timer disabled on timer compare */
      | FLEXIO_TIMCFG_TIMENA(2)                                                /* Timer enabled on trigger high */
      | FLEXIO_TIMCFG_TSTOP(0)                                                 /* Timer stop bit disabled */
      | FLEXIO_TIMCFG_TSTART*(0);                                              /* Timer start bit disabled */
    
    p->TIMCTL[0] = 
        FLEXIO_TIMCTL_TRGSEL((((0) << 2) | 1))                                 /* Timer trigger selected as shifter's status flag */
      | FLEXIO_TIMCTL_TRGPOL*(1)                                               /* Timer trigger polarity as active low */
      | FLEXIO_TIMCTL_TRGSRC*(1)                                               /* Timer trigger source as internal */
      | FLEXIO_TIMCTL_PINCFG(3)                                                /* Timer' pin configured as output */
      | FLEXIO_TIMCTL_PINSEL(0)                                                /* Timer' pin index: WR pin */
      | FLEXIO_TIMCTL_PINPOL*(1)                                               /* Timer' pin active low */
      | FLEXIO_TIMCTL_TIMOD(1);                                                /* Timer mode as dual 8-bit counters baud/bit */

  /* 
  Serial.printf("CCM_CDCDR: %x\n", CCM_CDCDR);
  Serial.printf("VERID:%x PARAM:%x CTRL:%x PIN: %x\n", IMXRT_FLEXIO2_S.VERID, IMXRT_FLEXIO2_S.PARAM, IMXRT_FLEXIO2_S.CTRL, IMXRT_FLEXIO2_S.PIN);
  Serial.printf("SHIFTSTAT:%x SHIFTERR=%x TIMSTAT=%x\n", IMXRT_FLEXIO2_S.SHIFTSTAT, IMXRT_FLEXIO2_S.SHIFTERR, IMXRT_FLEXIO2_S.TIMSTAT);
  Serial.printf("SHIFTSIEN:%x SHIFTEIEN=%x TIMIEN=%x\n", IMXRT_FLEXIO2_S.SHIFTSIEN, IMXRT_FLEXIO2_S.SHIFTEIEN, IMXRT_FLEXIO2_S.TIMIEN);
  Serial.printf("SHIFTSDEN:%x SHIFTSTATE=%x\n", IMXRT_FLEXIO2_S.SHIFTSDEN, IMXRT_FLEXIO2_S.SHIFTSTATE);
  Serial.printf("SHIFTCTL:%x %x %x %x\n", IMXRT_FLEXIO2_S.SHIFTCTL[0], IMXRT_FLEXIO2_S.SHIFTCTL[1], IMXRT_FLEXIO2_S.SHIFTCTL[2], IMXRT_FLEXIO2_S.SHIFTCTL[3]);
  Serial.printf("SHIFTCFG:%x %x %x %x\n", IMXRT_FLEXIO2_S.SHIFTCFG[0], IMXRT_FLEXIO2_S.SHIFTCFG[1], IMXRT_FLEXIO2_S.SHIFTCFG[2], IMXRT_FLEXIO2_S.SHIFTCFG[3]);
  Serial.printf("TIMCTL:%x %x %x %x\n", IMXRT_FLEXIO2_S.TIMCTL[0], IMXRT_FLEXIO2_S.TIMCTL[1], IMXRT_FLEXIO2_S.TIMCTL[2], IMXRT_FLEXIO2_S.TIMCTL[3]);
  Serial.printf("TIMCFG:%x %x %x %x\n", IMXRT_FLEXIO2_S.TIMCFG[0], IMXRT_FLEXIO2_S.TIMCFG[1], IMXRT_FLEXIO2_S.TIMCFG[2], IMXRT_FLEXIO2_S.TIMCFG[3]);
  Serial.printf("TIMCMP:%x %x %x %x\n", IMXRT_FLEXIO2_S.TIMCMP[0], IMXRT_FLEXIO2_S.TIMCMP[1], IMXRT_FLEXIO2_S.TIMCMP[2], IMXRT_FLEXIO2_S.TIMCMP[3]);
  Serial.printf("FlexIO bus speed: %d\n", pFlex->computeClockRate());
  */  
    /* Enable FlexIO */
   p->CTRL |= FLEXIO_CTRL_FLEXEN;      

}

FASTRUN void ILI948x_t4_mm::FlexIO_Config_MultiBeat()
{
    uint32_t i;
    uint8_t MulBeatWR_BeatQty = SHIFTNUM * sizeof(uint32_t) / sizeof(uint8_t);                                //Number of beats = number of shifters * beats per shifter
    /* Disable and reset FlexIO */
    p->CTRL &= ~FLEXIO_CTRL_FLEXEN;
    p->CTRL |= FLEXIO_CTRL_SWRST;
    p->CTRL &= ~FLEXIO_CTRL_SWRST;

    for(i=0; i<=SHIFTNUM-1; i++)
    {
        p->SHIFTCFG[i] = 
        FLEXIO_SHIFTCFG_INSRC*(1U)                                                /* Shifter input from next shifter's output */
      | FLEXIO_SHIFTCFG_SSTOP(0U)                                                 /* Shifter stop bit disabled */
      | FLEXIO_SHIFTCFG_SSTART(0U)                                                /* Shifter start bit disabled and loading data on enabled */
      | FLEXIO_SHIFTCFG_PWIDTH(8U-1U);                                            /* 8 bit shift width */
    }

    p->SHIFTCTL[0] = 
    FLEXIO_SHIFTCTL_TIMSEL(0)                                                     /* Shifter's assigned timer index */
      | FLEXIO_SHIFTCTL_TIMPOL*(0U)                                               /* Shift on posedge of shift clock */
      | FLEXIO_SHIFTCTL_PINCFG(3U)                                                /* Shifter's pin configured as output */
      | FLEXIO_SHIFTCTL_PINSEL(4)                                                 /* Shifter's pin start index */
      | FLEXIO_SHIFTCTL_PINPOL*(0U)                                               /* Shifter's pin active high */
      | FLEXIO_SHIFTCTL_SMOD(2U);                                                 /* shifter mode transmit */

    for(i=1; i<=SHIFTNUM-1; i++)
    {
        p->SHIFTCTL[i] = 
        FLEXIO_SHIFTCTL_TIMSEL(0)                                                 /* Shifter's assigned timer index */
      | FLEXIO_SHIFTCTL_TIMPOL*(0U)                                               /* Shift on posedge of shift clock */
      | FLEXIO_SHIFTCTL_PINCFG(0U)                                                /* Shifter's pin configured as output disabled */
      | FLEXIO_SHIFTCTL_PINSEL(4)                                                 /* Shifter's pin start index */
      | FLEXIO_SHIFTCTL_PINPOL*(0U)                                               /* Shifter's pin active high */
      | FLEXIO_SHIFTCTL_SMOD(2U);                                                 /* shifter mode transmit */          
    }

    /* Configure the timer for shift clock */
    p->TIMCMP[0] = 
        ((MulBeatWR_BeatQty * 2U - 1) << 8)                                       /* TIMCMP[15:8] = number of beats x 2 – 1 */
      | (_buad_div/2U - 1U);                                                       /* TIMCMP[7:0] = shift clock divide ratio / 2 - 1 */
      
    p->TIMCFG[0] =   FLEXIO_TIMCFG_TIMOUT(0U)                                     /* Timer output logic one when enabled and not affected by reset */
      | FLEXIO_TIMCFG_TIMDEC(0U)                                                  /* Timer decrement on FlexIO clock, shift clock equals timer output */
      | FLEXIO_TIMCFG_TIMRST(0U)                                                  /* Timer never reset */
      | FLEXIO_TIMCFG_TIMDIS(2U)                                                  /* Timer disabled on timer compare */
      | FLEXIO_TIMCFG_TIMENA(2U)                                                  /* Timer enabled on trigger high */
      | FLEXIO_TIMCFG_TSTOP(0U)                                                   /* Timer stop bit disabled */
      | FLEXIO_TIMCFG_TSTART*(0U);                                                /* Timer start bit disabled */



    p->TIMCTL[0] = 
        FLEXIO_TIMCTL_TRGSEL((0 << 2) | 1U)                                       /* Timer trigger selected as highest shifter's status flag */
      | FLEXIO_TIMCTL_TRGPOL*(1U)                                                 /* Timer trigger polarity as active low */
      | FLEXIO_TIMCTL_TRGSRC*(1U)                                                 /* Timer trigger source as internal */
      | FLEXIO_TIMCTL_PINCFG(3U)                                                  /* Timer' pin configured as output */
      | FLEXIO_TIMCTL_PINSEL(0)                                                   /* Timer' pin index: WR pin */
      | FLEXIO_TIMCTL_PINPOL*(1U)                                                 /* Timer' pin active low */
      | FLEXIO_TIMCTL_TIMOD(1U);                                                  /* Timer mode 8-bit baud counter */

/*
  Serial.printf("CCM_CDCDR: %x\n", CCM_CDCDR);
  Serial.printf("VERID:%x PARAM:%x CTRL:%x PIN: %x\n", IMXRT_FLEXIO2_S.VERID, IMXRT_FLEXIO2_S.PARAM, IMXRT_FLEXIO2_S.CTRL, IMXRT_FLEXIO2_S.PIN);
  Serial.printf("SHIFTSTAT:%x SHIFTERR=%x TIMSTAT=%x\n", IMXRT_FLEXIO2_S.SHIFTSTAT, IMXRT_FLEXIO2_S.SHIFTERR, IMXRT_FLEXIO2_S.TIMSTAT);
  Serial.printf("SHIFTSIEN:%x SHIFTEIEN=%x TIMIEN=%x\n", IMXRT_FLEXIO2_S.SHIFTSIEN, IMXRT_FLEXIO2_S.SHIFTEIEN, IMXRT_FLEXIO2_S.TIMIEN);
  Serial.printf("SHIFTSDEN:%x SHIFTSTATE=%x\n", IMXRT_FLEXIO2_S.SHIFTSDEN, IMXRT_FLEXIO2_S.SHIFTSTATE);
  for(int i=0; i<SHIFTNUM; i++){
    Serial.printf("SHIFTCTL[%d]:%x \n", i, IMXRT_FLEXIO2_S.SHIFTCTL[i]);
    } 

  for(int i=0; i<SHIFTNUM; i++){
    Serial.printf("SHIFTCFG[%d]:%x \n", i, IMXRT_FLEXIO2_S.SHIFTCFG[i]);
    }   
  
  Serial.printf("TIMCTL:%x %x %x %x\n", IMXRT_FLEXIO2_S.TIMCTL[0], IMXRT_FLEXIO2_S.TIMCTL[1], IMXRT_FLEXIO2_S.TIMCTL[2], IMXRT_FLEXIO2_S.TIMCTL[3]);
  Serial.printf("TIMCFG:%x %x %x %x\n", IMXRT_FLEXIO2_S.TIMCFG[0], IMXRT_FLEXIO2_S.TIMCFG[1], IMXRT_FLEXIO2_S.TIMCFG[2], IMXRT_FLEXIO2_S.TIMCFG[3]);
  Serial.printf("TIMCMP:%x %x %x %x\n", IMXRT_FLEXIO2_S.TIMCMP[0], IMXRT_FLEXIO2_S.TIMCMP[1], IMXRT_FLEXIO2_S.TIMCMP[2], IMXRT_FLEXIO2_S.TIMCMP[3]);
*/
    /* Enable FlexIO */
   p->CTRL |= FLEXIO_CTRL_FLEXEN;
   p->SHIFTSDEN |= 1U << (SHIFTER_DMA_REQUEST); // enable DMA trigger when shifter status flag is set on shifter SHIFTER_DMA_REQUEST
}

FASTRUN void ILI948x_t4_mm::SglBeatWR_nPrm_8(uint32_t const cmd, const uint8_t *value = NULL, uint32_t const length = 0)
{
  while(WR_DMATransferDone == false)
  {
    //Wait for any DMA transfers to complete
  }

    FlexIO_Config_SnglBeat();
     uint32_t i;
    /* Assert CS, RS pins */
    
    //delay(1);
    CSLow();
    DCLow();

    /* Write command index */
    p->SHIFTBUF[0] = cmd;

    /*Wait for transfer to be completed */
    while(0 == (p->SHIFTSTAT & (1 << 0)))
    {
    }
    while(0 == (p->TIMSTAT & (1 << 0)))
            {  
            }

    /* De-assert RS pin */
    
    microSecondDelay();
    DCHigh();
    microSecondDelay();

    if(length)
    {
        for(i = 0; i < length; i++)
        {    
            p->SHIFTBUF[0] = *value++;
            while(0 == (p->SHIFTSTAT & (1 << 0)))
            {  
            }
        }
        while(0 == (p->TIMSTAT & (1 << 0)))
            {  
            }
    }
    microSecondDelay();
    CSHigh();
    /* De-assert CS pin */
}

FASTRUN void ILI948x_t4_mm::SglBeatWR_nPrm_16(uint32_t const cmd, const uint16_t *value, uint32_t const length)
{
 while(WR_DMATransferDone == false)
  {
    //Wait for any DMA transfers to complete
  }
    FlexIO_Config_SnglBeat();
    uint16_t buf;
    /* Assert CS, RS pins */
    CSLow();
    DCLow();
    //microSecondDelay();
    
    /* Write command index */
    p->SHIFTBUF[0] = cmd;

    /*Wait for transfer to be completed */
    while(0 == (p->TIMSTAT & (1 << 0)))
            {  
            }
    microSecondDelay();
    /* De-assert RS pin */
    DCHigh();
    microSecondDelay();

    if(length)
    {
      for(uint32_t i=0; i<length-1U; i++)
        {
          buf = *value++;
            while(0 == (p->SHIFTSTAT & (1U << 0)))
            {
            }
            p->SHIFTBUF[0] = buf >> 8;

            while(0 == (p->SHIFTSTAT & (1U << 0)))
            {
            }
            p->SHIFTBUF[0] = buf & 0xFF;
        }
        buf = *value++;
        /* Write the last byte */
        while(0 == (p->SHIFTSTAT & (1U << 0)))
            {
            }
        p->SHIFTBUF[0] = buf >> 8;

        while(0 == (p->SHIFTSTAT & (1U << 0)))
        {
        }
        p->TIMSTAT |= (1U << 0);

        p->SHIFTBUF[0] = buf & 0xFF;

        /*Wait for transfer to be completed */
        while(0 == (p->TIMSTAT |= (1U << 0)))
        {
        }
    }
    microSecondDelay();
    CSHigh();
}


bool WR_DMATransferDone = true;
uint32_t MulBeatCountRemain;
//uint16_t *MulBeatDataRemain;
uint32_t TotalSize; 
ILI948x_t4_mm * ILI948x_t4_mm::dmaCallback = nullptr;
DMAChannel ILI948x_t4_mm::flexDma;

FASTRUN void ILI948x_t4_mm::MulBeatWR_nPrm_DMA(uint32_t const cmd,  const void *value, uint32_t const length) 
{
  while(WR_DMATransferDone == false)
  {
    //Wait for any DMA transfers to complete
  }
    uint32_t BeatsPerMinLoop = SHIFTNUM * sizeof(uint32_t) / sizeof(uint8_t);      // Number of shifters * number of 8 bit values per shifter
    uint32_t majorLoopCount, minorLoopBytes;
    uint32_t destinationModulo = 31-(__builtin_clz(SHIFTNUM*sizeof(uint32_t))); // defines address range for circular DMA destination buffer 

    FlexIO_Config_SnglBeat();
    CSLow();
    DCLow();

    /* Write command index */
    p->SHIFTBUF[0] = cmd;

    /*Wait for transfer to be completed */

    while(0 == (p->TIMSTAT & (1 << 0)))
            {  
            }
    microSecondDelay();
    /* De-assert RS pin */
    DCHigh();
    microSecondDelay();


  if (length < 8){
    //Serial.println ("In DMA but to Short to multibeat");
    const uint16_t * newValue = (uint16_t*)value;
    uint16_t buf;
    for(uint32_t i=0; i<length; i++)
      {
        buf = *newValue++;
          while(0 == (p->SHIFTSTAT & (1U << 0)))
          {
          }
          p->SHIFTBUF[0] = buf >> 8;


          while(0 == (p->SHIFTSTAT & (1U << 0)))
          {
          }
          p->SHIFTBUF[0] = buf & 0xFF;
          
      }        
      //Wait for transfer to be completed 
      while(0 == (p->TIMSTAT & (1U << 0)))
      {
      }

    microSecondDelay();
    CSHigh();

  }

  else{
    //memcpy(framebuff, value, length); 
    //arm_dcache_flush((void*)framebuff, sizeof(framebuff)); // always flush cache after writing to DMAMEM variable that will be accessed by DMA
    
    FlexIO_Config_MultiBeat();
    
    MulBeatCountRemain = length % BeatsPerMinLoop;
    MulBeatDataRemain = (uint16_t*)value + ((length - MulBeatCountRemain)); // pointer to the next unused byte (overflow if MulBeatCountRemain = 0)
    TotalSize = (length - MulBeatCountRemain)*2;               /* in bytes */
    minorLoopBytes = SHIFTNUM * sizeof(uint32_t);
    majorLoopCount = TotalSize/minorLoopBytes;
    //Serial.printf("Length(16bit): %d, Count remain(16bit): %d, Data remain: %d, TotalSize(8bit): %d, majorLoopCount: %d \n",length, MulBeatCountRemain, MulBeatDataRemain, TotalSize, majorLoopCount );

    /* Configure FlexIO with multi-beat write configuration */
    flexDma.begin();

    /* Setup DMA transfer with on-the-fly swapping of MSB and LSB in 16-bit data:
     *  Within each minor loop, read 16-bit values from buf in reverse order, then write 32bit values to SHIFTBUFBYS[i] in reverse order.
     *  Result is that every pair of bytes are swapped, while half-words are unswapped.
     *  After each minor loop, advance source address using minor loop offset. */
    int destinationAddressOffset, destinationAddressLastOffset, sourceAddressOffset, sourceAddressLastOffset, minorLoopOffset;
    volatile void *destinationAddress, *sourceAddress;

    DMA_CR |= DMA_CR_EMLM; // enable minor loop mapping

    sourceAddress = (uint16_t*)value + minorLoopBytes/sizeof(uint16_t) - 1; // last 16bit address within current minor loop
    sourceAddressOffset = -sizeof(uint16_t); // read values in reverse order
    minorLoopOffset = 2*minorLoopBytes; // source address offset at end of minor loop to advance to next minor loop
    sourceAddressLastOffset = minorLoopOffset - TotalSize; // source address offset at completion to reset to beginning
    destinationAddress = (uint32_t*)&p->SHIFTBUFBYS[SHIFTNUM-1]; // last 32bit shifter address (with reverse byte order)
    destinationAddressOffset = -sizeof(uint32_t); // write words in reverse order
    destinationAddressLastOffset = 0;

    flexDma.TCD->SADDR = sourceAddress;
    flexDma.TCD->SOFF = sourceAddressOffset;
    flexDma.TCD->SLAST = sourceAddressLastOffset;
    flexDma.TCD->DADDR = destinationAddress;
    flexDma.TCD->DOFF = destinationAddressOffset;
    flexDma.TCD->DLASTSGA = destinationAddressLastOffset;
    flexDma.TCD->ATTR =
        DMA_TCD_ATTR_SMOD(0U)
      | DMA_TCD_ATTR_SSIZE(DMA_TCD_ATTR_SIZE_16BIT) // 16bit reads
      | DMA_TCD_ATTR_DMOD(destinationModulo)
      | DMA_TCD_ATTR_DSIZE(DMA_TCD_ATTR_SIZE_32BIT); // 32bit writes
    flexDma.TCD->NBYTES_MLOFFYES = 
        DMA_TCD_NBYTES_SMLOE
      | DMA_TCD_NBYTES_MLOFFYES_MLOFF(minorLoopOffset)
      | DMA_TCD_NBYTES_MLOFFYES_NBYTES(minorLoopBytes);
    flexDma.TCD->CITER = majorLoopCount; // Current major iteration count
    flexDma.TCD->BITER = majorLoopCount; // Starting major iteration count

    flexDma.triggerAtHardwareEvent(hw->shifters_dma_channel[SHIFTER_DMA_REQUEST]);
    flexDma.disableOnCompletion();
    flexDma.interruptAtCompletion();
    flexDma.clearComplete();
    
    //Serial.println("Dma setup done");

    /* Start data transfer by using DMA */
    WR_DMATransferDone = false;
    flexDma.attachInterrupt(dmaISR);
    flexDma.enable();
    //Serial.println("Starting transfer");
    dmaCallback = this;
   }
}

FASTRUN void ILI948x_t4_mm::_onCompleteCB()
{
if (_callback){
      _callback();
    }
    return;
}


FASTRUN void ILI948x_t4_mm::dmaISR()
{
  flexDma.clearInterrupt();
  asm volatile ("dsb"); // prevent interrupt from re-entering
  dmaCallback->flexDma_Callback();
}


FASTRUN void ILI948x_t4_mm::flexDma_Callback()
{
    //Serial.printf("DMA callback start triggred \n");
    
    /* the interrupt is called when the final DMA transfer completes writing to the shifter buffers, which would generally happen while
    data is still in the process of being shifted out from the second-to-last major iteration. In this state, all the status flags are cleared.
    when the second-to-last major iteration is fully shifted out, the final data is transfered from the buffers into the shifters which sets all the status flags.
    if you have only one major iteration, the status flags will be immediately set before the interrupt is called, so the while loop will be skipped. */
    while(0 == (p->SHIFTSTAT & (1U << (SHIFTNUM-1))))
    {
    }
    
    /* Wait the last multi-beat transfer to be completed. Clear the timer flag
    before the completing of the last beat. The last beat may has been completed
    at this point, then code would be dead in the while() below. So mask the
    while() statement and use the software delay .*/
    p->TIMSTAT |= (1U << 0U);

    /* Wait timer flag to be set to ensure the completing of the last beat. */
    while(0 == (p->TIMSTAT & (1U << 0U)))
    {
    }
    
    if(MulBeatCountRemain)
    {
      //Serial.printf("MulBeatCountRemain in DMA callback: %d, MulBeatDataRemain %x \n", MulBeatCountRemain,MulBeatDataRemain);
      uint16_t value;
        /* Configure FlexIO with 1-beat write configuration */
        FlexIO_Config_SnglBeat();
        

        //Serial.printf("Starting single beat completion: %d \n", MulBeatCountRemain);

        /* Use polling method for data transfer */
        for(uint32_t i=0; i<(MulBeatCountRemain); i++)
        {
          value = *MulBeatDataRemain++;
            while(0 == (p->SHIFTSTAT & (1U << 0)))
            {
            }
            p->SHIFTBUF[0] = value >> 8;

            while(0 == (p->SHIFTSTAT & (1U << 0)))
            {
            }
            p->SHIFTBUF[0] = value & 0xFF;
        }
        p->TIMSTAT |= (1U << 0);
        /*
        value = *MulBeatDataRemain++;
        //Write the last byte 
        
        while(0 == (p->SHIFTSTAT & (1U << 0)))
            {
            }
        p->SHIFTBUF[0] = value >> 8;

        while(0 == (p->SHIFTSTAT & (1U << 0)))
        {
        }
        p->TIMSTAT |= (1U << 0);

        p->SHIFTBUF[0] = value & 0xFF;
        */
        /*Wait for transfer to be completed */
        while(0 == (p->TIMSTAT |= (1U << 0)))
        {
        }
        //Serial.println("Finished single beat completion");
    }

    microSecondDelay();
    CSHigh();
    /* the for loop is probably not sufficient to complete the transfer. Shifting out all 32 bytes takes (32 beats)/(6 MHz) = 5.333 microseconds which is over 3000 CPU cycles.
    If you really need to wait in this callback until all the data has been shifted out, the while loop is probably the correct solution and I don't think it risks an infinite loop.
    however, it seems like a waste of time to wait here, since the process otherwise completes in the background and the shifter buffers are ready to receive new data while the transfer completes.
    I think in most applications you could continue without waiting. You can start a new DMA transfer as soon as the first one completes (no need to wait for FlexIO to finish shifting). */

    WR_DMATransferDone = true;
//    flexDma.disable(); // not necessary because flexDma is already configured to disable on completion
    if(isCB){
      //Serial.printf("custom callback triggred \n");
    _onCompleteCB();
    
    }
    //Serial.printf("DMA callback end triggred \n");
}


void ILI948x_t4_mm::DMAerror(){
  if(flexDma.error()){
    Serial.print("DMA error: ");
    Serial.println(DMA_ES, HEX);
  } 
}