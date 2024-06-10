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

#include "ChipArch/App&UI/PageManage/PageManage.h"
#include "ChipArch/App&UI/AppManage/Application/Application.h"


const uint8_t max_app_num=64;
class ApplicationManage final {
public:
    enum class AppState {
        CREATE,
        RESUME,
        RUNNING,
        BGRUNNING,
        PAUSED,
        DELETE,
        NOTINGTODO
    };
private:

    PageManage * PageMange;
protected:
    struct AppLifecycle_t
    {
        Application* app = nullptr;
        AppState state = AppState::CREATE;
    };
    std::map<String, AppLifecycle_t*> app_creat_buff_map; // Change std::string to String

public:

public:
    ApplicationManage();

    ApplicationManage(PageManage * set_pageManage);

    ~ApplicationManage();

    inline std::size_t getCreateAppNum(){return app_creat_buff_map.size();}

    void removeAllApplication(); // Change std::string to String

    Application * creatApplication(AppPackage * appPackage);

    bool startApplication(const String & appName);

    bool closeApplication(const String & appName);

    bool deleteApplication(const String & appName);

    Application * findApplication(const String & appName);

    void applicationUpData();

    void changeAppInterface(const String & InterfaceName);


};
extern ApplicationManage* appManage;
extern Application* curApp;
#endif //MUSICCLION_APPLICATIONMANAGE_H
