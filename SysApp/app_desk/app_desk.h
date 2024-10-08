/**
*********************************************************************
*********
* @project_name :lvgl
* @file : app_desk.hpp
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2024/9/30 
*********************************************************************
*********
*/


#ifndef MODM_APP_DESK_HPP
#define MODM_APP_DESK_HPP

# include "AppUI/AppManage/Application/app.h"
using namespace ChipArch_;
class app_desk :public APP_BASE{
public:
    ~app_desk() override;

    void onCreate() override;

    void onResume() override;

    void onRunning() override;

    void onRunningBG() override;

    void onPause() override;

    void onDestroy() override;
};

class app_desk_packer:public APP_PACKER_BASE{
public:
    ~app_desk_packer() override;

    std::string getAppName() override;

    void *getAppIcon() override;

    void *getCustomData() override;

    void *newApp() override;

    void deleteApp(void *app) override;

    void *newScreenPacker() override;

    void deleteScreenPacker(void *pVoid) override;
};

#endif //MODM_APP_DESK_HPP
