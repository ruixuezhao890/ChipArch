/**
*********************************************************************
*********
* @project_name :lvgl
* @file : HAL.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/4/12 
*********************************************************************
*********
*/
//


#include "HAL.h"

HAL *HAL::hal_ = nullptr;


void HAL::initInputDevice(char letter) {
   
}

HAL *HAL::getHal() {
    if (hal_)
        return hal_;
    return nullptr;
}

bool HAL::Inject(HAL *inject, char letter) {
    if (hal_) {
        return false;
    }
    if (!inject) {
        return false;
    }
    inject->init();



    initInputDevice(letter);

   fmt::newline_info("HAL injected, type:{}", inject->type().c_str());
    hal_ = inject;

    return true;
}

bool HAL::check() {
    if (hal_) {
        return true;
    }
    return false;
}

void HAL::destroy() {
    if (hal_ == nullptr) {
        LV_LOG("HAL not exist");
        return;
    }
    delete hal_;

    hal_ = nullptr;
   
}
void HAL:: Os_delay(unsigned long millisenconds){
    getHal()->os_delay(millisenconds);
}

void HAL:: os_delay(unsigned long millisenconds){

}
void HAL::Delay(unsigned long milliseconds) {
#if ESP32 && MCU
    getHal()->delay_ms(milliseconds);
#else
    getHal()->delay(milliseconds);
#endif
}

void HAL::Display(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p) {
    getHal()->display(disp_drv, area, color_p);
}

void HAL::display(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p) {

}

void HAL::KeyBoardRead(lv_indev_data_t *data) {
    getHal()->keyboard_read(data);
}

void HAL::keyboard_read(lv_indev_data_t *data) {

}

#if COMPUTER

void HAL::MousePointRead(lv_indev_data_t *data) {
    getHal()->mouse_point_read(data);
}

void HAL::mouse_point_read(lv_indev_data_t *data) {

}

#elif MCU
void HAL::Toggle_LED(uint8_t id) {
    getHal()->toggle_LED(id);
}

void HAL::toggle_LED(uint8_t id) {

}
#endif


#if MCU

void HAL::TouchpadPointRead(lv_indev_drv_t * indev_drv,lv_indev_data_t *data) {
    getHal()->touchpad_point_read(indev_drv,data);
}

void HAL::touchpad_point_read(lv_indev_drv_t * indev_drv,lv_indev_data_t *data) {

}
#endif

void HAL::Up_Data() {

    getHal()->up_data_();
}

void HAL::up_data_() {

}


void HAL::Microseconds_delay(unsigned long milliseconds) {
    getHal()->microseconds_delay(milliseconds);
}

void HAL::microseconds_delay(unsigned long milliseconds) {

}

bool HAL::GetAnyButton() {
   return getHal()->getAnyButton();
}

bool HAL::getAnyButton() {
    return false;
}

void  HAL::Up_data_lvgl() {
    lv_timer_handler();
}

void HAL::PowerOff() {

}

void HAL::powerOff() {

}

void HAL::Reboot() {

}

void HAL::reboot() {

}

void HAL::VolumeStart(const String &filePath) {

}

void HAL::volumeStart(const String &filePath) {

}

void HAL::VolumeStop() {

}

void HAL::volumeStop() {

}

void HAL::SetVolume(uint8_t volume) {

}

void HAL::setVolume(uint8_t volume) {

}

bool HAL::CheckSdCard() {
    return false;
}

bool HAL::checkSdCard() {
    return false;
}

void HAL::PopFatalError(const String &msg) {

}

void HAL::popFatalError(const String &msg) {

}

void HAL::UpdateImuData() {

}

void HAL::updateImuData() {

}

ImuData_t &HAL::GetImuData() {
    return getHal()->getImuData();
}

ImuData_t &HAL::getImuData() {
    return imu_data_;
}




#if ESP32 && MCU
void HAL::delay_ms(unsigned long milliseconds) {

}
#elif COMPUTER

void HAL::delay(unsigned long milliseconds) {

}

#endif





