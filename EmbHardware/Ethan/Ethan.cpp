/**
*********************************************************************
*********
* @project_name :chip_arch_demo
* @file : Ethan.cpp
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2024/6/23 
*********************************************************************
*********
*/
//

#include "Ethan.h"
#if STM32&&MCU

#include "./BSP/LCD/lcd.h"
#include "./BSP/LED/led.h"
#include "./BSP/KEY/key.h"
#include "./BSP/TIMER/gtim.h"
#include "./BSP/TOUCH/touch.h"
#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/usart/usart.h"
#include "./LVGL/lvgl/porting/lv_port_disp.h"
#include "./LVGL/lvgl/porting/lv_port_indev.h"

String Ethan::type() {
    return "STM32";
}

void Ethan::init() {
    HAL_Init();
    sys_stm32_clock_init(336,8,2,7);
    delay_init(168);
    usart_init(115200);
    led_init();
    key_init();
    gtim_tim3_int_init(10 - 1, 8400 - 1);

    lv_init();
    lcd_init();
    lcd_display_dir(1);
    tp_dev.init();
    gtim_tim6_int_init(5000-1,84-1);





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
    static lv_coord_t last_x = 0;
    static lv_coord_t last_y = 0;
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
    tp_dev.scan(0);
    if (tp_dev.sta&TP_PRES_DOWN){
        last_x= (lv_coord_t)tp_dev.x[0];
        last_y= (lv_coord_t)tp_dev.y[0];
        data->state=LV_INDEV_STATE_PR;
    }else{
        data->state=LV_INDEV_STATE_REL;
    }
    data->point.x=last_x;
    data->point.y=last_y;
}

void Ethan::updata() {
   LED1_TOGGLE();
//   LED0_TOGGLE();
}

bool Ethan::getAnyButton() {
  return  key_scan(0);
}

void Ethan::microseconds_delay(unsigned long milliseconds) {
    delay_us(milliseconds);
}

void Ethan::toggle_LED(uint8_t id) {

    if (id==1){
        LED0_TOGGLE();
    }else if (id==2){
        LED1_TOGGLE();
    }else{
        return;
    }
}

#endif