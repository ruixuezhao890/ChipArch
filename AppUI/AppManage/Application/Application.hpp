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
#include "../../../EmbHardware/HAL.h"
#include "../../PageManage/PageManage.h"
#include "ChipArch/AppUI/AppMessagePipe/AppMessagePipe.h"

class AppPackage {
private:
    bool allow_display_icon_= true;
    void * user_data_;
    void * workshop_;
public:
    AppPackage() : user_data_(nullptr),workshop_(nullptr) {}
    virtual ~AppPackage() = default;

    // UserData pointer
    inline void setUserData(void* userData) { user_data_ = userData; }
    inline void* getUserData() { return user_data_; }
    //set workshop
    inline void setWorkShop(void* workshop) { workshop_ = workshop; }
    inline void* getWorkShop() { return workshop_; }

    // Self pointer
    inline AppPackage* getAddr() { return this; }
    // Display icon
    inline void setAllowDisplayIcon(bool allow){allow_display_icon_=allow;}
    inline bool getAllowDisplayIcon() const{return  allow_display_icon_;}
    /* ------------------------------- App factory ------------------------------ */
public:

    virtual void* newApp() { return nullptr; }

    virtual void deleteApp(void* app) {}

    /* -------------------------- Basic app static data ------------------------- */
public:
    virtual const char* getAppName() { return ""; };

    virtual void* getAppIcon() { return nullptr; };

    virtual void* getCustomData() { return nullptr; }
};

class Application{
    struct State_t
    {
        bool allow_bg_running = false;
        bool go_start = false;
        bool go_close = false;
        bool go_destroy = false;
    };
protected:
    AppPackage * app_package_;

    Page * page_;

    State_t state_;
public:
    Application():app_package_(nullptr),page_(nullptr){

    };

    virtual ~Application()=default;

    inline  void setAppPacker(AppPackage * appPackage){app_package_=appPackage;}

    inline AppPackage* getAppPacker(){return app_package_;}

    inline  void setPage(Page * page){page_=page;}

    template<typename T>
    inline T* getPage(){return dynamic_cast<T*>(page_);}

    inline Page* getPage(){return (page_);}

    inline const char* getAppName() { return app_package_->getAppName(); }

    inline void* getAppIcon() { return getAppPacker()->getAppIcon(); }
    inline void* getCustomData() { return getAppPacker()->getCustomData(); }
    inline void* get_packer_userdata() { return getAppPacker()->getUserData(); }

    inline void set_packer_userdata(void * userData){getAppPacker()->setUserData(userData);}

    inline bool isAllowBgRunning() { return  state_.allow_bg_running;}
    inline bool isGoingStart() { return state_.go_start; }
    inline bool isGoingClose() { return state_.go_close; }
    inline bool isGoingDestroy() { return state_.go_destroy; }
    inline void resetGoingStartFlag() { state_.go_start = false; }
    inline void resetGoingCloseFlag() { state_.go_close = false; }
    inline void resetGoingDestroyFlag() { state_.go_destroy = false; }
protected:

    inline void setAllowBgRunning(bool allow) { state_.allow_bg_running = allow; }
    inline void startApp() { state_.go_start = true; }
    inline void closeApp() { state_.go_close = true; }
    inline void destroyApp() { state_.go_destroy = true; }
public:
    virtual void initPage()=0;//创建屏幕对象

    virtual void creat()=0;//为应用所需的资源申请空间或者加载应用所需的数据文件

    virtual void resume()=0;//应用初始化

    virtual void running()=0;//应用运行时

    virtual void backRunning()=0;//后台运行

    virtual void pause()=0;//退出运行

    virtual void Destruction()=0;//删除保存的文件并且进行初始化
};



#endif //MUSICCLION_APPLICATION_H
