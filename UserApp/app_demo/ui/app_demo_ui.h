/**
*********************************************************************
*********
* @project_name :lvgl
* @file : app_demo_ui.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/6/9
*********************************************************************
*********
*/
//

#ifndef LVGL_APP_TEMPLATE_UI_H
#define LVGL_APP_TEMPLATE_UI_H

#include "AppUI/ScreenController/Screen.hpp"
#include "AppUI/AppManage/ApplicationManage/app_manager.h"

class app_demo_widget;

class app_demo_ui:public SCREEN_BASE{
protected:
  app_demo_widget * getWidget();
public:
    app_demo_ui(lv_pm_page_t* lv_pm_page_set);

    void initScreen(lv_obj_t * cont) override;

    void deInitScreen(lv_obj_t * cont) override;
};
class app_demo_widget{
public:

};

class app_demo_ui_packer:public SCREEN_PACKER_BASE{
protected:
    app_demo_widget widget;
public:
    void * newPage(lv_pm_page_t* lv_pm_page_set) override{
        return new app_demo_ui(lv_pm_page_set);
    }
    void deletePage(void * pVoid) override{
        delete static_cast<app_demo_ui *>(pVoid);
    }

    uint8_t getPageId() override{//这里的编号是唯一的，0已经被使用记得更改。范围：0~255
        return 1;
    };

    virtual void * getWidgetStruct() override{
        return (void *)&widget;
    };


};
#endif //LVGL_APP_TEMPLATE_UI_H
