/**
*********************************************************************
*********
* @project_name :lvgl
* @file : app_desk.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/4/12
*********************************************************************
*********
*/

#include "app_desk.h"
#include "ChipArch/ChipArchChild/ChipArch.h"



app_desk::app_desk() : Application(){

}

app_desk::~app_desk() = default;

void app_desk::creat() {
    app_desk_ui_=new app_desk_ui(getAppName());
    setPage(app_desk_ui_);
    setAllowBgRunning(true);
}

void app_desk::resume() {
    spdlog::info("resume Running\n");
    app_desk_ui_->drawDeskIcon();
}

void app_desk::running() {
    spdlog::info("desk Running\n");

    lv_indev_data_t getKey{};
    HAL::KeyBoardRead(&getKey);

    if (getKey.key) {
        spdlog::info("getKey: %d\n", getKey.key);
        switch (getKey.key) {
            case 19: // Right
                app_desk_ui_->scrollRight();
                break;
            case 20: // Left
                app_desk_ui_->scrollLeft();
                break;
            case 10: // Select
                app_desk_ui_->scrollOpen();
                break;
            default:
                break;
        }
    }

    HAL::Delay(500);
}

void app_desk::backRunning() {
    spdlog::info("back app_setting Running\n");
    HAL::Delay(500);

    if (ChipArch::getOrCreateChipArch()->getApplicationManage()->getCreateAppNum() == 1) {
        spdlog::info("back to desk\n");
        ChipArch::getOrCreateChipArch()->getApplicationManage()->startApplication(this->getAppName());
    }
}

void app_desk::pause() {}

void app_desk::Destruction() {}

app_desk_package::~app_desk_package() = default;

void* app_desk_package::newApp() {
    return new app_desk();
}

void app_desk_package::deleteApp(void* app) {
    delete static_cast<app_desk*>(app);
}

const char* app_desk_package::getAppName() {
    return home_page_name.c_str();
}

void* app_desk_package::getAppIcon() {
    return nullptr;
}

void* app_desk_package::getCustomData() {
    return AppPackage::getCustomData();
}
