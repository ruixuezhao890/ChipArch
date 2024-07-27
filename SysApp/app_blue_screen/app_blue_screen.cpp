/**
*********************************************************************
*********
* @project_name :lvgl
* @file : app_blue_screen.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/6/9 
*********************************************************************
*********
*/
//

#include "app_blue_screen.h"



void app_blue_screen::creat() {

}

void app_blue_screen::resume() {

}

void app_blue_screen::running() {
    app_blue_screen_ui_->monitorMessageUpdates();
}

void app_blue_screen::backRunning() {

}

void app_blue_screen::pause() {

}

void app_blue_screen::Destruction() {

}

void app_blue_screen::initPage() {
    app_blue_screen_ui_=new app_blue_screen_ui(getAppName());
    setPage(app_blue_screen_ui_);
}

app_blue_screen::~app_blue_screen() {
    delete app_blue_screen_ui_;
    app_blue_screen_ui_= nullptr;
}




app_blue_screen_package::~app_blue_screen_package() = default;

void *app_blue_screen_package::newApp() {
    setAllowDisplayIcon(false);
    return new app_blue_screen();
}

void app_blue_screen_package::deleteApp(void *app) {
    delete static_cast<app_blue_screen *>(app);
}

const char *app_blue_screen_package::getAppName() {
    return "blue_screen";
}

void *app_blue_screen_package::getAppIcon() {
    return nullptr;
}

void *app_blue_screen_package::getCustomData() {
    return nullptr;
}
