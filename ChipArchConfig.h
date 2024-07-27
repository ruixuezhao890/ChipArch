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

#define FREERTOS 0
#define Examlpes 0
#define MCU 0
#define STM32 0
#define ESP32 1
#define TOUCH 0
#define COMPUTER 1
#define IMU 1
#define LVGL_UPDATA_TIME (1*1000)


#define MESSAGE_NUM 32
/*****Number of buffers*****/
#define BUFFER_NUM 2 //default:2 min:1 max:3

/**
    %v	用户的日志文本
    %t	线程id
    %P	进程id
    %n	日志器名称
    %l	日志级别
    %x	简略的日期 MM/DD/YY
    %X	24小时制的时间，显示时分秒
    %s	显示日志所在的文件的名称。需要使用spdlog提供的宏输出日志才有效果
    %!	显示日志所在的函数的名称。需要使用spdlog提供的宏输出日志才有效果
    %#	显示日志所在的行号。需要使用spdlog提供的宏输出日志才有效果
 * */
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_INFO

#endif //LVGL_CHIPARCHCONFIG_H
