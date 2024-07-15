/**
*********************************************************************
*********
* @project_name :chip_arch_demo
* @file : Bridege.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/6/23 
*********************************************************************
*********
*/
//

#include "Bridege.h"
#include "../ChipArch/AppUI/AppInstall/AppInstall.hpp"
#include "../../../EmbHardware/Ethan//Ethan.h"
void step() {
    HAL::Inject(new Ethan);

    auto chipArchObtain= ChipArch::chipArchObtain();
    chipArchObtain->init();
    auto desk_package=new app_desk_pakger;
    chipArchObtain->installApp(desk_package);
//    chip_arch_install_callback(chipArchObtain);
    chipArchObtain->creatStartApp(desk_package);
    
}


void loop() {
    auto chipArchObtain= ChipArch::chipArchObtain();
    for(;;){
        chipArchObtain->update();
        HAL::UpDate();
        HAL::Delay(5);
    }
}
