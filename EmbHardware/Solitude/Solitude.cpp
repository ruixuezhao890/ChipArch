/**
*********************************************************************
*********
* @project_name :lvgl
* @file : Solitude.cpp
* @author : ruixuezhao890
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
#include "EmbHardware/LVGLPort/porting/lv_port_indev.h"
#include "EmbHardware/LVGLPort/porting/lv_port_disp.h"
#include <unistd.h>

void Solitude::init() {
    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();
}

void Solitude::delay(unsigned long milliseconds) {
    usleep(milliseconds);
}

void Solitude::display(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p) {
    sdl_display_flush(disp_drv,area,color_p);
}

void Solitude::keyboard_read(lv_indev_data_t *data) {

}

void Solitude::mouse_point_read(lv_indev_data_t *data) {

}

String Solitude::type() {
    return "computer";
}

#endif