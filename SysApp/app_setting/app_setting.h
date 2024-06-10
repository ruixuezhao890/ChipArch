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

#include "ChipArch/App&UI/AppManage/Application/Application.h"
#include "ChipArch/SysApp/app_setting/ui/app_setting_ui.h"

class app_setting :public Application{
   app_setting_ui* app_setting_ui_;
public:
    app_setting();

    app_setting(Application * band_app);

    ~app_setting() override;

    void creat() override;

    void resume() override;

    void running() override;

    void backRunning() override;

    void pause() override;

    void Destruction() override;

    Page *createNewPage() override;

    void deleteOldPage() override;

};
class app_setting_pakger:public AppPackage{
public:
    ~app_setting_pakger() override;

    void *newApp() override;

    void deleteApp(void *app) override;

    const char *getAppName() override;

    void *getAppIcon() override;

    void *getCustomData() override;


};

#endif //LVGL_APP_SETTING_H
