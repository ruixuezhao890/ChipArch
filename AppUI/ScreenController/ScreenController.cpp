/**
*********************************************************************
*********
* @project_name :micro_snow
* @file : ScreenController.cpp
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2024/10/1 
*********************************************************************
*********
*/


#include "ScreenController.hpp"
#include "EmbHardware/HAL.h"
#include "PubInculde.hpp"
lv_pm_open_options_t SCREEN_PACKER_BASE::open_options={
        LV_PM_ANIMA_NONE,
        LV_PM_TARGET_RESET,
        LV_PM_ANIMA_TOP
};

void SCREEN_PACKER_BASE::setScreenBase(SCREEN_BASE *screenBase) {
    screenBase_ = screenBase;
}

void SCREEN_PACKER_BASE::setAppBase(ChipArch_::APP_BASE *appBase) {
    appBase_ = appBase;
}

SCREEN_BASE *SCREEN_PACKER_BASE::getScreenBase() const {
    return screenBase_;
}

ChipArch_::APP_BASE *SCREEN_PACKER_BASE::getAppBase() const {
    return appBase_;
}

ScreenController::ScreenController(){
    if (lv_pm_init()){
        fmt::newline_info("lv_pm_init error");
    }
}
SCREEN_BASE * ScreenController::creatPage(SCREEN_PACKER_BASE * screenPackerBase){
    auto page_id=screenPackerBase->getPageId();

    auto createPage= lv_pm_create_page(page_id);
    if (!createPage)
    {
     fmt::newline_info("createpage error");   
    }

    auto pScreenBase=(SCREEN_BASE *)screenPackerBase->newPage(createPage);
    screenPackerBase->setScreenBase(pScreenBase);
    pScreenBase->setPage(createPage);
    pScreenBase->setScreenPacker(screenPackerBase);
    return pScreenBase;

}

bool ScreenController::openScreen(SCREEN_PACKER_BASE *screenPackerBase) {
    return lv_pm_open_page(screenPackerBase->getPageId(),&SCREEN_PACKER_BASE::open_options);
}

bool ScreenController::backScreen(SCREEN_PACKER_BASE * screenPackerBase) {
    auto  router=lv_pm_router[screenPackerBase->getPageId()];
    auto  obj=router->page;
    auto  function=router->unLoad;
    if (!obj){
        return false;
    }
    function(obj);
    lv_obj_clean(obj);
    return true;
}
