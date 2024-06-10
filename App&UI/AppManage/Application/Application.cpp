/**
*********************************************************************
*********
* @project_name :MusicClion
* @file : Application.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/2/7 
*********************************************************************
*********
*/
//

#include "Application.h"

#include "ChipArch/ChipArch/ChipArch.h"
#include "ChipArch/App&UI/AppManage/ApplicationManage/ApplicationManage.h"
void appIconStopCallBack(lv_event_t *e);

Application::Application():app_package_(nullptr) {
    chipArch_= ChipArch::chipArchObtain();
}




