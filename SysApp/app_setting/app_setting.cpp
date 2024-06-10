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
#include "ChipArch/ChipArch/ChipArch.h"
#include "ChipArch/SysApp/app_setting/assets/icon_app_settings.hpp"
app_setting::app_setting():Application() {


}

app_setting::~app_setting() {

}



void app_setting::creat() {
    setAllowBgRunning(true);

}

void app_setting::resume() {


}

void app_setting::running() {
   LV_LOG("app_setting Running\n");
    usleep(500);
}

void app_setting::backRunning() {
    LV_LOG("back app_setting Running\n");
    usleep(500);
}

void app_setting::pause() {

}

void app_setting::Destruction() {

}

Page *app_setting::createNewPage() {
    page_=app_setting_ui_= new app_setting_ui(getAppName());
    return page_;
}

void app_setting::deleteOldPage() {
    lv_obj_del(page_->getNowPage());
}

app_setting_pakger::~app_setting_pakger() {

}

void *app_setting_pakger::newApp() {
    return new app_setting();
}

void app_setting_pakger::deleteApp(void *app) {
   delete (app_setting *)app;
}

const char *app_setting_pakger::getAppName() {
    return "setting_app";
}

void *app_setting_pakger::getAppIcon() {
    return (void *)image_data_icon_app_settings;
}

void *app_setting_pakger::getCustomData() {
    return AppPackage::getCustomData();
}



