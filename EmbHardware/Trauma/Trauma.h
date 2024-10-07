#ifndef Trauma_H
#define Trauma_H
#include "ChipArchConfig.h"
#if ESP32&&MCU
#include "EmbHardware/HAL.h"
#include "Arduino.h"



class Trauma:public HAL
{
protected:
   
public:
    String type() override;

    void init() override;

    void delay_ms(unsigned long milliseconds) override;

    void os_delay(unsigned long millisenconds) override;

    void display(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p) override;

    void keyboard_read(lv_indev_data_t *data) override;

    void touchpad_point_read(lv_indev_drv_t * indev_drv,lv_indev_data_t *data) override;

    void up_data_() override;
};





#endif
#endif