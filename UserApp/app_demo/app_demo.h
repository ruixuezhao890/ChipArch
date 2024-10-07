/**
*********************************************************************
*********
* @project_name :lvgl
* @file : app_demo.h
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
#include "ui/app_demo_ui.h"
#if 1
# include "AppUI/AppManage/Application/app.h"
using namespace ChipArch_;
class app_demo: public APP_BASE {
protected:
    app_demo_widget * getWidget();
public:
    ~app_demo() override;

    void onCreate() override;

    void onResume() override;

    void onRunning() override;

    void onRunningBG() override;

    void onPause() override;

    void onDestroy() override;


};

class app_demo_packer:public APP_PACKER_BASE{
public:
    ~app_demo_packer() override;

    std::string getAppName() override;

    void *getAppIcon() override;

    void *getCustomData() override;

    void *newApp() override;

    void deleteApp(void *app) override;

     void *newScreenPacker() override;

    void deleteScreenPacker(void *pVoid) override;

};
#endif
#endif //LVGL_APP_TEMPLATE_H
