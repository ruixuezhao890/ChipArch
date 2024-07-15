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
#if 0
namespace SentinelLog{

    class log: public outputStream{
    protected:
       static log * log_ptr_;

       static void print_cb(const char * massage);

       log()=default;

        virtual void log_print(const char * message);

        size_t write(uint8_t uint8) override;

        size_t write(const uint8_t *uint8, size_t size) override;
    public:
        static log* getLogPtr();
        static void initLog();

    };

    log info =*log::getLogPtr();

};
#endif
#endif //LVGL_LOG_H
