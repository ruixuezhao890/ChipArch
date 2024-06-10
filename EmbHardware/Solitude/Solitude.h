/**
*********************************************************************
*********
* @project_name :lvgl
* @file : Solitude.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/4/12 
*********************************************************************
*********
*/
//

#ifndef LVGL_SOLITUDE_H
#define LVGL_SOLITUDE_H
#include "ChipArch/EmbHardware/HAL.h"
#if COMPUTER

class Solitude:public HAL{
public:
    Solitude()=default;

    String type() override;

    void init() override;

    void delay(unsigned long milliseconds) override;

    void display(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p) override;

    void keyboard_read(lv_indev_data_t *data) override;

    void mouse_point_read(lv_indev_data_t *data) override;

};
#endif
#endif //LVGL_SOLITUDE_H
