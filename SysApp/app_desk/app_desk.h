/**
*********************************************************************
*********
* @project_name :lvgl
* @file : app_desk.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/4/12 
*********************************************************************
*********
*/
//

#ifndef LVGL_APP_DESK_H
#define LVGL_APP_DESK_H
#include "ChipArch/SysApp/app_desk/ui/app_desk_ui.h"
# include "ChipArch/App&UI/AppManage/Application/Application.h"


class app_desk: public Application {
protected:
    ap_desk_ui * app_desk_ui_;
public:
    app_desk();

    ~app_desk() override;

    void creat() override;

    void resume() override;

    void running() override;

    void backRunning() override;

    void pause() override;

    void Destruction() override;

    Page *createNewPage() override;

    void deleteOldPage() override;
};

class app_desk_pakger:public AppPackage{
public:
    ~app_desk_pakger() override;

    void *newApp() override;

    void deleteApp(void *app) override;

    const char *getAppName() override;

    void *getAppIcon() override;

    void *getCustomData() override;
};


#endif //LVGL_APP_DESK_H
