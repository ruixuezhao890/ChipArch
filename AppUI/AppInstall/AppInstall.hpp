/**
*********************************************************************
*********
* @project_name :lvgl
* @file : AppInstall.h
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2024/6/9 
*********************************************************************
*********
*/
//

#ifndef LVGL_APPINSTALL_H
#define LVGL_APPINSTALL_H
#include "ChipArch/ChipArch.h"
#include "SysApp/app_desk/app_desk.h"

#include "UserApp/app_demo/app_demo.h"
#include "UserApp/app_mi/app_mi.h"
#include "UserApp/app_mi/app_mi.h"
/* Header files locator(Don't remove) */

void chip_arch_install_callback(ChipArch_::ChipArch * chipArch){
   auto demo= chipArch->installApp(new app_demo_packer);
    if (!demo) fmt::newline_info("error {}",demo);

	 
	 auto mi= chipArch->installApp(new app_mi_packer);
	if (!mi) fmt::newline_info("error {}",mi);
	/* Install app locator(Don't remove) */
}
#endif //LVGL_APPINSTALL_H
