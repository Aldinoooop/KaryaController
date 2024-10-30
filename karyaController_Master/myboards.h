//#pragma once
#ifndef xmyboards_H
  #define myboards_H

  //#include "platform.h"
  //#include "config_pins.h"

  /*
    ============================================================================================
       _WEMOS_CNC_ONLY
    ============================================================================================
  */
  #if defined(BOARD_WEMOSCNC_ONLY_V2)
    #define INDEX "/cnc.html"
    #define xdirection 25
    #define xstep 26

    #define zdirection 15
    #define zstep 2

    // z and e have same direction pin, we think that normally slicer never move z and e together.. we hope we right :D
    #define ydirection 27
    #define ystep 14
    //#define e0direction D6
    //#define e0step D2

    #define AC_SPINDLE // 
    //#define INVERTENDSTOP
    #define NUMBUFFER 30

    //#define IR_KEY D2
    #define LCD_OLED
    #define IR_OLED_MENU 0x3c, RX, TX
    //#define IR_OLED_MENU 0x3c, RX, D1

  #else
    #warning No BOARD Defined !
  #endif
#endif
