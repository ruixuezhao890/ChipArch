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

Page *app_template::createNewPage() {
    page_=app_template_ui_= new app_template_ui(this->getAppName());
    return page_;
}

void app_template::deleteOldPage() {

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
