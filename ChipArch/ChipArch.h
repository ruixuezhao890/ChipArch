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
#include "AppUI/AppManage/Application/app.h"
#include "AppUI/AppManage/Application/app_register.h"
#include "AppUI/AppManage/ApplicationManage/app_manager.h"
#include "AppUI/AppManage/InputSystem/input_device_register.h"

#include "vendor/simplekv/simplekv.h"
#include "ChipArchConfig.h"


/* Disable some features */
#ifdef ESP_PLATFORM
#define SPDLOG_NO_EXCEPTIONS
#define SPDLOG_NO_THREAD_ID
#endif
//#include "vendor/spdlog/include/spdlog/spdlog.h"
#include "AppUI/AppManage/InputSystem/input_device.h"

void chip_arch_updata();

namespace ChipArch_
{


    class ChipArch;

    /* Structure that contains userdata */
    /* Will be passed to every running apps */
    /* You can inherit this to create your own userdata */
    struct APP_UserData_t
    {
        /* Pointer to the framwork */
        ChipArch* framework = nullptr;

        /* Pointer to the database */
        SIMPLEKV::SimpleKV* database = nullptr;

        APP_PACKER_BASE * desk_packer_point = nullptr;
    };

    /* ChipArch framework class */
    /* Inherit App Register to manager apps' install and uninstall */
    /* Contains a App Manager to control apps' lifecycles */
    class ChipArch
    {
    private:
        /* Component Input system */
        InputDevice_Register _input_device_register;

        /* Component App register */
        APP_Register _app_register;

        /* Component App manager */
        APP_Manager _app_manager;



        /* Component Database */
        SIMPLEKV::SimpleKV _database;

        /* User data pointer */
        static APP_UserData_t* _user_data;

        /* Boot anim pointer */
        APP_PACKER_BASE* _boot_anim;
        void (*_database_setup_callback)(SIMPLEKV::SimpleKV&);

        /* Flag to free the memory, if they are created by framework */
        bool _flag_free_user_data;
        bool _flag_free_boot_anim;

        void _data_base_setup_internal();

    public:
        ChipArch()// _user_data(nullptr),
        : _boot_anim(nullptr), _database_setup_callback(nullptr), _flag_free_user_data(false),
                  _flag_free_boot_anim(false)
        {
        }
        ~ChipArch();

        /* Framework's components getter */
        inline InputDevice_Register& getInputDeviceRegister() { return _input_device_register; }
        inline APP_Register& getAppRegister() { return _app_register; }
        inline APP_Manager& getAppManager() { return _app_manager; }
        inline SIMPLEKV::SimpleKV& getDatabase() { return _database; }

        /**
         * @brief Set the user data, which will be passed to every apps
         * , if not set, framework will create a default one
         * @param userData
         */
        static inline void setChipArchInstance(ChipArch* userData) { _user_data->framework = userData; }

        static inline void setSimpleKVInstance(SIMPLEKV::SimpleKV* userData) { _user_data->database = userData; }

        static inline void setDeskPointInstance(APP_PACKER_BASE* userData) { _user_data->desk_packer_point=userData; }

        static inline APP_PACKER_BASE * getDeskPointInstance() { return _user_data->desk_packer_point; }


        /**
         * @brief Get the User Data object
         *
         * @return APP_UserData_t*
         */
        static inline ChipArch* getChipArchInstance() {
            if (_user_data){
                return _user_data->framework;
            }
            return nullptr;
        }

        static inline SIMPLEKV::SimpleKV* getSimpleKVInstance(){
            if (_user_data){
                return _user_data->database;
            }
            return nullptr;
        }

        /**
         * @brief Set the boot anim, which will be created and run in framework's init()
         * , if not set, framework will create a default one
         * @param bootAnim
         */
        inline void setBootAnim(APP_PACKER_BASE* bootAnim) { _boot_anim = bootAnim; }

        /**
         * @brief Set the Database Setup Callback
         * , the call back will be called after some basic data were set, you can add some custom data into database in the
         * callback
         * @param databaseSetupCallback
         */
        inline void setDatabaseSetupCallback(void (*databaseSetupCallback)(SIMPLEKV::SimpleKV&))
        {
            _database_setup_callback = databaseSetupCallback;
        }

        /**
         * @brief Init framework
         *
         */
        void init();

        /**
         * @brief Calling this to keep framework running
         *
         */
        void update();

        /* Framework wrap to the App register */

        /* *Important*: this wrap will pass user data pointer to the app packer */

        /**
         * @brief Install an app (Register an app packer)
         *
         * @param appPacker
         * @return true
         * @return false
         */
        inline bool installApp(APP_PACKER_BASE* appPacker) { return _app_register.install(appPacker, _user_data); }

        /**
         * @brief Uninstall an app (Remove it from the register)
         *
         * @param appPacker
         * @return true
         * @return false
         */
        inline bool uninstallApp(APP_PACKER_BASE* appPacker) { return _app_register.uninstall(appPacker); }

        /**
         * @brief Uninstall all apps
         *
         */
        inline void uninstallAllApps() { _app_register.uninstallAllApps(); }

        /**
         * @brief Get the total installed app num in app register
         *
         * @return std::size_t
         */
        inline std::size_t getInstalledAppNum() { return _app_register.getInstalledAppNum(); }

        /**
         * @brief Get the reference to the installed app packer list
         *
         * @return std::vector<APP_PACKER_BASE*>&
         */
        inline std::vector<APP_PACKER_BASE*>& getInstalledAppList() { return _app_register.getInstalledAppList(); }

        /* Framework wrap to the App manager */

        /**
         * @brief Create an app
         *
         * @param appPacker app's packer
         * @return APP_BASE* started app's pointer
         */
        inline APP_BASE* createApp(APP_PACKER_BASE* appPacker) { return _app_manager.createApp(appPacker); }

        /**
         * @brief Start an app, this method will only change passing app's state
         *
         * @param app
         * @return true
         * @return false
         */
        inline bool startApp(APP_BASE* app) { return _app_manager.startApp(app); }

        /**
         * @brief Wrap of create and start an app
         *
         * @param appPacker
         * @return true
         * @return false
         */
        inline bool createAndStartApp(APP_PACKER_BASE* appPacker) { return startApp(createApp(appPacker)); }

        /**
         * @brief Close an app, this method will only change passing app's state
         *
         * @param app App's pointer which you want to close
         * @return true
         * @return false
         */
        inline bool closeApp(APP_BASE* app) { return _app_manager.closeApp(app); }

        /**
         * @brief Destroy an app, app will be deleted by it's app packer
         *
         * @param app App's pointer which you want to destroy
         * @return true
         * @return false
         */
        inline bool destroyApp(APP_BASE* app) { return _app_manager.destroyApp(app); }

        /**
         * @brief Destroy all apps
         *
         */
        inline void destroyAllApps() { _app_manager.destroyAllApps(); }

        /**
         * @brief Get total created app num in app manager
         *
         * @return std::size_t
         */
        inline std::size_t getCreatedAppNum() { return _app_manager.getCreatedAppNum(); }

        /* Framework wrap to the Input device register */

        /**
         * @brief Install an input device, it's init method will be called here
         *
         * @param inputDevice
         * @param userData
         * @return true
         * @return false
         */
        inline bool installIndev(INPUT_DEVICE_BASE* inputDevice, void* userData = nullptr)
        {
            return _input_device_register.install(inputDevice, userData);
        }

        /**
         * @brief Uninstall an input device
         *
         * @param inputDevice
         * @return true
         * @return false
         */
        inline bool uninstallIndev(INPUT_DEVICE_BASE* inputDevice) { return _input_device_register.uninstall(inputDevice); }

        /**
         * @brief Uninstall all input devices
         *
         */
        inline void uninstallAllIndev() { _input_device_register.uninstallAllDevice(); }

        /**
         * @brief Get the total number of installed input device
         *
         * @return std::size_t
         */
        inline std::size_t getInstalledIndevNum() { return _input_device_register.getInstalledDeviceNum(); }
    };
} // namespace ChipArch
