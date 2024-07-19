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
//这是竖屏的分辨率
//#define VerticalScreen
#ifdef VerticalScreen
#define MY_DISP_HOR_RES   240
#define MY_DISP_VER_RES   280
#else
#define MY_DISP_HOR_RES   320 //宽
#define MY_DISP_VER_RES   240  //高
#endif
#define Examlpes 0
#define MCU 0
#define STM32 0
#define ESP32 1
#define TOUCH 0
#define COMPUTER 1
#define IMU 1
#define LVGL_UPDATA_TIME (1*1000)

/*****Number of buffers*****/
#define BUFFER_NUM 2 //default:2 min:1 max:3

#endif //LVGL_CHIPARCHCONFIG_H
