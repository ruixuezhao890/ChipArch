/**
*********************************************************************
*********
* @project_name :lvgl
* @file : test_app.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/5/3 
*********************************************************************
*********
*/
//

#include "test_app.h"
#include "ChipArch/SysApp/app_setting/assets/icon_app_settings.hpp"
test_app::~test_app() {

}

void test_app::creat() {

}

void test_app::resume() {

}

void test_app::running() {

}

void test_app::backRunning() {

}

void test_app::pause() {

}

void test_app::Destruction() {

}

Page *test_app::createNewPage() {
    return nullptr;
}

void test_app::deleteOldPage() {
    lv_obj_del(page_->getNowPage());
}


test_app_packer1::~test_app_packer1() {

}

void *test_app_packer1::newApp() {
    return new test_app();
}

void test_app_packer1::deleteApp(void *app) {
    AppPackage::deleteApp(app);
}

const char *test_app_packer1::getAppName() {
    return "test1";
}

void *test_app_packer1::getAppIcon() {
    return AppPackage::getAppIcon();
}

void *test_app_packer1::getCustomData() {
    return AppPackage::getCustomData();
}

test_app_packer2::~test_app_packer2() {

}

void *test_app_packer2::newApp() {
    return new test_app();
}

void test_app_packer2::deleteApp(void *app) {
    AppPackage::deleteApp(app);
}

const char *test_app_packer2::getAppName() {
    return "test2";
}

void *test_app_packer2::getAppIcon() {
    return AppPackage::getAppIcon();
}

void *test_app_packer2::getCustomData() {
    return AppPackage::getCustomData();
}

test_app_packer3::~test_app_packer3() {

}

void *test_app_packer3::newApp() {
    return AppPackage::newApp();
}

void test_app_packer3::deleteApp(void *app) {
    AppPackage::deleteApp(app);
}

const char *test_app_packer3::getAppName() {
    return "test3";
}

void *test_app_packer3::getAppIcon() {
    return (void *) image_data_icon_app_settings;
}

void *test_app_packer3::getCustomData() {
    return AppPackage::getCustomData();
}

test_app_packer4::~test_app_packer4() {

}

void *test_app_packer4::newApp() {
    return AppPackage::newApp();
}

void test_app_packer4::deleteApp(void *app) {
    AppPackage::deleteApp(app);
}

const char *test_app_packer4::getAppName() {
    return "test4";
}

void *test_app_packer4::getAppIcon() {
    return AppPackage::getAppIcon();
}

void *test_app_packer4::getCustomData() {
    return AppPackage::getCustomData();
}


