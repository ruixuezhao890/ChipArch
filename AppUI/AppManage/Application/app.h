/**
*********************************************************************
*********
* @project_name :modm
* @file : ChipArchChild.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/4/11
*********************************************************************
*/
#pragma once
#include <string>
#include "ChipArchConfig.h"
#include "AppUI/ScreenController/Screen.hpp"
namespace ChipArch_
{
    /* App packer base */
    /* Contains the static elements of an app, like name, icon... */
    /* Also an app's memory allocation, freeing... */
    /* This class is designed for a better resource and memory manager, like launcher's usage */
    class APP_PACKER_BASE
    {
    private:
        void* _user_data;

    public:
        APP_PACKER_BASE() : _user_data(nullptr) {}
        /* Virtual it for subclass's memory free */
        virtual ~APP_PACKER_BASE() {}

        /* Basic data getter and setter */
        inline void setUserData(void* userData) { _user_data = userData; }
        inline void* getUserData() { return _user_data; }
        inline APP_PACKER_BASE* getAddr() { return this; }

        /* ---------------------------------------------------------------------------------- */
        /**
         * @brief Override and return app's name
         *
         * @return std::string
         */
        virtual std::string getAppName() { return ""; };

        /**
         * @brief Override and return app's icon pointer
         *
         * @return void*
         */
        virtual void* getAppIcon() { return nullptr; }

        /**
         * @brief Override and return more custom data, like theme color, iamges...
         *
         * @return void*
         */
        virtual void* getCustomData() { return nullptr; }

        /* ---------------------------------------------------------------------------------- */
        /* App's create and delete */
        /* For app manager's usage */
        /* To make app comes and go memory dynamically */
        /* ---------------------------------------------------------------------------------- */
        /**
         * @brief Override and return a new app's pointer
         *
         * @return void* new app's pointer
         */
        virtual void* newApp() { return nullptr; }

        /**
         * @brief Override and delete the passing app
         *
         * @param app app's pointer
         */
        virtual void deleteApp(void* app) {}

        virtual void * newScreenPacker(){return nullptr;}

        virtual void deleteScreenPacker(void * pVoid){}

        /* ---------------------------------------------------------------------------------- */
    };

    /* App base class */
    /* Contains states for life cycle control (FSM) */
    /* Polymorphism of the life cycle makes different apps */
    class APP_BASE
    {
//        friend class SCREEN_BASE;
    private:
        /* App packer's pointer */
        /* Where you can get the app's resource */
        /* Like name, icon, database... */
        APP_PACKER_BASE* _app_packer;

        SCREEN_PACKER_BASE * _screen_packer;

        SCREEN_BASE * _screen;

        /* Internal state */
        bool _allow_bg_running;
        bool _go_start;
        bool _go_close;
        bool _go_destroy;

//    protected:
    public:
        /* API to control app's lifecycle state (internal) */

        /**
         * @brief Set if is App running background after closed
         *
         * @param allow
         */
        inline void setAllowBgRunning(bool allow) { _allow_bg_running = allow; }

        /**
         * @brief Notice the app manager, that this app want to be started
         *
         */
        inline void startApp() { _go_start = true; }

        /**
         * @brief Notice the app manager, that this app want to be cloesd
         * , better call this in onRunning() only, to avoid repeat method callback
         */
        inline void closeApp() { _go_close = true; }

        /**
         * @brief Notice the app manager, that this app want to be destroyed
         * , better call this in onRunning() or onRunningBG() only, to avoid repeat method callback
         */
        inline void destroyApp() { _go_destroy = true; }


        APP_BASE() : _app_packer(nullptr), _allow_bg_running(false), _go_start(false), _go_close(false), _go_destroy(false),
                    _screen_packer(nullptr),_screen(nullptr){

        }
        virtual ~APP_BASE() {

        }

        /* Wrap for resource getting from app packer */
        inline APP_PACKER_BASE* getAppPacker() { return _app_packer; }
        inline std::string getAppName() { return getAppPacker()->getAppName(); }
        inline void* getAppIcon() { return getAppPacker()->getAppIcon(); }
        inline void* getCustomData() { return getAppPacker()->getCustomData(); }
        inline void* getUserData() { return getAppPacker()->getUserData(); }

        /* API for lifecycle's state checking */
        inline bool isAllowBgRunning() { return _allow_bg_running; }
        inline bool isGoingStart() { return _go_start; }
        inline bool isGoingClose() { return _go_close; }
        inline bool isGoingDestroy() { return _go_destroy; }
        inline void resetGoingStartFlag() { _go_start = false; }
        inline void resetGoingCloseFlag() { _go_close = false; }
        inline void resetGoingDestroyFlag() { _go_destroy = false; }

        /**
         * @brief Set the App Packer
         *
         * @param appPacker
         */
        inline void setAppPacker(APP_PACKER_BASE* appPacker) { _app_packer = appPacker; }

        inline void setScreenPacker(SCREEN_PACKER_BASE * screenPackerBase){_screen_packer=screenPackerBase;}

        inline SCREEN_PACKER_BASE* getScreenPacker(){return _screen_packer;}

        inline void setScreen(SCREEN_BASE * screenBase){_screen=screenBase;}
        /* Lifecycle methonds */
        /* basically the only thing you need to care about */
        /* Override and do what you want */
        /* It's very lite version of andriod's lifecycle :( */
        virtual void onCreate() {}
        virtual void onResume() {}
        virtual void onRunning() {}
        virtual void onRunningBG() {}
        virtual void onPause() {}
        virtual void onDestroy() {}
    };
} // namespace ChipArch
