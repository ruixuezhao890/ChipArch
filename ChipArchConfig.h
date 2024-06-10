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

#define MY_DISP_HOR_RES    320
#define MY_DISP_VER_RES    240

#define MCU 0
#define TOUCH 0
#define COMPUTER 1

/*****Number of buffers*****/
#define BUFFER_NUM 2 //default:2 min:1 max:3

#endif //LVGL_CHIPARCHCONFIG_H
