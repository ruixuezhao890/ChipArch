/**
*********************************************************************
*********
* @project_name :lvgl
* @file : ChipArchChild.h
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

#include "../AppUI/PageManage/PageManage.h"
#include "../AppUI/AppManage/ApplicationManage/ApplicationManage.h"
#include "ChipArch/AppUI/AppManage/Application/AppRegister.h"


class ApplicationManage;

class ChipArch {
protected:
    struct Data{
        AppRegister * app_register_;
        ApplicationManage * application_manage_;
        PageManage * page_manage_;
    };
    Data data_{};
private:
    static ChipArch* chipArch_;
    //todo 微型数据库指针 静态的指针

    ChipArch(){};

public:
    static ChipArch * getOrCreateChipArch();

    void init();

    void freeComponents() const;

    static void welcomeLog() ;

    void update() const;
public:
    ~ChipArch();
    inline   etl::map<String,AppPackage*,max_app_num>& getInstalledAppList() const{return data_.app_register_->getInstalledAppList();}

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
    inline void  creatApp(const char * appName)const {
        data_.application_manage_->creatApplication(getInstalledAppList()[appName]);
    };

    inline void  startApp(const char * appName)const {
        data_.application_manage_->startApplication(appName);
    };
    inline void creatStartApp(const char * appName)const{
        auto app_name=getInstalledAppList()[appName];
        data_.application_manage_->creatApplication(app_name);
        data_.application_manage_->startApplication(appName);
    }
    inline void closeApp(const char * appName)const{
        data_.application_manage_->closeApplication(appName);
    }
    inline void deleteApp(const char * appName)const{
        data_.application_manage_->deleteApplication(appName);
    }
};




#endif //LVGL_CHIPARCH_H
