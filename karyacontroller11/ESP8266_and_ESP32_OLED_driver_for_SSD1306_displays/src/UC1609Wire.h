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

#ifndef UC1609Wire_h
#define UC1609Wire_h

#include "OLEDDisplay.h"

#define uint unsigned int
#define uchar unsigned char

#define RS this->_cd // C/D  Data/Command Control
#define SDA this->_sda //serial data input
#define SCLK this->_scl //serial clock input

#define CS1_1
#define CS1_0
#define NOP __asm__ __volatile__("nop");

#define FASTPIN

#ifdef FASTPIN
#define PIN_ON(pin) GPOS = (1 << pin)
#define PIN_OFF(pin) GPOC = (1 << pin)
#else
#define PIN_ON(pin) digitalWrite(pin, HIGH)
#define PIN_OFF(pin) digitalWrite(pin, LOW)
#endif

//#define PIN_OFF(pin) WRITE_PERI_REG( 0x60000308, 1 << pin)

//#define PIN_ON(pin) digitalWrite(pin,HIGH)
//#define PIN_OFF(pin) digitalWrite(pin,LOW)

#define RS_1 PIN_ON(RS)
#define RS_0 PIN_OFF(RS)
#define SCLK_1 PIN_ON(SCLK)
#define SCLK_0 PIN_OFF(SCLK)

#define SDAe(n)      \
    if (n)           \
        PIN_ON(SDA); \
    else             \
        PIN_OFF(SDA);

const uchar Contrast_level = 140; // for DARK from best is 200, other is 150

#define ROTATE_DISPLAY() Write_Instruction(0xC2) //  Reverse display : 0 illuminated
#define REVERSE_DISPLAY_ON() Write_Instruction(0xa7) //  Reverse display : 0 illuminated
#define REVERSE_DISPLAY_OFF() Write_Instruction(0xa6) //  Normal display : 1 illuminated
#define ENTIRE_DISPLAY_ON() Write_Instruction(0xa5) //  Entire dislay   Force whole LCD point
#define ENTIRE_DISPLAY_OFF() Write_Instruction(0xa4) //  Normal display

#define Start_column 0x00
#define Start_page 0x00
#define StartLine_set 0x00

//--------------------------------------

class UC1609Wire : public OLEDDisplay {
private:
    uint8_t _sda;
    uint8_t _scl;
    uint8_t _cd;

public:
    UC1609Wire(uint8_t sda, uint8_t scl, uint8_t cd, OLEDDISPLAY_GEOMETRY g = GEOMETRY_192_64)
    {
        setGeometry(g);

        this->_sda = sda;
        this->_scl = scl;
        this->_cd = cd;
        pinMode(_scl, OUTPUT);
        digitalWrite(scl, LOW);
        pinMode(_sda, OUTPUT);
        digitalWrite(sda, LOW);
    }

    bool connect()
    {
        //we actualy use SPI

        return true;
    }

    void display(void)
    {
        long m = micros();
        //Initial();
        pinMode(_cd, OUTPUT);
        pinMode(_scl, OUTPUT);
        pinMode(_sda, OUTPUT);

#ifdef OLEDDISPLAY_DOUBLE_BUFFER

        uint8_t minBoundY = UINT8_MAX;
        uint8_t maxBoundY = 0;

        uint8_t minBoundX = UINT8_MAX;
        uint8_t maxBoundX = 0;

        uint8_t x, y;
        extern int motionloop();
        // Calculate the Y bounding box of changes
        // and copy buffer[pos] to buffer_back[pos];
        for (y = 0; y < (displayHeight / 8); y++) {
            for (x = 0; x < displayWidth; x++) {
                uint16_t pos = x + y * displayWidth;
                if (buffer[pos] != buffer_back[pos]) {
                    minBoundY = _min(minBoundY, y);
                    maxBoundY = _max(maxBoundY, y);
                    minBoundX = _min(minBoundX, x);
                    maxBoundX = _max(maxBoundX, x);
                }
                buffer_back[pos] = buffer[pos];
            }
            yield();
            motionloop();
        }

        // If the minBoundY wasn't updated
        // we can savely assume that buffer_back[pos] == buffer[pos]
        // holdes true for all values of pos
        if (minBoundY == UINT8_MAX)
            return;

        // Calculate the colum offset
        uint8_t minBoundXp2H = (minBoundX + 0) & 0x0F; // +2
        uint8_t minBoundXp2L = 0x10 | ((minBoundX + 0) >> 4); // +2

        for (y = minBoundY; y <= maxBoundY; y++) {
            //sendCommand(0xB0 + y);
            //sendCommand(minBoundXp2H);
            //sendCommand(minBoundXp2L);
            Set_Page_Address(y);
            Set_Column_Address(minBoundX);
            RS_1;
            CS1_0;
#define SCLK_TICK(n)    \
    SDAe(dat&(1 << n)); \
    SCLK_0;             \
    NOP;                \
    SCLK_1
            for (x = minBoundX; x <= maxBoundX; x++) {
                //Write_Data(buffer[x + y * displayWidth]);
                uint8_t dat = buffer[x + y * displayWidth];
                SCLK_TICK(7);
                SCLK_TICK(6);
                SCLK_TICK(5);
                SCLK_TICK(4);
                SCLK_TICK(3);
                SCLK_TICK(2);
                SCLK_TICK(1);
                SCLK_TICK(0);
            }
            CS1_1;
            yield();
            motionloop();
        }

//m=micros()-m;
//Serial.println(m);
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
        CS1_0;
        RS_0;
        for (i = 0; i < 8; i++) {
            SDAe((dat & 0x80));
            SCLK_0;
            dat = dat << 1;
            SCLK_1;
        }

        CS1_1;
        return;
    }

    inline void sendCommand(uint8_t command) __attribute__((always_inline))
    {
    }

    void Set_Page_Address(unsigned char add)
    {
        add = 0xb0 | add;
        Write_Instruction(add);
    }

    void Set_Column_Address(unsigned char add)
    {
        Write_Instruction((0x10 | (add >> 4)));
        Write_Instruction((0x0f & add));
    }

    void setContrast(uint8_t mod, bool rev = false)
    {
        pinMode(_cd, OUTPUT);
        Write_Instruction(0x81);
        Write_Instruction(mod);
        if (rev)
            REVERSE_DISPLAY_ON();
        else
            REVERSE_DISPLAY_OFF();
    }
    void setRotate(bool rot)
    {
        Write_Instruction(rot ? 0xC2 : 0xC4);
    }

    void Initial(void)
    {
        pinMode(_cd, OUTPUT);
        pinMode(_scl, OUTPUT);
        pinMode(_sda, OUTPUT);

        Write_Instruction(0xe2); //system reset

        Write_Instruction(0xa3); //set Frame Rate[A0: 76fps, A1b: 95fps, A2b: 132fps, A3b: 168fps(fps: frame-per-second)]

        Write_Instruction(0xeb); //set BR
        Write_Instruction(0x2f); //set Power Control

        Write_Instruction(0xc2); //set LCD Mapping Control
        Write_Instruction(0xaf); //display Enable
        Write_Instruction(0x81); //set PM
        Write_Instruction(190); //set PM 110
        delay(20);
    }
};

#endif
