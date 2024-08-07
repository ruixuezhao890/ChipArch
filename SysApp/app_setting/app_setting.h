/**
*********************************************************************
*********
* @project_name :lvgl
* @file : app_setting.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/4/12
*********************************************************************
*********
*/
//

#ifndef LVGL_APP_SETTING_H
#define LVGL_APP_SETTING_H

#include "ChipArch/AppUI/AppManage/Application/Application.hpp"
#include "ChipArch/SysApp/app_setting/ui/app_setting_ui.h"

class app_setting :public Application{
   app_setting_ui* app_setting_ui_{};
public:
    app_setting();

    ~app_setting() override;

    void initPage() override;

    void creat() override;

    void resume() override;

    void running() override;

    void backRunning() override;

    void pause() override;

    void Destruction() override;
};
class app_setting_package: public AppPackage{
public:
    ~app_setting_package() override;

    void *newApp() override;

    void deleteApp(void *app) override;

    const char *getAppName() override;

    void *getAppIcon() override;

    void *getCustomData() override;


};

#endif //LVGL_APP_SETTING_H
