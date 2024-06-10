/**
*********************************************************************
*********
* @project_name :2048
* @file : PageManage.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/12/26 
*********************************************************************
*********
*/
//

#include "PageManage.h"
PageManage::~PageManage()
{

}

void PageManage::page_manage_add_page(Page *page, const String &id) {
    //查找是否有注册的页面 如果没有则进行创建 如果有则直接返回
    auto  find_page=page_map_.find(id);
    if (find_page!=page_map_.end()){
        LV_LOG("add_page_error\n");
        return;
    }else{

    }
    if (page){
        page->setNowPage(lv_obj_create(nullptr));
        page_map_[id]=page;
    }
}

void PageManage::page_manage_switch_page(const String &id) {
    auto pPage=page_map_[id];
    if (pPage){
        pPage->init();
        if (pPage->getScreenOrientation()){//改为竖屏
            display_->set_rotation(LV_DISP_ROT_90);
        }
        lv_scr_load_anim(pPage->getNowPage(), pPage->getLoadAnim(), 800, 0, false);
        if (current_page_){
            lv_obj_clean(current_page_->getNowPage());
            current_page_->exit();
        }
        current_page_=pPage;
    }
}

PageManage::PageManage(Display *display) {
    display_=display;
    current_page_= nullptr;
}

void PageManage::setDisplay(Display &display) {
    display_=&display;
}











