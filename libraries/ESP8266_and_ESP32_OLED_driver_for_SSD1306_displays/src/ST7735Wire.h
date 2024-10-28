
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

#ifndef ST7735Wire_h
#define ST7735Wire_h

#include "OLEDDisplay.h"

#define uint unsigned int
#define uchar unsigned char

#define CS this->_cs // C/D  Data/Command Control
#define SDA this->_sda //serial data input
#define SCLK this->_scl //serial clock input

#define NOP __asm__ __volatile__("nop");

#define FASTPIN

#ifdef FASTPIN
#define PIN_ON(pin) GPOS = (1 << pin)
#define PIN_OFF(pin) GPOC = (1 << pin)
#else
#define PIN_ON(pin) digitalWrite(pin, HIGH)
#define PIN_OFF(pin) digitalWrite(pin, LOW)
#endif

#define CS_1    \
    if (CS > 0) \
    PIN_ON(CS)
#define CS_0    \
    if (CS > 0) \
    PIN_OFF(CS)

#define SCLK_1 PIN_ON(SCLK)
#define SCLK_0 PIN_OFF(SCLK)

#define SDAe(n)      \
    if (n)           \
        PIN_ON(SDA); \
    else             \
        PIN_OFF(SDA);

#define ISDATA  \
    SDAe(HIGH); \
    SCLK_1;     \
    SCLK_0
#define ISCMD  \
    SDAe(LOW); \
    SCLK_1;    \
    SCLK_0

const uchar Contrast_level = 140;

#define ST7735_TFTWIDTH  128
#define ST7735_TFTHEIGHT 160

#define ST7735_INIT_DELAY 0x80

// These are the ST7735 control registers
// some flags for initR() :(

#define ST7735_TFTWIDTH  128
#define ST7735_TFTHEIGHT 160

#define ST7735_NOP     0x00
#define ST7735_SWRESET 0x01
#define ST7735_RDDID   0x04
#define ST7735_RDDST   0x09

#define ST7735_SLPIN   0x10
#define ST7735_SLPOUT  0x11
#define ST7735_PTLON   0x12
#define ST7735_NORON   0x13

#define ST7735_INVOFF  0x20
#define ST7735_INVON   0x21
#define ST7735_DISPOFF 0x28
#define ST7735_DISPON  0x29
#define ST7735_CASET   0x2A
#define ST7735_RASET   0x2B
#define ST7735_RAMWR   0x2C
#define ST7735_RAMRD   0x2E

#define ST7735_PTLAR   0x30
#define ST7735_COLMOD  0x3A
#define ST7735_MADCTL  0x36

#define ST7735_FRMCTR1 0xB1
#define ST7735_FRMCTR2 0xB2
#define ST7735_FRMCTR3 0xB3
#define ST7735_INVCTR  0xB4
#define ST7735_DISSET5 0xB6

#define ST7735_PWCTR1  0xC0
#define ST7735_PWCTR2  0xC1
#define ST7735_PWCTR3  0xC2
#define ST7735_PWCTR4  0xC3
#define ST7735_PWCTR5  0xC4
#define ST7735_VMCTR1  0xC5

#define ST7735_RDID1   0xDA
#define ST7735_RDID2   0xDB
#define ST7735_RDID3   0xDC
#define ST7735_RDID4   0xDD

#define ST7735_PWCTR6  0xFC

#define ST7735_GMCTRP1 0xE0
#define ST7735_GMCTRN1 0xE1


#define MADCTL_MY  0x80
#define MADCTL_MX  0x40
#define MADCTL_MV  0x20
#define MADCTL_ML  0x10
#define MADCTL_RGB 0x00
#define MADCTL_BGR 0x08
#define MADCTL_MH  0x04

// New color definitions use for all my libraries
#define TFT_BLACK       0x0000      /*   0,   0,   0 */
#define TFT_NAVY        0x000F      /*   0,   0, 128 */
#define TFT_DARKGREEN   0x03E0      /*   0, 128,   0 */
#define TFT_DARKCYAN    0x03EF      /*   0, 128, 128 */
#define TFT_MAROON      0x7800      /* 128,   0,   0 */
#define TFT_PURPLE      0x780F      /* 128,   0, 128 */
#define TFT_OLIVE       0x7BE0      /* 128, 128,   0 */
#define TFT_LIGHTGREY   0xC618      /* 192, 192, 192 */
#define TFT_DARKGREY    0x7BEF      /* 128, 128, 128 */
#define TFT_BLUE        0x001F      /*   0,   0, 255 */
#define TFT_GREEN       0x07E0      /*   0, 255,   0 */
#define TFT_CYAN        0x07FF      /*   0, 255, 255 */
#define TFT_RED         0xF800      /* 255,   0,   0 */
#define TFT_MAGENTA     0xF81F      /* 255,   0, 255 */
#define TFT_YELLOW      0xFFE0      /* 255, 255,   0 */
#define TFT_WHITE       0xFFFF      /* 255, 255, 255 */
#define TFT_ORANGE      0xFD20      /* 255, 165,   0 */
#define TFT_GREENYELLOW 0xAFE5      /* 173, 255,  47 */
#define TFT_PINK        0xF81F

// Color definitions for backwards compatibility
#define ST7735_BLACK       0x0000      /*   0,   0,   0 */
#define ST7735_NAVY        0x000F      /*   0,   0, 128 */
#define ST7735_DARKGREEN   0x03E0      /*   0, 128,   0 */
#define ST7735_DARKCYAN    0x03EF      /*   0, 128, 128 */
#define ST7735_MAROON      0x7800      /* 128,   0,   0 */
#define ST7735_PURPLE      0x780F      /* 128,   0, 128 */
#define ST7735_OLIVE       0x7BE0      /* 128, 128,   0 */
#define ST7735_LIGHTGREY   0xC618      /* 192, 192, 192 */
#define ST7735_DARKGREY    0x7BEF      /* 128, 128, 128 */
#define ST7735_BLUE        0x001F      /*   0,   0, 255 */
#define ST7735_GREEN       0x07E0      /*   0, 255,   0 */
#define ST7735_CYAN        0x07FF      /*   0, 255, 255 */
#define ST7735_RED         0xF800      /* 255,   0,   0 */
#define ST7735_MAGENTA     0xF81F      /* 255,   0, 255 */
#define ST7735_YELLOW      0xFFE0      /* 255, 255,   0 */
#define ST7735_WHITE       0xFFFF      /* 255, 255, 255 */
#define ST7735_ORANGE      0xFD20      /* 255, 165,   0 */
#define ST7735_GREENYELLOW 0xAFE5      /* 173, 255,  47 */
#define ST7735_PINK        0xF81F

#define SCR_WD 80
#define SCR_HT 64
#define SCR_HT8 8

#define ALIGN_LEFT 0
#define ALIGN_RIGHT -1
#define ALIGN_CENTER -2

#define SET 1
#define CLR 0
#define XOR 2

#define CS_ACTIVE CS_0
#define CS_IDLE CS_1

#define RGB16(r,g,b) ((r) + (g<<5) + (b<<11))

// Idea swiped from 1.8" TFT code: rather than a bazillion writeCommand()
// and writeData() calls, screen initialization commands and arguments are
// organized in this table in PROGMEM.  It may look bulky, but that's
// mostly the formatting -- storage-wise this is considerably more compact
// than the equiv code.  Command sequence is from TFT datasheet.
#define DELAY 0x80
const uint16_t _lcd_init_list[] = {

    SPFD54124B_CMD_SLPOUT,
    SPFD54124B_CMD_COLMOD, SPFD54124B_SEND_DATA | SPFD54124B_CMD_COLMOD_MCU16bit,
    SPFD54124B_CMD_DISPON,
    SPFD54124B_CMD_INVOFF,
    SPFD54124B_CMD_NORON
};
//--------------------------------------

class ST7735Wire : public OLEDDisplay {
private:
    uint8_t _sda;
    uint8_t _scl;
    uint8_t _cs,_rs,hpos,_a0;
    uint16_t col,hcol;

public:
    ST7735Wire(uint8_t sda, uint8_t scl, uint8_t cs = -1, uint8_t rs=-1,uint8_t a0=-1, OLEDDISPLAY_GEOMETRY g = GEOMETRY_160_130)
    {
        setGeometry(g);

        this->_sda = sda;
        this->_scl = scl;
        this->_cs = cs;
        this->_rs=rs;
        this->_a0=a0;
        col=RGB16(31,63,15);
        hcol=RGB16(15,33,31);
        hpos=23;
        
        pinMode(_scl, OUTPUT);
        pinMode(_sda, OUTPUT);
        if (_cs > 0)
            pinMode(_cs, OUTPUT);
    }

    bool connect()
    {
        //we actualy use SPI

        return true;
    }

    void setWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
    {
        uint8_t t0, t1;
        CS_ACTIVE;

        writeCommand(SPFD54124B_CMD_CASET); // Column addr set
        writeData(x0 >> 8);
        writeData(x0); // X start
        writeData(x1 >> 8);
        writeData(x1); // X end

        writeCommand(SPFD54124B_CMD_RASET); // Page addr set
        writeData(y0 >> 8);
        writeData(y0); // Y start
        writeData(y1 >> 8);
        writeData(y1); // Y end

        writeCommand(SPFD54124B_CMD_RAMWR);
        CS_IDLE;
    }
    void sendPixel(bool lit)
    {
#define SCLK_TICK \
    SDAe(lit);    \
    SCLK_1;       \
    SCLK_0;
        ISDATA;
        SCLK_TICK;
        SCLK_TICK;
        SCLK_TICK;
        SCLK_TICK;
        SCLK_TICK;
        SCLK_TICK;
        SCLK_TICK;
        SCLK_TICK;
    }
    void display(void)
    {

#ifdef OLEDDISPLAY_DOUBLE_BUFFER
        long m = micros();
        if (_cs > 0)
            pinMode(_cs, OUTPUT);
        pinMode(_scl, OUTPUT);
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
                if ((x<displayWidth) && (buffer[pos] != buffer_back[pos])) {
                    buffer_back[pos] = buffer[pos];
                    minBoundX = _min(minBoundX, x);
                    npx++;
                } else {
                    // draw a chunk of display
                    if ((minBoundX!=UINT8_MAX) && (npx>(x<displayWidth?10:0))) { // minimum 10pixel at once
                        CS_ACTIVE;
                        uint8_t maxBoundX=_min(x+1,displayWidth);
                        setWindow(130 - (y + 1) * 8, minBoundX+1,130 - y * 8 -1, maxBoundX);
                        uint8_t* pdat = &buffer[minBoundX + y * displayWidth];
                        for (uint8_t dx = minBoundX; dx < maxBoundX; dx++) {
                            // send 8pixel /byte
                            uint8_t dat = *pdat;
                            pdat++;
                            uint8_t hy=y*8+7;
                            for (uint8_t p = 0x80; p; p>>=1) {
                                uint16_t ccol=col;
                                if (hy--<hpos)ccol=hcol;
                                uint16_t px=dat & p ? ccol:0;
                                writeData(px >> 8);
                                writeData(px);
                            }
                        }
                        CS_IDLE;
                        // reset counter find other chunk
                        minBoundX = UINT8_MAX;
                        npx=0;

                    }
                    
                }

            }

            yield();
            motionloop();
        }

        

//m=micros()-m;
//Serial.println(m);
#else

#endif
    }
    // clear everything
    void setLCDColor(uint16_t c1,uint16_t c2){
        col=c1;
        hcol=c2;
        memset(buffer_back, 1, displayBufferSize);
    }
    void fillScreen(uint16_t c)
    {
        uint8_t x, y, hi = c >> 8, lo = c;

        setWindow(0, 0, 160 - 1, 130 - 1);

        CS_ACTIVE;

        for (y = 130; y > 0; y--) {
            for (x = 160; x > 0; x--) {
                writeData(hi);
                writeData(lo);
                lo++;
            }
            hi++;
        }
        CS_IDLE;
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
    void writeany(uint16_t dat)
    {
        unsigned char i;
        CS_ACTIVE;
        for (i = 0; i < 9; i++) {
            SDAe((dat & 0x100));
            SCLK_1;
            dat = dat << 1;
            SCLK_0;
        }

        CS_IDLE;
        return;
    }
    void writeCommand(unsigned char dat)
    {
        unsigned char i;
        CS_ACTIVE;
        ISCMD;
        for (i = 0; i < 8; i++) {
            SDAe((dat & 0x80));
            SCLK_1;
            dat = dat << 1;
            SCLK_0;
        }

        CS_IDLE;
        return;
    }
    void writeData(uint16_t dat)
    {
        unsigned char i;
        CS_ACTIVE;
        ISDATA;
        for (i = 0; i < 8; i++) {
            SDAe((dat & 0x80));
            SCLK_1;
            dat = dat << 1;
            SCLK_0;
        }

        CS_IDLE;
        return;
    }

    void setContrast(uint8_t mod, bool rev = false)
    {
    }

    inline void sendCommand(uint8_t command) __attribute__((always_inline))
    {
    }

    void Initial(void)
    {
        if (_cs > 0)pinMode(_cs, OUTPUT);
        pinMode(_scl, OUTPUT);
        pinMode(_sda, OUTPUT);
        if (_rs > 0) {
            pinMode(_rs, OUTPUT);
            digitalWrite(_rs,LOW);
            delay(200);
            digitalWrite(_rs,HIGH);
            delay(200);
        }
        

        const uint16_t* list = &_lcd_init_list[0];
        uint8_t size = sizeof(_lcd_init_list) / sizeof(_lcd_init_list[0]);
        while (size--)
            writeany(*list++);
    }
};

#endif

