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

#include <unistd.h>
#include "HAL.h"

HAL * HAL::hal_= nullptr;
DisplayInterface * HAL:: DisplayInterface_= nullptr;
InputDeviceGroup * HAL:: InputDeviceGroup_= nullptr;

void HAL::initInputDevice(char letter) {
      DisplayInterface_=new DisplayInterface();
      InputDeviceGroup_=new InputDeviceGroup(DisplayInterface_,letter);
}

HAL *HAL::getHal() {
    if (hal_)
        return hal_;
    return nullptr;
}

bool HAL::Inject(HAL *inject,char letter) {
    if (hal_){
        return false;
    }
    if (!inject){
        return false;
    }
    inject->init();
    initInputDevice(letter);
    LV_LOG("HAL injected, type: {%s}\n", inject->type().c_str());

    hal_ = inject;

    return true;
}

bool HAL::check() {
    if (hal_){
        return true;
    }
    return false;
}

void HAL::destroy() {
    if (hal_ == nullptr)
    {
       LV_LOG("HAL not exist");
        return;
    }
    delete hal_;
    delete DisplayInterface_;
    delete InputDeviceGroup_;
    hal_ = nullptr;
    DisplayInterface_=nullptr;
    InputDeviceGroup_=nullptr;
}

void HAL::Delay(unsigned long milliseconds) {
   getHal()->delay(milliseconds);
}

void HAL::delay(unsigned long milliseconds) {
    usleep(milliseconds);
}

void HAL::Display(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p) {
    getHal()->display(disp_drv,area,color_p);
}

void HAL::display(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p) {

}

void HAL::KeyBoardRead( lv_indev_data_t *data) {
    getHal()->keyboard_read(data);
}

void HAL::keyboard_read( lv_indev_data_t *data) {

}

void HAL::MousePointRead(lv_indev_data_t *data) {
    getHal()->mouse_point_read(data);
}

void HAL::mouse_point_read(lv_indev_data_t *data) {

}

DisplayInterface *HAL::getDisplayInterface() {
    return DisplayInterface_;
}

InputDeviceGroup *HAL::getInputDeviceGroup() {
    return InputDeviceGroup_;
}




