/**
*********************************************************************
*********
* @project_name :lvgl
* @file : HAL.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/4/12 
*********************************************************************
*********
*/
//

#ifndef LVGL_HAL_H
#define LVGL_HAL_H

#include "lvgl/lvgl.h"
#include "ChipArch/vendor/OtherLib/WString.h"
#include "ChipArch/ChipArch/Display_interface/DisplayInterface.h"
#include "ChipArch/ChipArch/Input_device_interface/InputDeviceInterface.h"

class HAL {
private:
    static HAL * hal_;
protected:
    static DisplayInterface * DisplayInterface_;

    static InputDeviceGroup * InputDeviceGroup_;

public:
    HAL()=default;

    static HAL * getHal();

    static void initInputDevice(char letter);

    static bool check();

    static void destroy();

    static DisplayInterface *getDisplayInterface();

    static InputDeviceGroup *getInputDeviceGroup();

    static String Type(){ return getHal()->type();};
    virtual String type(){ return "Base";};

    virtual void init(){};

    static bool Inject(HAL * inject,char letter='0');//注入

    static void Delay(unsigned long milliseconds) ;
    virtual void delay(unsigned long milliseconds);

    static void Display(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p) ;
    virtual void display(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p);

    static void KeyBoardRead(lv_indev_data_t * data);
    virtual void keyboard_read( lv_indev_data_t * data);

    static void  MousePointRead(lv_indev_data_t * data);
    virtual void mouse_point_read( lv_indev_data_t * data);
};


#endif //LVGL_HAL_H
