/**
*********************************************************************
*********
* @project_name :chip_arch_demo
* @file : Ethan.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/6/23 
*********************************************************************
*********
*/
//

#include "Ethan.h"
#if STM32&&MCU
#include "../Drivers/BSP/LCD/lcd.h"
#include "../Drivers/SYSTEM/delay/delay.h"
#include "../Drivers/SYSTEM/usart/usart.h"
#include "LED/led.h"
#include "TIMER/gtim.h"

String Ethan::type() {
    return "STM32";
}

void Ethan::init() {
    led_init();
    gtim_timx_int_init(10-1,8400-1);
    lcd_init();

    lv_init();
    usart_init(115200);

}

void Ethan::delay(unsigned long milliseconds) {
    delay_ms(milliseconds);
}

void Ethan::display(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p) {
    lcd_color_fill(area->x1,area->y1,area->x2,area->y2,(uint16_t *)color_p);
    lv_disp_flush_ready(disp_drv);
}

void Ethan::keyboard_read(lv_indev_data_t *data) {
    HAL::keyboard_read(data);
}

void Ethan::touchpad_point_read(lv_indev_data_t *data) {
//    static lv_coord_t last_x = 0;
//    static lv_coord_t last_y = 0;
//
//    /*Save the pressed coordinates and the state*/
//
//    if(touchpad_is_pressed()) {
//        touchpad_get_xy(&last_x, &last_y);
//        data->state = LV_INDEV_STATE_PR;
//    }
//    else {
//        data->state = LV_INDEV_STATE_REL;
//    }
//
//    /*Set the last pressed coordinates*/
//    data->point.x = last_x;
//    data->point.y = last_y;
}

void Ethan::up_date() {
   LED1_TOGGLE();
   LED0_TOGGLE();
}
#endif