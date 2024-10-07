/**
*********************************************************************
*********
* @project_name :micro_snow
* @file : app_desk_ui.hpp
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2024/10/3 
*********************************************************************
*********
*/


#ifndef MICRO_SNOW_APP_DESK_UI_HPP
#define MICRO_SNOW_APP_DESK_UI_HPP

#include "EmbHardware/HAL.h"
#include "AppUI/ScreenController/Screen.hpp"

class app_desk_widget;

class app_desk_ui:public SCREEN_BASE{
public:
    app_desk_widget * getWidget();//对控件访问的接口。里面 所有成员都是public的

    app_desk_ui(lv_pm_page_t* lv_pm_page_set);

    void initScreen(lv_obj_t * cont) override;

    void deInitScreen(lv_obj_t * cont) override;
};
class app_desk_widget{
public:
    lv_obj_t * app_name_label;
};

class app_desk_ui_packer:public SCREEN_PACKER_BASE{
protected:
    app_desk_widget widget{};
public:
    void * newPage(lv_pm_page_t* lv_pm_page_set) override{
        return new app_desk_ui(lv_pm_page_set);
    }
    void deletePage(void * pVoid) override{
        delete static_cast<app_desk_ui *>(pVoid);
    }

    uint8_t getPageId() override{
        return 0;
    };

    virtual void * getWidgetStruct() override{
        return (void *)&widget;
    };
};

#endif //MICRO_SNOW_APP_DESK_UI_HPP
