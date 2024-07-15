#ifndef Trauma_H
#define Trauma_H
#include "ChipArch/ChipArchConfig.h"
#if ESP32&&MCU
#include "ChipArch/EmbHardware/HAL.h"
#include "Arduino.h"
#include "TFT_eSPI.h"
class Trauma:public HAL
{
protected:
    TFT_eSPI * display_= nullptr;
public:
    String type() override;

    void init() override;

    void delay_ms(unsigned long milliseconds) override;

    void display(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p) override;

    void keyboard_read(lv_indev_data_t *data) override;

    void touchpad_point_read(lv_indev_data_t *data) override;

    void up_date() override;
};





#endif
#endif