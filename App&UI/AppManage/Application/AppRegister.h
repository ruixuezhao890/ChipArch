/**
*********************************************************************
*********
* @project_name :lvgl
* @file : AppRegister.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/4/25 
*********************************************************************
*********
*/
//

#ifndef LVGL_APPREGISTER_H
#define LVGL_APPREGISTER_H
#include "ChipArch/App&UI/AppManage/ApplicationManage/ApplicationManage.h"
#include "Application.h"
#include "AppPackage.h"
#include "ChipArch/vendor/ETL/ETLibrary/include/etl/map.h"

class AppRegister {
private:
    etl::map<String,AppPackage*,max_app_num> _app_packer_list;

public:
    AppRegister()= default;
    ~AppRegister();
    inline   etl::map<String,AppPackage*,max_app_num>& getInstalledAppList(){
            return  _app_packer_list;
        }
    inline std::size_t getInstalledAppNum() { return _app_packer_list.size(); }
    bool install(AppPackage* appPacker, void* framwork = nullptr);
    bool uninstall(AppPackage* appPacker, bool freeMemory = true);
    void uninstallAllApps(bool freeMemory = true);
    bool isAppInstalled(AppPackage* appPacker);
};


#endif //LVGL_APPREGISTER_H
