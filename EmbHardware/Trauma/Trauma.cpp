#include "EmbHardware/Trauma/Trauma.h"
#if ESP32&&MCU
#include "FreeRTOS.h"
#include "PWR_Key.h"
#include "Wireless.h"
#include "Gyro_QMI8658.h"
#include "RTC_PCF85063.h"
#include "SD_Card.h"
#include "Audio_PCM5101.h"
#include "EmbHardware/LVGLPort/porting/lv_port_disp.h"
#include "EmbHardware/LVGLPort/porting/lv_port_indev.h"
String Trauma::type() {
    return "ESP32";
}

void Trauma::init() {
   Serial.begin(115200);
   fmt::newline_info("BSP init");
//    BAT_Init();
    I2C_Init();
    RTC_Init();
    QMI8658_Init();
    SD_Init();
    Audio_Init();

   lv_init();
   lv_port_disp_init();
    lv_port_indev_init();

   fmt::newline_info("BSP init OK");
//    touch_driver_init();

}

void Trauma::delay_ms(unsigned long milliseconds) {
    delay(milliseconds);
}

void Trauma::display(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p) {
    LCD_addWindow(area->x1,area->y1,area->x2,area->y2,(uint16_t *)color_p);
    lv_disp_flush_ready(disp_drv);
}

void Trauma::keyboard_read(lv_indev_data_t *data) {
    HAL::keyboard_read(data);
}

void Trauma::touchpad_point_read(lv_indev_drv_t * indev_drv,lv_indev_data_t *data) {
    uint16_t touchpad_x[5] = {0};
    uint16_t touchpad_y[5] = {0};
    uint16_t strength[5]   = {0};
    uint8_t touchpad_cnt = 0;
    Touch_Read_Data();
    uint8_t touchpad_pressed = Touch_Get_XY(touchpad_x, touchpad_y, strength, &touchpad_cnt, CST328_LCD_TOUCH_MAX_POINTS);
    if (touchpad_pressed && touchpad_cnt > 0) {
        data->point.x = touchpad_x[0];
        data->point.y = touchpad_y[0];
        data->state = LV_INDEV_STATE_PR;
//        printf("LVGL  : X=%u Y=%u num=%d\r\n", touchpad_x[0], touchpad_y[0],touchpad_cnt);
    } else {
        data->state = LV_INDEV_STATE_REL;
    }
}

void Trauma::up_data_() {
//    Timer_Loop();
//     Audio_Loop();
    QMI8658_Loop();
    RTC_Loop();
    os_delay(2);
}


void Trauma::os_delay(unsigned long millisenconds) {
    vTaskDelay(millisenconds/portTICK_PERIOD_MS);
}
#if SRAM
// 重载的new操作符，用于PSRAM
void* operator new(size_t size) {
    void* ptr = heap_caps_malloc(size, MALLOC_CAP_SPIRAM);  // 在PSRAM上分配内存
    if (ptr == nullptr) {
        throw std::bad_alloc();  // 如果分配失败，抛出异常
    }
    return ptr;
}

// 重载的new[]操作符，用于PSRAM
void* operator new[](size_t size) {
    return operator new(size);  // 直接调用上面定义的new操作符
}

// 重载的delete操作符，用于PSRAM
void operator delete(void* ptr) noexcept {
    if (ptr != nullptr) {
        heap_caps_free(ptr);  // 在PSRAM上释放内存
    }
}

// 重载的delete[]操作符，用于PSRAM
void operator delete[](void* ptr) noexcept {
    operator delete(ptr);  // 直接调用上面定义的delete操作符
}
bool is_pointer_in_psram(void* ptr) {
    const intptr_t psram_start = SOC_EXTRAM_DATA_LOW;
    const intptr_t psram_end = SOC_EXTRAM_DATA_HIGH;
    intptr_t address = reinterpret_cast<intptr_t>(ptr);

    return (address >= psram_start) && (address <= psram_end);
}
#endif
#endif