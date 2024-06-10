/**
*********************************************************************
*********
* @project_name :lvgl
* @file : app_template_ui.h
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
#include "ChipArch/App&UI/PageManage/PageManage.h"
#include "ChipArch/App&UI/AppManage/ApplicationManage/ApplicationManage.h"

class app_template_ui : public Page{
protected:

public:
    app_template_ui(const String& band);

    ~app_template_ui() override;

    void init() override;

    void exit() override;

    bool getScreenOrientation() override;

    String &getNowAppName() override;
};


#endif //LVGL_APP_TEMPLATE_UI_H
