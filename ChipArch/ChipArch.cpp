/**
*********************************************************************
*********
* @project_name :lvgl
* @file : ChipArchhChild.h
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2024/4/11
*********************************************************************
*/
#include "ChipArch.h"
#include "SysApp/boot_anim_ascii/boot_anim_ascii.h"


using namespace ChipArch_;
APP_UserData_t * ChipArch::_user_data= nullptr;
ChipArch::~ChipArch()
{
//    spdlog::warn("ChipArch destruction");

    /* Free memory */
    if (_flag_free_user_data)
        delete _user_data;
    if (_flag_free_boot_anim)
        delete _boot_anim;

//    spdlog::info("bye :(");
}

void ChipArch::init()
{
//    spdlog::info("ChipArch init :)");

    /* Init user data */
    /* If user data not set */
    if (_user_data == nullptr)
    {
//        spdlog::info("create userdata");
        _user_data = new APP_UserData_t;
        _flag_free_user_data = true;
    }

    /* Copy framework's pointer into user data */
    _user_data->framework = this;

    /* Copy database's pointer into user data */
    _user_data->database = &_database;

    /* init database */
    _data_base_setup_internal();

    /* Init boot anim */
    /* If boot anim not set */
    if (_boot_anim == nullptr)
    {
//        spdlog::info("create boot anim");
        /* Create a default one */
        _boot_anim = new APPS::BootAnim_ASCII_Packer;
        _flag_free_boot_anim = true;
    }

    /* Start boot anim and wait till it finish */
//    spdlog::info("start boot anim");
    _app_manager.destroyAllApps();
    _app_manager.startApp(_app_manager.createApp(_boot_anim));
    // while (1)
    // {
    //     _app_manager.update();
    //     /* If boot anim is destroyed */
    //     if (_app_manager.getCreatedAppNum() == 0)
    //         break;
    // }

//    spdlog::info("init done");
}

void ChipArch::_data_base_setup_internal()
{
//    spdlog::info("start db setup");

    /* Setup basic data with default value */
    /* Display */
    _database.Add(MC_DB_DISP_HOR, MY_DISP_HOR_RES);
    _database.Add(MC_DB_DISP_VER, MY_DISP_VER_RES);

    /* Power */
    _database.Add(MC_DB_BATTERY_LEVEL, 100);
    _database.Add(MC_DB_BATTERY_IS_CHARGING, false);

    /* Call database setup callback if it's set */
    if (_database_setup_callback != nullptr)
    {
//        spdlog::info("call db setup callback");
        _database_setup_callback(_database);
    }
}

void ChipArch::update()
{
    /* Update input devices */
    // _input_device_register.update();

    /* Update apps' lifecycles */
    _app_manager.update();
}
void chip_arch_updata(){
//    ChipArch::getChipArchInstance()->update();
}