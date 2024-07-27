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
DisplayInterface *HAL::DisplayInterface_ = nullptr;
InputDeviceGroup *HAL::InputDeviceGroup_ = nullptr;
fileSystemInterface *HAL::FileInterface_ = nullptr;

void HAL::initInputDevice(char letter) {
    DisplayInterface_ = new DisplayInterface();
    InputDeviceGroup_ = new InputDeviceGroup(DisplayInterface_, letter);
    if (InputDeviceGroup_->getFileSystemInterface()) {
        FileInterface_ = InputDeviceGroup_->getFileSystemInterface();
    }
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

    spdlog::set_level(spdlog::level::debug);

    initInputDevice(letter);

    spdlog::info("HAL injected, type:{}", inject->type().c_str());
//如果想要使用行号之类的标志使用
//SPDLOG_LOGGER_INFO(spdlog::default_logger(), "Hello {}", "world");
//这个宏函数就可以得到行号
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
        spdlog::info("HAL not exist");
        return;
    }
    delete hal_;
    delete DisplayInterface_;
    delete InputDeviceGroup_;
    hal_ = nullptr;
    DisplayInterface_ = nullptr;
    InputDeviceGroup_ = nullptr;
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

#endif

DisplayInterface *HAL::getDisplayInterface() {
    return DisplayInterface_;
}

InputDeviceGroup *HAL::getInputDeviceGroup() {
    return InputDeviceGroup_;
}

#if MCU
void HAL::TouchpadPointRead(lv_indev_data_t *data) {
    getHal()->touchpad_point_read(data);
}

void HAL::touchpad_point_read(lv_indev_data_t *data) {

}
#endif

void HAL::UpDate() {
    lv_task_handler();
    getHal()->update();
}

void HAL::update() {

}

#if ESP32 && MCU
void HAL::delay_ms(unsigned long milliseconds) {

}
#elif COMPUTER

void HAL::delay(unsigned long milliseconds) {

}

bool HAL::GetAnyButton() {
    return getHal()->getAnyButton();
}

bool HAL::getAnyButton() {
    return false;
}

void HAL::PopFatalError(const String& msg) {
    getHal()->popFatalError(msg);
}

void HAL::popFatalError(const String& msg) {

}

bool HAL::CheckSdCard() {
    return getHal()->checkSdCard();
}

bool HAL::checkSdCard() {
    return false;
}

void HAL::VolumeStart(const String& filePath) {
    getHal()->volumeStart(filePath);
}

void HAL::volumeStart( const String& filePath) {

}

void HAL::VolumeStop() {
    getHal()->volumeStop();
}

void HAL::volumeStop() {

}

void HAL::SetVolume(uint8_t volume) {
    getHal()->setVolume(volume);
}

void HAL::setVolume(uint8_t volume) {

}
#if IMU
void HAL::UpdateImuData() {
    getHal()->updateImuData();
}

void HAL::updateImuData() {

}

ImuData_t &HAL::GetImuData() {
    return getHal()->getImuData();
}

ImuData_t &HAL::getImuData() {
    return imu_data_;
}
#endif
unsigned long HAL::Millis() {
    return getHal()->millis();
}

unsigned long HAL::millis() {
    return 0;
}

void HAL::PowerOff() {
    getHal()->powerOff();
}

void HAL::powerOff() {

}

void HAL::Reboot() {
    getHal()->reboot();
}

void HAL::reboot() {

}



#endif





