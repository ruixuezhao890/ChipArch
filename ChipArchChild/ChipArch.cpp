/**
*********************************************************************
*********
* @project_name :lvgl
* @file : ChipArchChild.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/4/11 
*********************************************************************
*********
*/
//

#include "ChipArch.h"
#include "ChipArch/AppUI/AppManage/Application/Application.hpp"


ChipArch* ChipArch::chipArch_= nullptr;
const char * version="1.0";
static const char* chip_arch_logo = R"(
    CCCCC  H   H IIIII  PPPPP AAAAA  RRRRR  CCCCC  H   H
    C      HHHHH   I    P   P A   A  R   R  C      HHHHH
    C      H   H   I    PPPPP AAAAA  RRRRR  C      H   H
    CCCCC  H   H IIIII  P     A   A  R   R  CCCCC  H   H
)";
ChipArch *ChipArch::chipArchObtain() {
    if (chipArch_){
        return chipArch_;
    }
    chipArch_=new ChipArch();
    chipArch_->data_.app_register_= nullptr;
    chipArch_->data_.application_manage_= nullptr;
    chipArch_->data_.page_manage_= nullptr;
    return chipArch_;
}

void ChipArch::freeComponents() const {
        delete data_.app_register_;
        delete data_.application_manage_;
        delete data_.page_manage_;
   LV_LOG("ChipArchChild destroyed");
   LV_LOG("bye :)");
}

void ChipArch:: init() {
    // todo 日志库输出信息 ：正在初始化
    spdlog::info("ChipArch Initializing\n");
    if (data_.application_manage_){
       // todo 串口或任意设备输出信息
        spdlog::info("ChipArch ReInitializing\n");
       freeComponents();
    }
//    SentinelLog::log::initLog();
    data_.app_register_=new AppRegister();
    data_.application_manage_=new ApplicationManage();
    welcomeLog();
}

void ChipArch::welcomeLog() const {
    printf("%s", chip_arch_logo);
    printf("\n- @author zen3\n");
    printf("- @version:%s\n",version);
    printf("- @build at " __TIME__ " " __DATE__ "\n\n");
}

ChipArch::~ChipArch() {
    freeComponents();
   LV_LOG("ChipArch destroyed");
   LV_LOG("bye :)");
}

void ChipArch::update() {
    lv_timer_handler();
    data_.application_manage_->applicationUpData();
    HAL::Delay(LVGL_UPDATA_TIME);

}

String ChipArch::installApp(AppPackage *installApp) {
    if (data_.app_register_->install(installApp, this)){
        return  installApp->getAppName();
    }
    return " ";
}



