/**
*********************************************************************
*********
* @project_name :lvgl
* @file : boot_anim_ascii_ui.cpp
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2024/10/7 
*********************************************************************
*********
*/


#include "boot_anim_ascii_ui.hpp"
boot_anim_ascii_ui::boot_anim_ascii_ui(lv_pm_page_t * set): SCREEN_BASE(set) {

}

void *boot_anim_ascii_ui_packer::newPage(lv_pm_page_t *lv_pm_page_set) {
    return new boot_anim_ascii_ui(lv_pm_page_set);
}

void boot_anim_ascii_ui_packer::deletePage(void *pVoid) {

}

uint8_t boot_anim_ascii_ui_packer::getPageId() {
    return 0;
}

void *boot_anim_ascii_ui_packer::getWidgetStruct() {
    return nullptr;
}

void boot_anim_ascii_ui::initScreen(lv_obj_t *cont) {
    auto obj= lv_obj_create(cont);
    lv_obj_set_size(obj,200,200);
    lv_obj_center(obj);
    auto label= lv_label_create(obj);
    lv_label_set_text(label,"BSP Init waiting...");
    lv_obj_center(label);
}

void boot_anim_ascii_ui::deInitScreen(lv_obj_t *cont) {

}


