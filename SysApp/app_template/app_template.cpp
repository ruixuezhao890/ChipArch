/**
*********************************************************************
*********
* @project_name :lvgl
* @file : app_template.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/6/9 
*********************************************************************
*********
*/
//

#include "app_template.h"
#include "EmbHardware/HAL.h"

app_template_widget *app_template::getWidget() {
    return static_cast<app_template_widget*>(getScreenPacker()->getWidgetStruct());
}
app_template::~app_template() {

}

void app_template::onCreate() {
    APP_BASE::onCreate();
}

void app_template::onResume() {
    APP_BASE::onResume();
}

void app_template::onRunning() {
    APP_BASE::onRunning();
}

void app_template::onRunningBG() {
    APP_BASE::onRunningBG();
}

void app_template::onPause() {
    APP_BASE::onPause();
}

void app_template::onDestroy() {
    APP_BASE::onDestroy();
}


app_template_packer::~app_template_packer() = default;


std::string app_template_packer::getAppName() {
    return "app_template";
}

void *app_template_packer::getAppIcon() {
    return APP_PACKER_BASE::getAppIcon();
}

void *app_template_packer::getCustomData() {
    return APP_PACKER_BASE::getCustomData();
}

void *app_template_packer::newApp() {
    return new app_template();
}

void app_template_packer::deleteApp(void *app) {
    delete static_cast<app_template *>(app);
}

void *app_template_packer::newScreenPacker() {
    return (void *)new app_template_ui_packer();
}

void app_template_packer::deleteScreenPacker(void *pVoid) {
     delete static_cast<app_template_ui_packer*>(pVoid);
}

