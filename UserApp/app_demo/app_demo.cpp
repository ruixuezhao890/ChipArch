/**
*********************************************************************
*********
* @project_name :lvgl
* @file : app_demo.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/6/9 
*********************************************************************
*********
*/
//

#include "app_demo.h"
#include "EmbHardware/HAL.h"
app_demo_widget *app_demo::getWidget() {
    return static_cast<app_demo_widget*>(getScreenPacker()->getWidgetStruct());
}
app_demo::~app_demo() {

}

void app_demo::onCreate() {
    APP_BASE::onCreate();
}

void app_demo::onResume() {
    APP_BASE::onResume();
}

void app_demo::onRunning() {

}

void app_demo::onRunningBG() {
    fmt::newline_info("demo BG_running");
    HAL::Delay(500);
}

void app_demo::onPause() {
    fmt::newline_info("demo OnPause");
    HAL::Delay(500);
}

void app_demo::onDestroy() {
    fmt::newline_info("demo onDestroy");
    HAL::Delay(500);
}


app_demo_packer::~app_demo_packer() = default;


std::string app_demo_packer::getAppName() {
    return "demo";
}

void *app_demo_packer::getAppIcon() {
    return APP_PACKER_BASE::getAppIcon();
}

void *app_demo_packer::getCustomData() {
    return APP_PACKER_BASE::getCustomData();
}

void *app_demo_packer::newApp() {
    return new app_demo();
}

void app_demo_packer::deleteApp(void *app) {
    delete static_cast<app_demo *>(app);
}

void *app_demo_packer::newScreenPacker() {
    return new app_demo_ui_packer();
}

void app_demo_packer::deleteScreenPacker(void *pVoid) {
    delete static_cast<app_demo_ui_packer*>(pVoid);
}


