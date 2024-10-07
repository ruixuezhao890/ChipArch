/**
*********************************************************************
*********
* @project_name :lvgl
* @file : app_mi.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/6/9 
*********************************************************************
*********
*/
//

#include "app_mi.h"

app_mi_widget *app_mi::getWidget() {
    return static_cast<app_mi_widget*>(getScreenPacker()->getWidgetStruct());
}
app_mi::~app_mi() {

}

void app_mi::onCreate() {
    APP_BASE::onCreate();
}

void app_mi::onResume() {
    APP_BASE::onResume();
}

void app_mi::onRunning() {
    APP_BASE::onRunning();
}

void app_mi::onRunningBG() {
    APP_BASE::onRunningBG();
}

void app_mi::onPause() {
    APP_BASE::onPause();
}

void app_mi::onDestroy() {
    APP_BASE::onDestroy();
}


app_mi_packer::~app_mi_packer() = default;


std::string app_mi_packer::getAppName() {
    return "mi";
}

void *app_mi_packer::getAppIcon() {
    return APP_PACKER_BASE::getAppIcon();
}

void *app_mi_packer::getCustomData() {
    return APP_PACKER_BASE::getCustomData();
}

void *app_mi_packer::newApp() {
    return new app_mi();
}

void app_mi_packer::deleteApp(void *app) {
    delete static_cast<app_mi *>(app);
}

void *app_mi_packer::newScreenPacker() {
    return (void *)new app_mi_ui_packer();
}


