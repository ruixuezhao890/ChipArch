/**
*********************************************************************
*********
* @project_name :lvgl
* @file : app_setting.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/4/12
*********************************************************************
*********
*/
//

#include "app_setting.h"
#include "ui/app_setting_ui.h"
#include "ChipArch/SysApp/app_setting/assets/icon_app_settings.hpp"
app_setting::app_setting():Application() {


}

app_setting::~app_setting() = default;



void app_setting::creat() {
    app_setting_ui_=new app_setting_ui(getAppName());
    setPage(app_setting_ui_);
    setAllowBgRunning(true);

}

void app_setting::resume() {


}

void app_setting::running() {
   spdlog::debug("app_setting Running\n");
   HAL::Delay(500);
}

void app_setting::backRunning() {
    spdlog::debug("back app_setting Running\n");
    HAL::Delay(500);
}

void app_setting::pause() {

}

void app_setting::Destruction() {

}

app_setting_package::~app_setting_package() = default;

void *app_setting_package::newApp() {
    return new app_setting();
}

void app_setting_package::deleteApp(void *app) {
   delete (app_setting *)app;
}

const char *app_setting_package::getAppName() {
    return "setting_app";
}

void *app_setting_package::getAppIcon() {
    return (void *)image_data_icon_app_settings;
}

void *app_setting_package::getCustomData() {
    return AppPackage::getCustomData();
}



