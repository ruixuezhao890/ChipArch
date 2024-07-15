/**
*********************************************************************
*********
* @project_name :MusicClion
* @file : ApplicationManage.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/2/7 
*********************************************************************
*********
*/
//

#ifndef MUSICCLION_APPLICATIONMANAGE_H
#define MUSICCLION_APPLICATIONMANAGE_H

#include "../../PageManage/PageManage.h"
#include "../../AppManage/Application/Application.hpp"


const uint8_t max_app_num=64;
class ApplicationManage final {
public:
    enum class AppState {
        CREATE,
        RESUME,
        RUNNING,
        BGRUNNING,
        PAUSED,
        DESTROY,
        NOTINGTODO
    };
private:
    PageManage  page_manager_;
protected:
    struct AppLifecycle_t
    {
        Application * app = nullptr;
        AppState state = AppState::CREATE;
    };
    std::map<String, AppLifecycle_t*> app_creat_buff_map; // Change std::string to String

    void backHome();

public:
    ApplicationManage();

    ~ApplicationManage();

    inline std::size_t getCreateAppNum(){return app_creat_buff_map.size();}

    void removeAllApplication(); // Change std::string to String

    Application * creatApplication(AppPackage * appPackage);

    bool startApplication(const String & appName);

    bool closeApplication(const String & appName);

    bool deleteApplication(const String & appName);

    void applicationUpData();

};

#endif //MUSICCLION_APPLICATIONMANAGE_H
