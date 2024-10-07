/**
*********************************************************************
*********
* @project_name :modm
* @file : app_desk.cpp
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2024/9/30 
*********************************************************************
*********
*/


#include "app_desk.h"
#include "ui/app_desk_ui.hpp"
#include "EmbHardware/HAL.h"

app_desk::~app_desk() {

}

void app_desk::onCreate() {
    fmt::newline_info("OnCreate:{}","Ok");
}

void app_desk::onResume() {
    fmt::newline_info("OnResume:{}","OK");
}

void app_desk::onRunning() {
//    fmt::newline_info("OnRunning {}","Ok");
//    HAL::Delay(500);
}

void app_desk::onRunningBG() {

}

void app_desk::onPause() {

}

void app_desk::onDestroy() {
    fmt::newline_info("onDestroy {}","Ok");
    HAL::Delay(500);
}

app_desk_packer::~app_desk_packer() {

}

std::string app_desk_packer::getAppName() {
    return "desk";
}

void *app_desk_packer::getAppIcon() {
    return APP_PACKER_BASE::getAppIcon();
}

void *app_desk_packer::getCustomData() {
    return APP_PACKER_BASE::getCustomData();
}

void *app_desk_packer::newApp() {
    return new app_desk();
}

void app_desk_packer::deleteApp(void *app) {
    delete static_cast<app_desk *>(app);
}

void *app_desk_packer::newScreenPacker() {
    return new app_desk_ui_packer();
}

void app_desk_packer::deleteScreenPacker(void *pVoid) {
    delete static_cast<app_desk_ui_packer*>(pVoid);
}
