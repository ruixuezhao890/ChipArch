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
#include "ChipArch/AppUI/PageManage/PageManage.h"
#include "ChipArch/AppUI/AppManage/ApplicationManage/ApplicationManage.h"

class app_template_ui : public Page{
protected:

public:
    explicit app_template_ui(const String& band);

    ~app_template_ui() override;

    void init() override;

    void exit() override;
};


#endif //LVGL_APP_TEMPLATE_UI_H
