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
#include "lvgl.h"
#include "log.h"
#if 0
using namespace SentinelLog;

log* log::log_ptr_= nullptr;
void log::print_cb(const char *massage) {
        getLogPtr()->log_print(massage);
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

log *log::getLogPtr() {
    if (log_ptr_){
        return log_ptr_;
    }
    return nullptr;
}

size_t log::write(uint8_t uint8) {
    lv_log("%s",uint8);
    return sizeof(uint8);
}

size_t log::write(const uint8_t *uint8, size_t size) {
    lv_log("%s",uint8);
    return size;
}
#endif

