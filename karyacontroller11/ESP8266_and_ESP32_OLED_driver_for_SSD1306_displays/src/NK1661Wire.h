
/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 by ThingPulse, Daniel Eichhorn
 * Copyright (c) 2018 by Fabrice Weinberg
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * ThingPulse invests considerable time and money to develop these open source libraries.
 * Please support us by buying our products (and not the clones) from
 * https://thingpulse.com
 *
 */

#define LCDTYPE 1 // 1 = invert
#ifndef NK1661Wire_h
#define NK1661Wire_h

#include "espSoftSPIx.h"
   
const uchar Contrast_level = 140;

#define SPFD54124B_SEND_CMD 0
#define SPFD54124B_SEND_DATA 0x100

#define SPFD54124B_CMD_NOP 0x00
#define SPFD54124B_CMD_RST 0x01
#define SPFD54124B_CMD_SLPOUT 0x11
#define SPFD54124B_CMD_NORON 0x13

#define SPFD54124B_CMD_INVOFF 0x20
#define SPFD54124B_CMD_INVON 0x21
#define SPFD54124B_CMD_DISPON 0x29
#define SPFD54124B_CMD_CASET 0x2A
#define SPFD54124B_CMD_RASET 0x2B
#define SPFD54124B_CMD_RAMWR 0x2C
#define SPFD54124B_CMD_RGBSET 0x2D

#define SPFD54124B_CMD_MADCTR 0x36
#define SPFD54124B_CMD_VSCSAD 0x37
#define SPFD54124B_CMD_COLMOD 0x3A

#define SPFD54124B_CMD_COLMOD_MCU12bit 3 // MCU interface 12bit
#define SPFD54124B_CMD_COLMOD_MCU16bit 5 // MCU interface 16bit
#define SPFD54124B_CMD_COLMOD_MCU18bit 6 // MCU interface 18bit
#define SPFD54124B_CMD_COLMOD_RGB16bit 50 // RGB interface 16bit
#define SPFD54124B_CMD_COLMOD_RGB18bit 60 // RGB interface 18bit

#define SPFD54124B_CMD_MADCTR_MY (1 << 7) // Row Address Order
#define SPFD54124B_CMD_MADCTR_MX (1 << 6) // Column Address Order
#define SPFD54124B_CMD_MADCTR_MV (1 << 5) // Row/Column Exchange
#define SPFD54124B_CMD_MADCTR_ML (1 << 4) // Vertical Refresh Order
#define SPFD54124B_CMD_MADCTR_RGB (1 << 3) // RGB-BGR ORDER
#define SPFD54124B_CMD_SETPWCTR1               (0xB1)
#define SPFD54124B_CMD_SETPWCTR2               (0xB2)
#define SPFD54124B_CMD_SETPWCTR3               (0xB3)
#define SPFD54124B_CMD_SETPWCTR4               (0xB4)
#define SPFD54124B_CMD_SETPWCTR5               (0xB5)

#define SCR_WD 80
#define SCR_HT 64
#define SCR_HT8 8

#define ALIGN_LEFT 0
#define ALIGN_RIGHT -1
#define ALIGN_CENTER -2

#define SET 1
#define CLR 0
#define XOR 2


//#define FLIPMODE

//#undef USERGB12

#ifdef USERGB12
#define RGB12(r,g,b) ((r>>1) + ((g>>2)<<4) + ((b>>1)<<8))
#define RGB16 RGB12
#else
#define RGB16(r,g,b) ((r) + (g<<5) + (b<<11))
#endif

//--------------------------------------

class NK1661Wire : public OLEDDisplay {
private:
    uint8_t _sda,_psda;
    uint8_t _scl,_pscl,_pcs,bctr;
    uint8_t _cs,_rs,hpos;
    uint16_t col,hcol,bg,hbg;
    bool justreset;

public:
    NK1661Wire(uint8_t sda, uint8_t scl, uint8_t cs,uint8_t rs,uint8_t tpos=21,OLEDDISPLAY_GEOMETRY g = GEOMETRY_162_132)
    {
        if (rs==255)rs=scl;
        if (cs==255)cs=scl;
        this->_sda = sda;
        this->_scl = scl;
        this->_cs = cs;
        this->_rs = rs;
        this->_psda = 1<<sda;
        this->_pscl = 1<<scl;
        this->_pcs = 1<<cs;
        //pinMode(_scl, OUTPUT);
        //CS_OFF
        setGeometry(g);
        
        col=RGB16(31,63,31);
        bg=RGB16(0,0,0);
        hcol=RGB16(5,63,5);
        hbg=RGB16(0,0,28);
        hpos=tpos;
    }

    bool connect()
    {
        //we actualy use SPI

        return true;
    }

    void setWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
    {
        uint8_t t0, t1;

        writeCommand(SPFD54124B_CMD_CASET); // Column addr set
        //writeData(x0 >>8); // X start
        writeData16(x0); // X start
        //writeData(x1 >>8); // X end
        writeData16(x1); // X end

        writeCommand(SPFD54124B_CMD_RASET); // Page addr set
        //writeData(y0>>8);
        writeData16(y0);
        //writeData(y1>>8);
        writeData16(y1);

        writeCommand(SPFD54124B_CMD_RAMWR);
    }
    int display(void)
    {
		//return 1;
#ifdef OLEDDISPLAY_DOUBLE_BUFFER
        long m = micros();
        pinMode(_scl, OUTPUT);
        pinMode(_cs, OUTPUT);
        pinMode(_sda, OUTPUT);
        
        

        

        uint8_t x, y,npx;
        extern int motionloop();
        // Calculate the Y bounding box of changes
        // and copy buffer[pos] to buffer_back[pos];
        for (y = 0; y < (displayHeight / 8); y++) {
            uint8_t minBoundX = UINT8_MAX;
            npx=0;
            for (x = 0; x <= displayWidth; x++) {
                uint16_t pos = x + y * displayWidth;
                if ((x<displayWidth) && (justreset || (buffer[pos] != buffer_back[pos]))) {
                    npx++;
                    buffer_back[pos] = buffer[pos];
                    if (minBoundX==UINT8_MAX)minBoundX = x;
                } else {
                    // draw a chunk of display
                    if ((minBoundX!=UINT8_MAX) && (npx>(x<displayWidth?10:0))) { // minimum 10pixel at once

                        uint8_t maxBoundX=_min(x+1,displayWidth);
                        uint8_t* pdat = &buffer[minBoundX + y * displayWidth];
                        CS_ON
#if FLIPMODE
                        setWindow((y) * 8, minBoundX+1,(y+1) * 8 -1, maxBoundX);
#else
                        //setWindow(130 - (y + 1) * 8, minBoundX+1,130 - y * 8 -1, maxBoundX);
                        setWindow(132 - (y+1) * 8, minBoundX,131 - y * 8 , maxBoundX-1);
#endif
                        int nn=0;
                        for (uint8_t dx = minBoundX; dx < maxBoundX; dx++) {
                            // send 8pixel /byte
                            uint8_t dat = *pdat;
                            pdat++;
                            int hy=(y+1)*8;
                            int16_t ccol=col;
                            uint16_t cbg=bg;
                            CS_ON
                            if (hy--<=hpos){ccol=hcol;cbg=hbg;}
                            for (uint8_t p = 0x80; p; p>>=1) {
                                
                                #ifdef RGB12
                                    writeData12(
                                #else
                                    writeData16(
                                #endif
                                    (dat & p ? ccol:cbg));
                                
                                nn++;
                                //if ((nn>300) && (bctr==7)){
                                    //CS_OFF
                                    //nn=0;
                                    //motionloop();
                                    //CS_ON
                                //}
                            }

                        }
                        #ifdef RGB12
                        for (bctr++;bctr<8;bctr++){
                            SCLK_1;
                            SCLK_0;
                        }
                        #endif
                        // reset counter find other chunk
                        minBoundX = UINT8_MAX;
                        npx=0;
                        //yield();
                        CS_OFF
                        motionloop();                       
                    }
                    
                }

            }
        }

    justreset=false;

        return 0;//micros()-m;
#else

#endif
    }
    // clear everything
    void setLCDColor(uint16_t c1,uint16_t c2,uint16_t c3=0,uint16_t c4=0){
        col=c1;
        hcol=c2;
        bg=c3;
        hbg=c4;
        Reset();
    }
    void fillScreen(uint16_t c)
    {
        //return;
        uint8_t x, y, hi = c >> 8, lo = c;

        CS_ON
        setWindow(0, 0, 131, 161);


        for (y = 132; y > 0; y--) {
            for (x = 162; x > 0; x--) {
                writeData(hi);
                writeData(lo);
                //lo++;
            }
            //hi++;
        }
        CS_OFF
    }

    int getBufferOffset(void)
    {
        return 0;
    }
    bool init()
    {
        if (!allocateBuffer()) {
            return false;
        }

        Initial();
        //clear();
        memset(buffer_back, 0, displayBufferSize);
        memset(buffer, 0, displayBufferSize);
		fillScreen(0);
        return true;
    }
    void writeany(uint16_t dat)
    {
        for (uint16_t i = 0x100; i ; i>>=1) {
            SDAe((dat & i));
        }
        return;
    }
    void writeCommand(unsigned char dat)
    {
        ISCMD;
        for (uint8_t i = 0x80; i ; i>>=1) {
            SDAe((dat & i));
        }
        bctr=7;
        return;
    }
    void writeData(uint16_t dat)
    {
        ISDATA;
        for (uint8_t i = 1<<7; i; i>>=1) {
            SDAe((dat & i));
        }

        return;
    }
    void writeData12(uint16_t dat)
    {        
        for (uint16_t i = 1<<11; i; i>>=1) {
            if (++bctr==8){
                ISDATA;
                bctr=0;
            }
            SDAe((dat & i));
        }
        return;
    }
    void writeData16(uint16_t dat)
    {        
        for (uint16_t i = 1 << 15; i; i>>=1) {
            if (++bctr==8){
                ISDATA;
                bctr=0;
            }
            SDAe((dat & i));
        }
        return;
    }
    void setContrast(uint8_t mod, bool rev = false)
    {
    }



    void Initial(void)
    {
        Reset();
        
    }
    void Reset(void){

// Idea swiped from 1.8" TFT code: rather than a bazillion writeCommand()
// and writeData() calls, screen initialization commands and arguments are
// organized in this table in PROGMEM.  It may look bulky, but that's
// mostly the formatting -- storage-wise this is considerably more compact
// than the equiv code.  Command sequence is from TFT datasheet.
#define DELAY 0x80
const uint16_t _lcd_init_list[] = {

/*
#ifdef RGB12    
    SPFD54124B_CMD_COLMOD, SPFD54124B_SEND_DATA | SPFD54124B_CMD_COLMOD_MCU12bit,
#else
    SPFD54124B_CMD_COLMOD, SPFD54124B_SEND_DATA | SPFD54124B_CMD_COLMOD_MCU16bit,
#endif
    SPFD54124B_CMD_MADCTR,SPFD54124B_SEND_DATA | SPFD54124B_CMD_MADCTR_ML,
#if LCDTYPE==1    
    SPFD54124B_CMD_INVON,
#endif
#if LCDTYPE==0    
    SPFD54124B_CMD_INVOFF,
#endif
	SPFD54124B_CMD_DISPON,
    SPFD54124B_CMD_NORON,
*/

	SPFD54124B_CMD_SLPOUT,
//    SPFD54124B_CMD_MADCTR,SPFD54124B_SEND_DATA | SPFD54124B_CMD_MADCTR_ML,
#ifdef RGB12    
    SPFD54124B_CMD_COLMOD, SPFD54124B_SEND_DATA | SPFD54124B_CMD_COLMOD_MCU12bit,
#else
    SPFD54124B_CMD_COLMOD, SPFD54124B_SEND_DATA | SPFD54124B_CMD_COLMOD_MCU16bit,
#endif
	
#if LCDTYPE==0    
    SPFD54124B_CMD_INVON,
#else   
    SPFD54124B_CMD_INVOFF,
#endif
    SPFD54124B_CMD_DISPON
	//SPFD54124B_CMD_NORON
};
        
        pinMode(_sda, OUTPUT);
        pinMode(_scl, OUTPUT);
        pinMode(_cs, OUTPUT);
        pinMode(_rs, OUTPUT);

        int dl=0;        
        if (_rs != _scl){
            digitalWrite(_rs,LOW); delay(5);
            digitalWrite(_rs,HIGH); delay(5);
        } else {
            digitalWrite(_rs,HIGH); delay(50);
            digitalWrite(_rs,LOW); delay(150);
        } 
        if (_cs == _scl){
            dl=50;
            digitalWrite(_cs,HIGH);
            delay(dl);
            digitalWrite(_cs,LOW);
            delay(dl);
        } else {
            CS_OFF
            delay(1);
            CS_ON
        }
        
        uint8_t size = 5;

        /*
        writeany(SPFD54124B_CMD_SLPOUT);
        delay(10);
        writeany(0x38);

    
        writeany(0xc0);                                 //power control 1      (PWCTR1)     
        writeany(SPFD54124B_SEND_DATA | 29);            //default value  LCM=0 set t)e GVDD voltage=3.3     
        writeany(SPFD54124B_SEND_DATA | 5);            //default value  LCM=0 set t)e GVDD voltage=3.3      
       
        writeany(0xc5);   
        writeany(SPFD54124B_SEND_DATA | 32);            //VCOM) voltage set 3.3  AGO IS C8H   
        

        writeany(0xc6);         
        writeany(SPFD54124B_SEND_DATA | 0);            //VCOMAC voltage set 4V // AGO IS 1FH   
        //*/
        
        const uint16_t* list = &_lcd_init_list[0];
        size = sizeof(_lcd_init_list) / sizeof(_lcd_init_list[0]);
        while (size--){
            writeany(*list++);
            //delay(1);
        }

        //writeany();
        //fillScreen(1234);

      //*/

      
        justreset=true;        
        CS_OFF
    }
};

#endif

