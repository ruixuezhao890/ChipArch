/**
*********************************************************************
*********
* @project_name :2048
* @file : PageManage.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/12/26 
*********************************************************************
*********
*/
//

#ifndef INC_2048_PAGEMANAGE_H
#define INC_2048_PAGEMANAGE_H

#include "map"

#include "ChipArch/vendor/OtherLib/WString.h"
#include "ChipArch/vendor/ETL/ETLibrary/include/etl/map.h"
#include "ChipArch/vendor/ETL/ETLibrary/include/etl/queue.h"
#include "ChipArch/vendor/ETL/ETLibrary/include/etl/vector.h"
#include "ChipArch/ChipArch/Input_device_interface/InputDeviceInterface.h"


const String home_page_name="home page";
class ChipArch;
class Application;
class Page{
protected:
    lv_obj_t * now_page_= nullptr;
    String  now_app_name_;
    lv_scr_load_anim_t anim_=LV_SCR_LOAD_ANIM_FADE_IN;
    bool screen_orientation_= false;
public:
    Page(const String & now_app){
        now_app_name_=now_app;
    }
    virtual ~Page(){

    }

    virtual void init()=0;

    virtual void exit() =0;

    virtual bool getScreenOrientation()=0;

    virtual String & getNowAppName()=0;

    inline lv_obj_t * getNowPage(){return now_page_;};

    inline void setNowPage(lv_obj_t * set_page){ now_page_=set_page;};

    inline lv_scr_load_anim_t getLoadAnim(){return anim_;};
};
class PageManage{
public:
    PageManage()=default;

    explicit PageManage(Display * display);

    ~PageManage();

    void page_manage_add_page(Page *page, const String &id);

    void page_manage_switch_page(const String &id);

    void setDisplay(Display& display);

    Page * current_page_= nullptr;
protected:
    Display * display_= nullptr;

    std::map<String ,Page *> page_map_;

};

#endif //INC_2048_PAGEMANAGE_H
