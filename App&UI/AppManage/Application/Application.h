/**
*********************************************************************
*********
* @project_name :MusicClion
* @file : Application.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/2/7 
*********************************************************************
*********
*/
//

#ifndef MUSICCLION_APPLICATION_H
#define MUSICCLION_APPLICATION_H
#include <unistd.h>
#include "ChipArch/EmbHardware/HAL.h"
#include "ChipArch/App&UI/PageManage/PageManage.h"
#include "ChipArch/App&UI/AppManage/Application/AppPackage.h"

class ChipArch;
class Application{
protected:
    void * framework_{};
    Page * page_;
    AppPackage * app_package_;
    ChipArch* chipArch_;
    struct State_t
    {
        bool allow_bg_running = false;
        bool go_start = false;
        bool go_close = false;
        bool go_destroy = false;
    };
    State_t _state;
public:
    Application();

    virtual ~Application(){
        if (framework_){framework_= nullptr;}
        if (app_package_){delete app_package_;}
        if (chipArch_){chipArch_= nullptr;}

    };

    inline  void setAppPacker(AppPackage * appPackage){app_package_=appPackage;}
    inline AppPackage* getAppPacker(){return app_package_;}
    inline const char* getAppName() { return app_package_->getAppName(); }

    inline void* getAppIcon() { return getAppPacker()->getAppIcon(); }
    inline void* getCustomData() { return getAppPacker()->getCustomData(); }
    inline void* getFramwork() { return getAppPacker()->getFramwork(); }

    inline void set(void * userData){framework_=userData;}


    inline bool isAllowBgRunning() { return  _state.allow_bg_running;}
    inline bool isGoingStart() { return _state.go_start; }
    inline bool isGoingClose() { return _state.go_close; }
    inline bool isGoingDestroy() { return _state.go_destroy; }
    inline void resetGoingStartFlag() { _state.go_start = false; }
    inline void resetGoingCloseFlag() { _state.go_close = false; }
    inline void resetGoingDestroyFlag() { _state.go_destroy = false; }
protected:
    inline void setAllowBgRunning(bool allow) { _state.allow_bg_running = allow; }
    inline void startApp() { _state.go_start = true; }
    inline void closeApp() { _state.go_close = true; }
    inline void destroyApp() { _state.go_destroy = true; }
public:
    virtual void creat()=0;//为应用所需的资源申请空间或者加载应用所需的数据文件

    virtual void resume()=0;//应用初始化

    virtual void running()=0;//应用运行时

    virtual void backRunning()=0;//后台运行

    virtual void pause()=0;//退出运行

    virtual void Destruction()=0;//删除保存的文件并且进行初始化

    virtual Page * createNewPage()=0;

    virtual void deleteOldPage()=0;
};


#endif //MUSICCLION_APPLICATION_H
