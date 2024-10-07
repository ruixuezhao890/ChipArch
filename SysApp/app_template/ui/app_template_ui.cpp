/**
*********************************************************************
*********
* @project_name :lvgl
* @file : app_template_ui.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/6/9
*********************************************************************
*********
*/
//

#include "app_template_ui.h"

app_template_ui::app_template_ui(lv_pm_page_t *lv_pm_page_set): SCREEN_BASE(lv_pm_page_set) {

}

 app_template_widget * app_template_ui::getWidget() {
    return static_cast<app_template_widget*>(getScreenPacker()->getWidgetStruct());
}
void app_template_ui::initScreen(lv_obj_t *cont) {

}

void app_template_ui::deInitScreen(lv_obj_t *cont) {

}