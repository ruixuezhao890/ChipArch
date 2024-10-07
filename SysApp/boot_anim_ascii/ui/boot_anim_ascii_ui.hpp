/**
*********************************************************************
*********
* @project_name :lvgl
* @file : boot_anim_ascii_ui.hpp
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2024/10/7 
*********************************************************************
*********
*/


#ifndef LVGL_BOOT_ANIM_ASCII_UI_HPP
#define LVGL_BOOT_ANIM_ASCII_UI_HPP

#include "AppUI/ScreenController/Screen.hpp"
class boot_anim_ascii_ui: public SCREEN_BASE{
public:
    explicit boot_anim_ascii_ui(lv_pm_page_t* set);

    void initScreen(lv_obj_t *cont) override;

    void deInitScreen(lv_obj_t *cont) override;
};
class app_template_widget{
public:

};
class boot_anim_ascii_ui_packer:public SCREEN_PACKER_BASE{
protected:
    app_template_widget widget;
public:
    void *newPage(lv_pm_page_t *lv_pm_page_set) override;

    void deletePage(void *pVoid) override;

    uint8_t getPageId() override;

    void *getWidgetStruct() override;
};
#endif //LVGL_BOOT_ANIM_ASCII_UI_HPP
