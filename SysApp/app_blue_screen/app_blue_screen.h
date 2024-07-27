/**
*********************************************************************
*********
* @project_name :lvgl
* @file : app_blue_screen.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/6/9 
*********************************************************************
*********
*/
//

#ifndef LVGL_APP_TEMPLATE_H
#define LVGL_APP_TEMPLATE_H
#include "ui/app_blue_screen_ui.h"
#if 1
# include "ChipArch/AppUI/AppManage/Application/Application.hpp"

class app_blue_screen: public Application{
protected:
    app_blue_screen_ui * app_blue_screen_ui_;
public:


    ~app_blue_screen() override;

    void initPage() override;

    void creat() override;

    void resume() override;

    void running() override;

    void backRunning() override;

    void pause() override;

    void Destruction() override;

};

class app_blue_screen_package:public AppPackage{
public:
    ~app_blue_screen_package() override;

    void *newApp() override;

    void deleteApp(void *app) override;

    const char *getAppName() override;

    void *getAppIcon() override;

    void *getCustomData() override;
};
#endif
#endif //LVGL_APP_TEMPLATE_H
