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
//


#include "app_desk.h"
#include "ChipArch/ChipArch/ChipArch.h"
static void desk_call_back(lv_event_t * event);
app_desk::app_desk() :Application(){

}



app_desk::~app_desk() = default;

void app_desk::creat() {
    setAllowBgRunning(true);
}

void app_desk::resume() {
    LV_LOG_USER("resume Running\n");
    app_desk_ui_->drawDeskIcon(chipArch_->getInstalledAppList());
}

void app_desk::running() {
    LV_LOG("desk Running\n");

    lv_indev_data_t getKey{0};
    HAL::KeyBoardRead(&getKey);
    if (getKey.key){
        LV_LOG("getKey:%d\n",getKey.key);
        switch (getKey.key) {
            case 19://右
                app_desk_ui_->scrollRight();
                break;
            case 20://左
                app_desk_ui_->scrollLeft();
                break;
            case 10:
                app_desk_ui_->scrollOpen();
                break;
            default:
                break;
        }
    }

    HAL::Delay(500);
}

void app_desk::backRunning() {
    LV_LOG("back app_setting Running\n");
    usleep(500);
    if (chipArch_->getApplicationManage()->getCreateAppNum()==1){
        LV_LOG("back to desk\n");
        chipArch_->getApplicationManage()->startApplication(this->getAppName());

    }
}

void app_desk::pause() {

}

void app_desk::Destruction() {

}

Page *app_desk::createNewPage() {
    page_=app_desk_ui_= new ap_desk_ui(this->getAppName());
    return page_;
}



void app_desk::deleteOldPage() {
    lv_obj_del(page_->getNowPage());
}

app_desk_pakger::~app_desk_pakger() = default;

void *app_desk_pakger::newApp() {
    return new app_desk();
}

void app_desk_pakger::deleteApp(void *app) {
   delete (app_desk *)app ;
}

const char *app_desk_pakger::getAppName() {
    return home_page_name.c_str();
}

void *app_desk_pakger::getAppIcon() {
    return nullptr;
}

void *app_desk_pakger::getCustomData() {
    return AppPackage::getCustomData();
}



void desk_call_back(lv_event_t * event){
    auto getEvent= lv_event_get_code(event);
    if (getEvent==LV_EVENT_CLICKED){
        uint16_t num=getEvent;
        LV_LOG("num:%d\n",num);
    }
    if (getEvent==LV_EVENT_SCROLL_BEGIN){
        uint16_t num=getEvent;
        LV_LOG("num:%d\n",num);
    }

}



