/**
*********************************************************************
*********
* @project_name :lvgl
* @file : app_template.h
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
#include "ui/app_template_ui.h"
# include "ChipArch/App&UI/AppManage/Application/Application.h"

class app_template: public Application{
protected:
    app_template_ui * app_template_ui_;
public:
    ~app_template() override;

    void creat() override;

    void resume() override;

    void running() override;

    void backRunning() override;

    void pause() override;

    void Destruction() override;

    Page *createNewPage() override;

    void deleteOldPage() override;
};

class app_template_package:public AppPackage{
public:
    ~app_template_package() override;

    void *newApp() override;

    void deleteApp(void *app) override;

    const char *getAppName() override;

    void *getAppIcon() override;

    void *getCustomData() override;
};

#endif //LVGL_APP_TEMPLATE_H
