/**
*********************************************************************
*********
* @project_name :lvgl
* @file : app_mi_ui.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/6/9
*********************************************************************
*********
*/
//

#include "app_mi_ui.h"

app_mi_ui::app_mi_ui(lv_pm_page_t *lv_pm_page_set): SCREEN_BASE(lv_pm_page_set) {

}

 app_mi_widget * app_mi_ui::getWidget() {
    return static_cast<app_mi_widget*>(getScreenPacker()->getWidgetStruct());
}
void app_mi_ui::initScreen(lv_obj_t *cont) {

}

void app_mi_ui::deInitScreen(lv_obj_t *cont) {

}