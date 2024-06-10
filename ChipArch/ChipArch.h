/**
*********************************************************************
*********
* @project_name :lvgl
* @file : ChipArch.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/4/11 
*********************************************************************
*********
*/
//

#ifndef LVGL_CHIPARCH_H
#define LVGL_CHIPARCH_H
#include "ChipArch/App&UI/AppManage/Application/AppRegister.h"
#include "ChipArch/App&UI/PageManage/PageManage.h"
#include "ChipArch/App&UI/AppManage/ApplicationManage/ApplicationManage.h"


class ApplicationManage;

class ChipArch {
protected:
    struct Data{
        AppRegister * app_register_;
        ApplicationManage * application_manage_;
        PageManage * page_manage_;
    };
    Data data_;
private:
    static ChipArch* chipArch_;
    ChipArch(){};

public:
    static ChipArch * chipArchObtain();

    void init();

    void freeComponents() const;

    void welcomeLog() const;

    void update();
public:
    ~ChipArch();
    inline   etl::map<String,AppPackage*,max_app_num>& getInstalledAppList(){return data_.app_register_->getInstalledAppList();}

    inline ApplicationManage *getApplicationManage() const{ return data_.application_manage_;};

    inline PageManage * getpageManage() const{return  data_.page_manage_;};

     String installApp(AppPackage * installApp);

    inline bool uninstallApp(AppPackage * appPackage){
        return data_.app_register_->uninstall(appPackage);
    };
    inline void uninstallAppAll()  {
        data_.app_register_->uninstallAllApps();
    };

    inline uint8_t getInstallAppNum() const {
        return data_.app_register_->getInstalledAppNum();
    }
    inline void  creatApp(AppPackage * appPackage)const {
        data_.application_manage_->creatApplication(appPackage);
    };

    inline void  startApp(const char * appName)const {
        data_.application_manage_->startApplication(appName);
    };
    inline void creatStartApp(AppPackage * appPackage)const{
        data_.application_manage_->creatApplication(appPackage);
        data_.application_manage_->startApplication(appPackage->getAppName());
    }
    inline void closeApp(const char * appName)const{
        data_.application_manage_->closeApplication(appName);
    }
    inline void deleteApp(const char * appName)const{
        data_.application_manage_->deleteApplication(appName);
    }
};




#endif //LVGL_CHIPARCH_H
