/**
*********************************************************************
*********
* @project_name :lvgl
* @file : setting_ui.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/4/13 
*********************************************************************
*********
*/
//

#include "app_setting_ui.h"
#include "ChipArch/ChipArch/ChipArch.h"

app_setting_ui::app_setting_ui(const String & band_page) : Page(band_page) {

}
void app_setting_ui::init() {
    initializeSettingUI();
}

void app_setting_ui::exit() {

}

bool app_setting_ui::getScreenOrientation() {
    return screen_orientation_;
}

void app_setting_ui::initializeSettingUI() {

    auto cont=new Container(this->getNowPage());
    cont->set_size(320,240);
    cont->clear_flag(LV_OBJ_FLAG_SCROLLABLE);
    cont->set_style_opa(255,LV_PART_MAIN|LV_STATE_DEFAULT);

   auto  menu=new Menu(*cont);
//        menu->set_style_bg_color(lv_color_hex(0x3C3C3C),LV_PART_MAIN|LV_STATE_DEFAULT);
//        menu->set_mode_root_back_btn(LV_MENU_ROOT_BACK_BTN_ENABLED);
//        menu->add_event_cb(backBtnCallBack,LV_EVENT_CLICKED,(void *)menu);
//        menu->set_size(cont->get_width(),cont->get_height());
//        menu->set_user_data(this);
//        menu->center();
    menu->set_style_bg_color(lv_color_hex(0x3C3C3C), LV_PART_MAIN | LV_STATE_DEFAULT);
    menu->set_mode_root_back_btn(LV_MENU_ROOT_BACK_BTN_ENABLED);
    menu->set_user_data((void *)this);
    lv_obj_add_event_cb(menu->raw_ptr(), backBtnCallBack, LV_EVENT_CLICKED, menu->raw_ptr());
    menu->set_size(cont->get_width(),cont->get_height());
    menu->center();
//    lv_obj_clear_flag(now_page_, LV_OBJ_FLAG_SCROLLABLE);
//    lv_obj_set_style_opa(now_page_, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
//
//    draw_setting_attribute_.setting_menu = lv_menu_create(now_page_);
//    lv_obj_t * menu = draw_setting_attribute_.setting_menu;
//
//    lv_obj_set_style_bg_color(menu, lv_color_hex(0x3C3C3C), LV_PART_MAIN | LV_STATE_DEFAULT);
//    lv_menu_set_mode_root_back_btn(menu, LV_MENU_ROOT_BACK_BTN_ENABLED);
//
//    lv_obj_set_user_data(menu, this);  // assuming lv_obj_set_user_data is used
//    lv_obj_add_event_cb(menu, backBtnCallBack, LV_EVENT_CLICKED, menu);
//
//    lv_obj_set_size(menu, lv_obj_get_width(now_page_), lv_obj_get_height(now_page_));
//    lv_obj_center(menu);
}

void app_setting_ui::backBtnCallBack(lv_event_t *e) {
    lv_obj_t * obj = lv_event_get_target(e);
    auto chip=ChipArch::chipArchObtain();
    auto menu =( lv_obj_t *) lv_event_get_user_data(e);
    auto get_user_data=(app_setting_ui *) lv_obj_get_user_data(menu);
    if(lv_menu_back_btn_is_root(menu, obj)) {
        chip->startApp(home_page_name.c_str());
        chip->closeApp(get_user_data->getNowAppName().c_str());
    }
}

app_setting_ui::~app_setting_ui() {

}

String & app_setting_ui::getNowAppName() {
    return now_app_name_;
}




