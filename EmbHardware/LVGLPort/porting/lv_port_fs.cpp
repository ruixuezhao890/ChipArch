/**
*********************************************************************
*********
* @project_name :lvgl
* @file : lv_port_fs.cpp
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2024/10/11 
*********************************************************************
*********
*/


#include "lv_port_fs.h"
#include "lvgl/lvgl.h"


void lv_port_fs_init(){
#if  LV_USE_FS_STDIO
    lv_fs_stdio_init();
#endif
#if LV_USE_FS_FATFS
    lv_fs_fatfs_init();
#endif
}