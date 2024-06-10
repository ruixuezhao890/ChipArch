/**
*********************************************************************
*********
* @project_name :lvgl
* @file : AppInstall.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/6/9 
*********************************************************************
*********
*/
//

#ifndef LVGL_APPINSTALL_H
#define LVGL_APPINSTALL_H
#include "ChipArch/ChipArch/ChipArch.h"
#include "ChipArch/SysApp/app_setting/app_setting.h"
#include "ChipArch/SysApp/app_desk/app_desk.h"
#include "ChipArch/UserApp/testApp/test_app.h"
/* Header files locator(Don't remove) */

void chip_arch_install_callback(ChipArch * chipArch){
     chipArch->installApp(new app_setting_pakger);
     chipArch->installApp(new test_app_packer1);
     chipArch->installApp(new test_app_packer2);
     chipArch->installApp(new test_app_packer3);
     chipArch->installApp(new test_app_packer4);
     /* Install app locator(Don't remove) */
}
#endif //LVGL_APPINSTALL_H
