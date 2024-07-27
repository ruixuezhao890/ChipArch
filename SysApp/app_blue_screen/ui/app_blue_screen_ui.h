/**
*********************************************************************
*********
* @project_name :lvgl
* @file : app_blue_screen_ui.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/6/9
*********************************************************************
*********
*/
//

#ifndef LVGL_APP_TEMPLATE_UI_H
#define LVGL_APP_TEMPLATE_UI_H
#include "ChipArch/AppUI/PageManage/PageManage.h"
#include "ChipArch/AppUI/AppManage/ApplicationManage/ApplicationManage.h"

class app_blue_screen_ui : public Page{
    //External access to parts that want to change properties should be declared here
    struct widgets{
        Label * error_label;
    };
public:
   widgets widgets_;

    explicit app_blue_screen_ui(const String& band);

    ~app_blue_screen_ui() override;

    void init() override;

    void exit() override;

    void monitorMessageUpdates();
};


#endif //LVGL_APP_TEMPLATE_UI_H
