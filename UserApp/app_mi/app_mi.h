/**
*********************************************************************
*********
* @project_name :lvgl
* @file : app_mi.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/6/9 
*********************************************************************
*********
*/
//

#ifndef LVGL_APP_MI_H
#define LVGL_APP_MI_H
#include "ui/app_mi_ui.h"
#if 1
# include "AppUI/AppManage/Application/app.h"
using namespace ChipArch_;
class app_mi: public APP_BASE {
protected:
    app_mi_widget * getWidget();
public:
    ~app_mi() override;

    void onCreate() override;

    void onResume() override;

    void onRunning() override;

    void onRunningBG() override;

    void onPause() override;

    void onDestroy() override;


};

class app_mi_packer:public APP_PACKER_BASE{
public:
    ~app_mi_packer() override;

    std::string getAppName() override;

    void *getAppIcon() override;

    void *getCustomData() override;

    void *newApp() override;

    void deleteApp(void *app) override;

     void *newScreenPacker() override;

};
#endif
#endif //LVGL_APP_MI_H
