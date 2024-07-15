#include "ChipArch/EmbHardware/Trauma/Trauma.h"
#if ESP32&&MCU

String Trauma::type() {
    return "ESP32";
}

void Trauma::init() {
    display_ =new TFT_eSPI(MY_DISP_HOR_RES,MY_DISP_VER_RES);
}

void Trauma::delay_ms(unsigned long milliseconds) {
    delay(milliseconds);
}

void Trauma::display(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p) {
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

   display_->startWrite();
   display_->setAddrWindow(area->x1, area->y1, w, h);
   display_->pushColors((uint16_t *)&color_p->full, w * h, true);
   display_->endWrite();

    lv_disp_flush_ready(disp_drv);
}

void Trauma::keyboard_read(lv_indev_data_t *data) {
    HAL::keyboard_read(data);
}

void Trauma::touchpad_point_read(lv_indev_data_t *data) {
    HAL::touchpad_point_read(data);
}

void Trauma::up_date() {
    HAL::up_date();
}
#endif