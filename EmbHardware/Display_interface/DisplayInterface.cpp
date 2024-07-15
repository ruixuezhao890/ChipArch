/**
*********************************************************************
*********
* @project_name :lvgl
* @file : DisplayInterface.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/5/9 
*********************************************************************
*********
*/
//

#include "DisplayInterface.h"
#include "../../EmbHardware/HAL.h"

#if COMPUTER
#include "ChipArch/EmbHardware/Solitude/Solitude.h"
#endif
void DisplayInterface::flush(const lv_area_t *area, lv_color_t *color_map) {
    HAL::getHal()->display(this->raw_ptr()->driver,area,color_map);

}

DisplayInterface::DisplayInterface(): Display(hor_res_,ver_res_,fb_size) {
    this->update_driver();
}
