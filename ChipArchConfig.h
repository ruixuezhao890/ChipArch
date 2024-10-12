/**
*********************************************************************
*********
* @project_name :lvgl
* @file : ChipArchConfig.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/5/9 
*********************************************************************
*********
*/
//

#ifndef LVGL_CHIPARCHCONFIG_H
#define LVGL_CHIPARCHCONFIG_H

#define VERSION 1.0
//这是竖屏的分辨率
//#define VerticalScreen
#ifdef VerticalScreen
#define MY_DISP_HOR_RES   240
#define MY_DISP_VER_RES   280
#else
#define MY_DISP_HOR_RES   240 //宽
#define MY_DISP_VER_RES   320  //高
#endif

#define MC_DB_DISP_HOR  "DISP_HOR"
#define MC_DB_DISP_VER  "DISP_VER"

/*power*/
#define MC_DB_BATTERY_LEVEL             "_BAT_LV"
#define MC_DB_BATTERY_LEVEL_T           std::uint8_t
#define MC_DB_BATTERY_IS_CHARGING       "_BAT_CHG"
#define MC_DB_BATTERY_IS_CHARGING_T     bool

#define FMT_ENABEL_EXIST 1



#define FREERTOS 0
#define Examlpes 0

#define MCU 0
#define STM32 0
#define ESP32 0
#define COMPUTER 1

#define TOUCH_PORT 0
#define DISPLAY_PORT 1


#define SRAM 1
#define IMU 1
#define LVGL_UPDATA_TIME (5)

#define FONT_NAME Font
#define FS_LETTER 'S'
#define FONT_PATH "S:/FONT/Font_16.bin"
#define USE_FATFS_FILE_SYSTEM 0
#define USE_PC_FILE_SYSTEM 1

#define MESSAGE_NUM 16
/*****Number of buffers*****/
#define BUFFER_NUM 2 //default:2 min:1 max:3


#endif //LVGL_CHIPARCHCONFIG_H
