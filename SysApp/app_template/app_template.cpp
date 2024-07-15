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
#if 1
app_template::~app_template() = default;

void app_template::creat() {

}

void app_template::resume() {

}

void app_template::running() {

}

void app_template::backRunning() {

}

void app_template::pause() {

}

void app_template::Destruction() {

}

app_template_package::~app_template_package() = default;

void *app_template_package::newApp() {
    return AppPackage::newApp();
}

void app_template_package::deleteApp(void *app) {
    AppPackage::deleteApp(app);
}

const char *app_template_package::getAppName() {
    return AppPackage::getAppName();
}

void *app_template_package::getAppIcon() {
    return AppPackage::getAppIcon();
}

void *app_template_package::getCustomData() {
    return AppPackage::getCustomData();
}
#endif