/**
*********************************************************************
*********
* @project_name :lvgl
* @file : app_blue_screen_ui.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/6/9
*********************************************************************
*********
*/
//

#include "app_blue_screen_ui.h"
#include "ChipArch/AppUI/AppMessagePipe/AppMessagePipe.h"
app_blue_screen_ui::app_blue_screen_ui(const String &band) : Page(band) {

}

app_blue_screen_ui::~app_blue_screen_ui() = default;

void app_blue_screen_ui::init() {
    auto cont=new Container(this->getNowPage());
    cont->set_size(320,240);
    cont->set_style_bg_color(palette::main(Color::Blue),LV_PART_MAIN);
    widgets_.error_label=new Label(*cont);
}

void app_blue_screen_ui::exit() {

}

void app_blue_screen_ui::monitorMessageUpdates() {
    auto message=message_pipe ::getMessage(now_app_name_.c_str(),0);
    if(message.first){
        widgets_.error_label->set_text(message.second.c_str());
        widgets_.error_label->center();
    }
}




