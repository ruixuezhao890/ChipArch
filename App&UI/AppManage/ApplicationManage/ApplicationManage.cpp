/**
*********************************************************************
*********
* @project_name :MusicClion
* @file : ApplicationManage.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/2/7 
*********************************************************************
*********
*/
#include "lvgl/lvgl.h"

#include "ApplicationManage.h"
#include "ChipArch/App&UI/AppManage/Application/Application.h"
#include "ChipArch/vendor/ETL/ETLibrary/include/etl/map.h"
#include "ChipArch/ChipArch/ChipArch.h"
ApplicationManage* appManage;
Application* curApp;

void ApplicationManage::removeAllApplication() {
   for(auto &iter:app_creat_buff_map){
       iter.second->app->pause();
       iter.second->app->Destruction();
       iter.second->app->getAppPacker()->deleteApp(iter.second->app);

   }
   app_creat_buff_map.clear();
}

void ApplicationManage::applicationUpData() {
    for (auto& pair : app_creat_buff_map) {
        if (pair.second->app->isGoingStart()){
            pair.second->app->resetGoingStartFlag();
            pair.second->state=AppState::RESUME;
        }
        if (pair.second->app->isGoingClose()){
            pair.second->app->resetGoingCloseFlag();
            if ( pair.second->app->isAllowBgRunning()){
                pair.second->state=AppState::PAUSED;
            }else{
                pair.second->state=AppState::DELETE;
            }

        }
        if (pair.second->app->isGoingDestroy()){
            pair.second->app->resetGoingDestroyFlag();
            pair.second->state=AppState::DELETE;
        }
        switch (pair.second->state) {
            case AppState::CREATE:
                break;
            case AppState::RESUME:
                //切换新界面
                PageMange->page_manage_switch_page(pair.second->app->getAppName());
               pair.second->app->resume();
               pair.second->state=AppState::RUNNING;
                break;
            case AppState::RUNNING:
                pair.second->app->running();
                // Do something when application is running
                break;
            case AppState::PAUSED:
                pair.second->app->pause();
                pair.second->state=AppState::BGRUNNING;

                //清除控件

                // Do something when application is paused
                break;
            case AppState::BGRUNNING:
                pair.second->app->backRunning();
                break;
            case AppState::DELETE: {

                pair.second->app->pause();
                pair.second->app->Destruction();

                app_creat_buff_map.erase(pair.second->app->getAppName());

                // Do something when application is stopped
                continue;
            }
            case AppState::NOTINGTODO:
                continue;
            default:
//                DEBUG_PRINTLN("Unknown state for " + app->getName());
                break;
        }
    }
}

bool ApplicationManage::startApplication(const String &appName) {
    auto app=app_creat_buff_map[appName];
    if (!app){
        return false;
    }
    switch (app->state) {
        case AppState::CREATE:
            app->state=AppState::RESUME;
            break;
        case AppState::RESUME:
            break;
        case AppState::RUNNING:
            break;
        case AppState::BGRUNNING:
            app->state=AppState::RESUME;
            break;
        case AppState::PAUSED:
            app->state=AppState::RESUME;
            break;
        case AppState::DELETE:
            break;
        case AppState::NOTINGTODO:
            app->state=AppState::RESUME;
        default:
            break;
    }
    return true;

}

bool ApplicationManage::closeApplication(const String &appName) {
    auto app=app_creat_buff_map[appName];
    auto set_state=AppState::NOTINGTODO;
    if (app->app->isAllowBgRunning()){
        set_state=AppState::PAUSED;
    }else{
        set_state=AppState::DELETE;
    }
    if (!app){
        return false;
    }
    switch (app->state) {
        case AppState::CREATE:

            break;
        case AppState::RESUME:
            app->state=set_state;
            break;
        case AppState::RUNNING:
            app->state=set_state;
            break;
        case AppState::BGRUNNING:

            break;
        case AppState::PAUSED:

            break;
        case AppState::DELETE:
            break;
        default:
            break;
    }
    return true;
}

bool ApplicationManage::deleteApplication(const String &appName) {
    auto app=app_creat_buff_map[appName];
    if (!app){
        return false;
    }
    switch (app->state) {
        case AppState::CREATE:

            break;
        case AppState::RESUME:
            app->state=AppState::DELETE;
            break;
        case AppState::RUNNING:
            app->state=AppState::DELETE;
            break;
        case AppState::BGRUNNING:

            break;
        case AppState::PAUSED:

            break;
        case AppState::DELETE:
            break;
        default:
            break;
    }
    return true;


}

ApplicationManage::ApplicationManage() {
    PageMange= nullptr;
}

ApplicationManage::~ApplicationManage() {
    if (PageMange)
    PageMange= nullptr;
}

ApplicationManage::ApplicationManage(PageManage *set_pageManage):
    PageMange(set_pageManage) {
}

Application * ApplicationManage::creatApplication(AppPackage * appPackage) {
    if (!appPackage){
        return nullptr;
    }
    auto new_app=(Application *)appPackage->newApp();
    if (!new_app){
        return nullptr;
    }

    new_app->setAppPacker(appPackage);
    PageMange->page_manage_add_page(new_app->createNewPage(),new_app->getAppName());
    new_app->creat();
    auto new_appLifecycle=new AppLifecycle_t;
    new_appLifecycle->state=AppState::CREATE;
    new_appLifecycle->app=new_app;
    app_creat_buff_map[appPackage->getAppName()]=new_appLifecycle;
    return new_app;

}











