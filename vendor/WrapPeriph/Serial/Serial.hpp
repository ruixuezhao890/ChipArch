/**
*********************************************************************
*********
* @project_name :new_lib
* @file : Serial.hpp
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2024/9/24 
*********************************************************************
*********
*/


#ifndef NEW_LIB_SERIAL_HPP
#define NEW_LIB_SERIAL_HPP
#include "./ChipArchConfig.h"

#if FMT_ENABEL_EXIST

#if ESP32
#include "HardwareSerial.h"
#include "fmt/format.h"
#elif STM32

#elif COMPUTER

#endif
#define FMT_HEADER_ONLY
#include "fmt/core.h"
#include "lvgl.h"
#include <string>
#include <iostream> // 包含标准输入输出流头文件
 #include "vendor/SimpleString/WString.h"
namespace fmt{
    template <typename... Args>
    void info(const char *format, Args &&...args){
        std::string receive = fmt::format(format, std::forward<Args>(args)...);
#if ESP32
        Serial.print(receive.c_str());
#elif STM32
#else
        std::cout<<receive;
#endif
    }
    
    template <typename... Args>
    void newline_info(const char *format, Args &&...args){
       std::string receive = fmt::format(format, std::forward<Args>(args)...);
#if ESP32
        Serial.println(receive.c_str());
#elif STM32
#else
        std::cout<<receive<<std::endl;

#endif
    }
 }
#else
#include "./SYSTEM/usart/usart.h"


template<uint8_t serial_id>
class Serial {
   static UART_HandleTypeDef * instance[6];
protected:
   static void putchar(char character){
       HAL_UART_Transmit(instance[serial_id],(uint8_t *)&character,1,HAL_MAX_DELAY);
   }
public:
    explicit Serial(UART_HandleTypeDef * set){
        instance[serial_id]=set;
    }

    template <typename... Args>
    static size_t print(const char *format, Args &&...args);
    template <class out_class_t, typename... Args>
    static size_t print(const char *format, Args &&...args);
    template <typename... Args>
    static size_t println(const char *format, Args &&...args);
    template <class out_class_t, typename... Args>
    static size_t println(const char *format, Args &&...args);

};


/**
 * @brief 格式化发送字符串
 *
 * @tparam Base
 * @tparam Args
 * @param format 格式化字符串
 * @param args 占位符对应的参数
 */
template<uint8_t serial_id>
template <typename... Args>
size_t Serial<serial_id>::print(const char *format, Args &&...args)
{
    return fmt::format_to(putchar, format, args...);
}

/**
 * @brief 格式化发送字符串
 *
 * @tparam Base
 * @tparam Args
 * @param format 格式化字符串
 * @param args 占位符对应的参数
 */
template<uint8_t serial_id>
template <class out_class_t, typename... Args>
size_t Serial<serial_id>::print(const char *format, Args &&...args)
{
    struct _out_class_t : public out_class_t
    {
        void operator()(char character) { putchar(character); }
    };

    return fmt::format_to(_out_class_t(), format, args...);
}

/**
 * @brief 格式化发送字符串并换行
 *
 * @tparam Base
 * @tparam Args
 * @param format 格式化字符串
 * @param args 占位符对应的参数
 */
template<uint8_t serial_id>
template <typename... Args>
size_t Serial<serial_id>::println(const char *format, Args &&...args)
{
    size_t retval = fmt::format_to(putchar, format, args...);
    putchar('\n');
    return retval;
}

/**
 * @brief 格式化发送字符串并换行
 *
 * @tparam Base
 * @tparam Args
 * @param format 格式化字符串
 * @param args 占位符对应的参数
 */
template<uint8_t serial_id>
template <class out_class_t, typename... Args>
size_t Serial<serial_id>::println(const char *format, Args &&...args)
{
    struct _out_class_t : public out_class_t
    {
        void operator()(char character) { putchar(character); }
    };

    size_t retval = fmt::format_to(_out_class_t(), format, args...);
    putchar('\n');
    return retval;
}


   namespace fmt{
    template <typename... Args>
    void info(const char *format, Args &&...args){
        std::string receive = fmt::format(format, std::forward<Args>(args)...);
        Serial.print(receive.c_str());
    }
    
    template <typename... Args>
    void newline_info(const char *format, Args &&...args){
        std::string receive = fmt::format(format, std::forward<Args>(args)...);
        Serial.println(receive.c_str());
    }
 } 
#endif

#endif //NEW_LIB_SERIAL_HPP
