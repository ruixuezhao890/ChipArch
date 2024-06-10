/**
*********************************************************************
*********
* @project_name :lvgl
* @file : log.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/4/30 
*********************************************************************
*********
*/
//

#ifndef LVGL_LOG_H
#define LVGL_LOG_H
#include "src/misc/lv_log.h"
class log {
private:
    static log * log_ptr_;
    static void print_cb(const char * massage);
    log()=default;
public:
    static void initLog();
    //默认为printf 进行重载后可更换为自己的串口函数
    virtual void log_print(const char * message);
};


#endif //LVGL_LOG_H
