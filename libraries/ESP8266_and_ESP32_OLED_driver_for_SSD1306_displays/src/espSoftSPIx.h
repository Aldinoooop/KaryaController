#include "OLEDDisplay.h"

#define uint unsigned int
#define uchar unsigned char


#define SDA this->_sda //serial data input
#define SDA2 this->_sda2 //serial data input
#define SCLK this->_scl //serial clock input
#define FCS this->_pcs //serial clock input
#define FSDA this->_psda //serial data input
#define FSDA2 this->_psda2 //serial data input
#define FSCLK this->_pscl //serial clock input

#define NOP __asm__ __volatile__("nop");

#define PIN_ON(pin) GPOS = (1 << pin)
#define PIN_OFF(pin) GPOC = (1 << pin)

#define SCLK_1 GPOS = FSCLK
#define SCLK_0 GPOC = FSCLK
#define SDAe(n)      \
    if (n) GPOS = FSDA; \
    else  GPOC = FSDA;  \
    SCLK_1;SCLK_0;

#define ISDATA  {GPOS = FSDA; SCLK_1;SCLK_0;}
#define ISCMD   {GPOC = FSDA; SCLK_1;SCLK_0;}
#define ISDATA2  {GPOS = FSDA2;}
#define ISCMD2   {GPOC = FSDA2;} 
//#define ISDATA2  {digitalWrite(SDA2,HIGH);}
//#define ISCMD2   {digitalWrite(SDA2,LOW);} 
#define CS_ON if (_cs!=_scl)GPOC=FCS;
#define CS_OFF {GPOS = FSDA;if (_cs!=_scl)GPOS=FCS;}
//#define CS_ON if (_cs!=_scl)digitalWrite(_cs,LOW);
//#define CS_OFF if (_cs!=_scl)digitalWrite(_cs,HIGH);
//#define CS_ON
//#define CS_OFF

