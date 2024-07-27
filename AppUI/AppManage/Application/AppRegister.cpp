/**
*********************************************************************
*********
* @project_name :lvgl
* @file : AppRegister.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/4/25 
*********************************************************************
*********
*/
//

#include "AppRegister.h"

AppRegister::~AppRegister() = default;

bool AppRegister::install(AppPackage *appPacker, void *framwork) {
    if (appPacker == nullptr)
        return false;

    if (isAppInstalled(appPacker))
        return false;

    appPacker->setWorkShop(framwork);

    /* Push into list */
   _app_packer_list[appPacker->getAppName()]=appPacker->getAddr();

    return true;
}

bool AppRegister::uninstall(AppPackage *appPacker, bool freeMemory) {
    if (appPacker == nullptr)
        return false;
    for (auto& iter :_app_packer_list)
    {
        if (iter.first == appPacker->getAppName())
        {
            /* Free parker's memory */
            if (freeMemory)
                delete iter.second;

            /* Remove it from the list */
            _app_packer_list.erase(iter.first);
            return true;
        }
    }
    return false;
}

void AppRegister::uninstallAllApps(bool freeMemory) {
    /* Free all the packers' memory */
    if (freeMemory)
    {
        for (const auto& i : _app_packer_list)
            delete i.second;
    }

    /* Clear the list */
    _app_packer_list.clear();
}

bool AppRegister::isAppInstalled(AppPackage *appPacker) {
    if (appPacker == nullptr)
        return false;

    /* Iterate the shit out */
    for (const auto& i : _app_packer_list)
    {
        if (i.first == appPacker->getAppName())
            return true;
    }
    return false;
}
