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

void app_template::initPage() {
    app_template_ui_=new app_template_ui(getAppName());
    setPage(app_template_ui_);
}

app_template::~app_template() {
    delete app_template_ui_;
    app_template_ui_= nullptr;
}


app_template_package::~app_template_package() = default;

void *app_template_package::newApp() {
    return new app_template();
}

void app_template_package::deleteApp(void *app) {
    delete static_cast<app_template *>(app);
}

const char *app_template_package::getAppName() {
    return "template";
}

void *app_template_package::getAppIcon() {
    return nullptr;
}

void *app_template_package::getCustomData() {
    return nullptr;
}
