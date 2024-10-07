/**
*********************************************************************
*********
* @project_name :micro_snow
* @file : ScreenController.hpp
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2024/10/1 
*********************************************************************
*********
*/


#ifndef MICRO_SNOW_SCREEN_HPP
#define MICRO_SNOW_SCREEN_HPP
#include "ScreenCoupled/pm.h"
/*           设计这个类的想法

这个功能实现类似与APP的实现，拆分为screen_packer和screen，初始化还是使用ScreenControllerBase
使用screen是为了统一初始化接口将需要外部访问的控件放screen_packer当中进行访问 
通过app_packer中编写的虚函数对对应screen_packer进行初始化，回调函数通过函数包装绑定’‘
* * * * * * */

class SCREEN_BASE;
namespace ChipArch_{
    class APP_BASE;
}
class SCREEN_PACKER_BASE{
protected:
    SCREEN_BASE * screenBase_= nullptr;

    ChipArch_::APP_BASE* appBase_= nullptr;

public:
    void setScreenBase(SCREEN_BASE *screenBase);

    void setAppBase(ChipArch_::APP_BASE *appBase);

    SCREEN_BASE *getScreenBase() const;

    ChipArch_::APP_BASE *getAppBase() const;


    static lv_pm_open_options_t open_options;

    virtual void * newPage(lv_pm_page_t* lv_pm_page_set)=0;

    virtual void deletePage(void * pVoid)=0;

    inline SCREEN_PACKER_BASE * getAddr() { return this; }

    virtual uint8_t getPageId()=0;

    virtual void * getWidgetStruct()=0;


};

class SCREEN_BASE{
protected:
    SCREEN_PACKER_BASE * screen_packerBase_;

    lv_pm_page_t * page_;
public:
    explicit SCREEN_BASE(lv_pm_page_t* lv_pm_page_set):screen_packerBase_(nullptr),page_(lv_pm_page_set){
      page_->page->user_data=static_cast<void*>(this);
      auto load=[](lv_obj_t * cont){
          auto obj=reinterpret_cast<SCREEN_BASE *>(cont->user_data);
          obj->initScreen(cont);
      };
      auto exit=[](lv_obj_t * cont){
          auto obj=reinterpret_cast<SCREEN_BASE*>(cont->user_data);
          obj->deInitScreen(cont);
      };
      page_->onLoad=load;

      page_->unLoad=exit;
    }

    inline lv_pm_page_t *getPage() const {
        return page_;
    }

    inline void setPage(lv_pm_page_t *page) {
        page_ = page;
    }

    inline void setScreenPacker(SCREEN_PACKER_BASE * set){
        screen_packerBase_=set;
    }
    inline SCREEN_PACKER_BASE * getScreenPacker(){
        return screen_packerBase_;
    }

    virtual void initScreen(lv_obj_t * cont)=0;

    virtual void deInitScreen(lv_obj_t * cont)=0;
};
#endif