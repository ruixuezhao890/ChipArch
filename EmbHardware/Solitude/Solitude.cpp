/**
*********************************************************************
*********
* @project_name :lvgl
* @file : Solitude.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/4/12 
*********************************************************************
*********
*/
//

#include "Solitude.h"
#if COMPUTER
#include "lv_drivers/sdl/sdl.h"
#include <unistd.h>

void Solitude::init() {
    lv_init();
    sdl_init();
}

void Solitude::delay(unsigned long milliseconds) {
    usleep(milliseconds);
}

void Solitude::display(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p) {
    sdl_display_flush(disp_drv,area,color_p);
}

void Solitude::keyboard_read(lv_indev_data_t *data) {
    sdl_keyboard_read(HAL::InputDeviceGroup_->getKeyBoardInterface()->raw_ptr()->driver,data);
}

void Solitude::mouse_point_read(lv_indev_data_t *data) {
    sdl_mouse_read(HAL::InputDeviceGroup_->getKeyBoardInterface()->raw_ptr()->driver,data);
}

String Solitude::type() {
    return "computer";
}

#endif