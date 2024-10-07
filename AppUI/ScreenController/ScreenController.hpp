/**
*********************************************************************
*********
* @project_name :micro_snow
* @file : ScreenController.hpp
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2024/10/1 
*********************************************************************
*********
*/


#ifndef MICRO_SNOW_SCREENCONTROLLER_HPP
#define MICRO_SNOW_SCREENCONTROLLER_HPP
#include "ScreenCoupled/pm.h"
#include "AppUI/ScreenController/Screen.hpp"
#include <vector>
class ScreenController {
public:
    ScreenController();

    SCREEN_BASE * creatPage(SCREEN_PACKER_BASE * screenPackerBase);

    static bool openScreen(SCREEN_PACKER_BASE * screenPackerBase);

    static bool backScreen(SCREEN_PACKER_BASE * screenPackerBase);
};


#endif //MICRO_SNOW_SCREENCONTROLLER_HPP
