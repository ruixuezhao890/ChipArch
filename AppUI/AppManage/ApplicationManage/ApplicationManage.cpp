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
#include "ApplicationManage.h"



void ApplicationManage::removeAllApplication() {
   for(auto &iter:app_creat_buff_map){
       iter.second->app->pause();
       iter.second->app->Destruction();
       iter.second->app->getAppPacker()->deleteApp(iter.second->app);

   }
   app_creat_buff_map.clear();
}

void ApplicationManage::applicationUpData() {
    for (auto pair = app_creat_buff_map.begin(); pair != app_creat_buff_map.end();) {
        if (pair->second->app->isGoingStart()){
            pair->second->app->resetGoingStartFlag();
            pair->second->state=AppState::RESUME;
        }
        if (pair->second->app->isGoingClose()){
            pair->second->app->resetGoingCloseFlag();
            if ( pair->second->app->isAllowBgRunning()){
                pair->second->state=AppState::PAUSED;
            }else{
                pair->second->state=AppState::DESTROY;
            }
        }
        if (pair->second->app->isGoingDestroy()){
            pair->second->app->resetGoingDestroyFlag();
            pair->second->state=AppState::DESTROY;
        }
        switch (pair->second->state) {
            case AppState::CREATE:
                break;
            case AppState::RESUME:
                //切换新界面
                page_manager_.page_manage_switch_page(pair->second->app->getAppName());
               pair->second->app->resume();
               pair->second->state=AppState::RUNNING;
                break;
            case AppState::RUNNING:
                pair->second->app->running();
                // Do something when application is running
                break;
            case AppState::PAUSED:
                pair->second->app->pause();
                pair->second->state=AppState::BGRUNNING;
                //返回桌面
                if (pair->first!=home_page_name){
                    backHome();
                }
                // Do something when application is paused
                break;
            case AppState::BGRUNNING:
                pair->second->app->backRunning();
                break;
            case AppState::DESTROY: {

                pair->second->app->pause();
                pair->second->app->Destruction();

                pair->second->app->getAppPacker()->deleteApp(pair->second->app);
                pair=app_creat_buff_map.erase(pair);
                //返回桌面
                backHome();
                // Do something when application is stopped
                continue;
            }
            case AppState::NOTINGTODO:
                continue;
            default:
//               ("Unknown state for " + pair.first);
                break;
        }
        pair++;
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
        case AppState::DESTROY:
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
        set_state=AppState::DESTROY;
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
        case AppState::DESTROY:
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
            app->state=AppState::DESTROY;
            break;
        case AppState::RUNNING:
            app->state=AppState::DESTROY;
            break;
        case AppState::BGRUNNING:

            break;
        case AppState::PAUSED:

            break;
        case AppState::DESTROY:
            break;
        default:
            break;
    }
    return true;
}

ApplicationManage::ApplicationManage() {
    page_manager_.setDisplay(HAL::getDisplayInterface());
};

ApplicationManage::~ApplicationManage() = default;

Application * ApplicationManage::creatApplication(AppPackage * appPackage) {
    if (!appPackage){
        return nullptr;
    }
    auto new_app=(Application *)appPackage->newApp();
    if (!new_app){
        return nullptr;
    }

    new_app->setAppPacker(appPackage);
    new_app->creat();
    page_manager_.page_manage_add_page(new_app->getPage(),new_app->getAppName());
    auto new_appLifecycle=new AppLifecycle_t;
    new_appLifecycle->state=AppState::CREATE;
    new_appLifecycle->app=new_app;
    app_creat_buff_map[appPackage->getAppName()]=new_appLifecycle;
    return new_app;

}

void ApplicationManage::backHome()  {
    auto get=app_creat_buff_map[home_page_name];
    get->state=AppState::RESUME;
}











