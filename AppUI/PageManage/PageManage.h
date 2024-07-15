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
#include "../../vendor/OtherLib/WString.h"
#include "../../vendor/ETL/ETLibrary/include/etl/map.h"
#include "../../vendor/ETL/ETLibrary/include/etl/queue.h"
#include "../../vendor/ETL/ETLibrary/include/etl/vector.h"
#include "ChipArch/EmbHardware/Input_device_interface/InputDeviceInterface.h"


const String home_page_name="home page";
class ChipArch;
class Application;
class Page {
protected:
    lv_obj_t* now_page_ = nullptr;
    String now_app_name_;
    lv_scr_load_anim_t anim_ = LV_SCR_LOAD_ANIM_FADE_IN;
    bool screen_orientation_ = false;

public:
    explicit Page(const String& now_app);
    virtual ~Page() = default;

    virtual void init() = 0;
    virtual void exit() = 0;

    lv_obj_t* getNowPage() const;
    void setNowPage(lv_obj_t* set_page);

    lv_scr_load_anim_t getLoadAnim() const;
    void setLoadAnim(lv_scr_load_anim_t anim);

    bool getScreenOrientation() const;
    void setScreenOrientation(bool orientation);
};
class PageManage{
public:
    PageManage()=default;

    ~PageManage();

    void page_manage_add_page(Page *page, const String &id);

    void page_manage_switch_page(const String &id);

    void setDisplay(Display* display);

    Page * current_page_= nullptr;
protected:
    Display * display_= nullptr;

    std::map<String ,Page *> page_map_;

};

#endif //INC_2048_PAGEMANAGE_H
