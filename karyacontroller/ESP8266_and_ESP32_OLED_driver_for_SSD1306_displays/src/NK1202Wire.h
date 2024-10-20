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

#ifndef NK1202Wire_h
#define NK1202Wire_h

#include "espSoftSPIx.h"

const uchar Contrast_level = 140;

// HX1230 Commands
#define HX1230_POWER_ON 0x2F // internal power supply on
#define HX1230_POWER_OFF 0x28 // internal power supply off
#define HX1230_CONTRAST 0x80 // 0x80 + (0..31)
#define HX1230_SEG_NORMAL 0xA0 // SEG remap normal
#define HX1230_SEG_REMAP 0xA1 // SEG remap reverse (flip horizontal)
#define HX1230_DISPLAY_NORMAL 0xA4 // display ram contents
#define HX1230_DISPLAY_TEST 0xA5 // all pixels on
#define HX1230_INVERT_OFF 0xA6 // not inverted
#define HX1230_INVERT_ON 0xA7 // inverted
#define HX1230_DISPLAY_ON 0XAF // display on
#define HX1230_DISPLAY_OFF 0XAE // display off
#define HX1230_SCAN_START_LINE 0x40 // scrolling 0x40 + (0..63)
#define HX1230_COM_NORMAL 0xC0 // COM remap normal
#define HX1230_COM_REMAP 0xC8 // COM remap reverse (flip vertical)
#define HX1230_SW_RESET 0xE2 // connect RST pin to GND and rely on software reset
#define HX1230_COM_VOP 0xE1 // connect RST pin to GND and rely on software reset

#define HX1230_68_LINE 0xD0 // no operation
#define HX1230_NOP 0xE3 // no operation
#define HX1230_COL_ADDR_H 0x10 // x pos (0..95) 4 MSB
#define HX1230_COL_ADDR_L 0x00 // x pos (0..95) 4 LSB
#define HX1230_PAGE_ADDR 0xB0 // y pos, 8.5 rows (0..8)

#define SCR_WD 96
#define SCR_HT 68
#define SCR_HT8 9 // (SCR_HT+7)/8

#define ALIGN_LEFT 0
#define ALIGN_RIGHT -1
#define ALIGN_CENTER -2

#define SET 1
#define CLR 0
#define XOR 2


#define sendCmd Write_Instruction


const uint8_t initData[] PROGMEM = {
    
    
    HX1230_DISPLAY_NORMAL,
    HX1230_POWER_ON,
    HX1230_DISPLAY_ON,
    

};
//--------------------------------------

class NK1202Wire : public OLEDDisplay {
private:
    uint8_t _sda,_psda;
    uint8_t _scl,_pscl, _cs;
    bool justreset;

public:
    NK1202Wire(uint8_t sda, uint8_t scl, uint8_t cs=-1,OLEDDISPLAY_GEOMETRY g = GEOMETRY_96_68)
    {
        setGeometry(g);

        this->_sda = sda;
        this->_scl = scl;
        if (cs>0)this->_cs=cs;else this->_cs==scl;
        this->_psda = 1<<sda;
        this->_pscl = 1<<scl;
        
        pinMode(_scl, OUTPUT);
        pinMode(_sda, OUTPUT);
        pinMode(_cs, OUTPUT);

    }

    bool connect()
    {
        //we actualy use SPI

        return true;
    }

    int display(void)
    {

#ifdef OLEDDISPLAY_DOUBLE_BUFFER
        long m = micros();

        pinMode(_sda, OUTPUT);
        CS_ON

        uint8_t x, y,npx;
        extern int motionloop();
        // Calculate the Y bounding box of changes
        // and copy buffer[pos] to buffer_back[pos];
        for (y = 0; y < 9; y++) {
            uint8_t minBoundX = UINT8_MAX;
            npx=0;
            for (x = 0; x <= displayWidth; x++) {
                uint16_t pos = x + y * displayWidth;
                if ((x<displayWidth) && (justreset || (buffer[pos] != buffer_back[pos]))) {
                    if (minBoundX==UINT8_MAX)minBoundX =x;
                    buffer_back[pos] = buffer[pos];
                    npx++;
                } else {
                    // draw a chunk of display
                    if ((minBoundX!=UINT8_MAX) && (npx>(x<displayWidth?10:0))) { // minimum 10pixel at once

                        
                        uint8_t maxBoundX=_min(x+1,displayWidth);
                        sendCmd(HX1230_PAGE_ADDR | y);
                        sendCmd(HX1230_COL_ADDR_H | (minBoundX >> 4));
                        sendCmd(HX1230_COL_ADDR_L | (minBoundX & 0xf));
                        uint8_t* pdat = &buffer[minBoundX + y * displayWidth];
                        for (uint8_t dx = minBoundX; dx < maxBoundX; dx++) {

                                uint8_t dat = *pdat;
                                //if (y==8)dat=0xff;
                                pdat++;
                                ISDATA;
                                SDAe(dat&(1<<7));
                                SDAe(dat&(1<<6));
                                SDAe(dat&(1<<5));
                                SDAe(dat&(1<<4));
                                SDAe(dat&(1<<3));
                                SDAe(dat&(1<<2));
                                SDAe(dat&(1<<1));
                                SDAe(dat&(1<<0));
                        }

                        // reset counter find other chunk
                        minBoundX = UINT8_MAX;
                        npx=0;
                        

                    }

                }
                
            }
            yield();
            motionloop();
        }
    CS_OFF
    justreset=false;
    return micros()-m;
#else

#endif
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
        clear();
        memset(buffer_back, 1, displayBufferSize);

        return true;
    }
    void Write_Instruction(unsigned char dat)
    {
        unsigned char i;

        ISCMD;
        for (i = 1 <<7; i; i>>=1) {
            SDAe((dat & i));
        }

        return;
    }

    void setContrast(uint8_t mod, bool rev = false)
    {
        CS_ON

        //Write_Instruction(rev ? HX1230_INVERT_ON : HX1230_INVERT_OFF);
        CS_OFF
        //Write_Instruction(HX1230_CONTRAST + (mod >> 3));
    }

    inline void sendCommand(uint8_t command) __attribute__((always_inline))
    {
    }

    void Initial(void)
    {


        Reset();
        
    }
    void Reset(void){
        pinMode(_sda, OUTPUT);
        digitalWrite(_cs,HIGH);
        delay(50);
        digitalWrite(_cs,LOW);
        delay(50);


        sendCmd(HX1230_SW_RESET);
        delay(30);
        for (int i = 0; i < sizeof(initData); i++)
            sendCmd(pgm_read_byte(initData + i));
        justreset=true;
        CS_OFF
    }
};

#endif
