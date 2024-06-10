/**
*********************************************************************
*********
* @project_name :lvgl
* @file : log.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/4/30 
*********************************************************************
*********
*/
//

#include <functional>
#include "log.h"

log* log::log_ptr_= nullptr;
void log::print_cb(const char *massage) {
    if (log_ptr_){
        log_ptr_->log_print(massage);
    }

}

void log::initLog() {
    if (!log_ptr_){
      log_ptr_=new log();
    }
    lv_log_register_print_cb(log::print_cb);
}

void log::log_print(const char *message) {
    printf("%s",message);
}
