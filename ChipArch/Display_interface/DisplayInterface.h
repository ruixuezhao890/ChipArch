/**
*********************************************************************
*********
* @project_name :lvgl
* @file : DisplayInterface.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/5/9 
*********************************************************************
*********
*/
//

#ifndef LVGL_DISPLAYINTERFACE_H
#define LVGL_DISPLAYINTERFACE_H
#include "ChipArch/ChipArchConfig.h"
#include "ChipArch/App&UI/utils/lvglpp/core/display.h"

using namespace lvgl::core;
class DisplayInterface: public Display{
protected:
    const static lv_coord_t hor_res_=MY_DISP_HOR_RES;
    const static lv_coord_t ver_res_=MY_DISP_VER_RES;
    const static uint32_t fb_size=hor_res_*10;
public:
    DisplayInterface();
    void flush(const lv_area_t *area, lv_color_t *color_map) override;
};


#endif //LVGL_DISPLAYINTERFACE_H
