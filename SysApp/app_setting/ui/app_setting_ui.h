/**
*********************************************************************
*********
* @project_name :lvgl
* @file : setting_ui.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/4/13 
*********************************************************************
*********
*/
//

#ifndef LVGL_APP_SETTING_UI_H
#define LVGL_APP_SETTING_UI_H
//#include "ChipArch/ChipArch/Input_device_interface/InputDeviceInterface.h"
#include "ChipArch/App&UI/PageManage/PageManage.h"

class app_setting_ui: public Page{
public:
    app_setting_ui(const String &);

    ~app_setting_ui() override;

    void init() override;

    void exit() override;

    bool getScreenOrientation() override;

    String & getNowAppName() override;


protected:
    struct Draw{
//        lv_obj_t * setting_menu;
//        Menu  setting_menu;
    };
    Draw draw_setting_attribute_;

    void initializeSettingUI();

    static void backBtnCallBack(lv_event_t *e);
};


#endif //LVGL_APP_SETTING_UI_H
