/**
*********************************************************************
*********
* @project_name :lvgl
* @file : AppMessagePipe.h
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2024/7/25
*********************************************************************
*********
*/
//

#ifndef LVGL_APPMESSAGEPIPE_H
#define LVGL_APPMESSAGEPIPE_H
#include "ChipArchConfig.h"
#include "vendor/ETL/ETLibrary/include/etl/multimap.h"
#include "vendor/ETL/ETLibrary/include/etl/map.h"
#include "vendor/ETL/ETLibrary/include/etl/vector.h"
#include "vendor/ETL/ETLibrary/include/etl/function.h"
#include "vendor/SimpleString/WString.h"
using namespace etl;
constexpr uint8_t num_message=16;
const String None("none");
const String Error_APP_Label("blue_screen");
using MessageDataMap=map<uint8_t, String, num_message>;

class AppMessagePipe{
protected:
    static multimap<String,MessageDataMap,MESSAGE_NUM> container;
public:
    static void addMessage(const String &appName, uint8_t id, const String &message);

    static pair<bool,String> getMessage(const String& appName,uint8_t id);

    // 删除消息
    static bool removeMessage(const String& appName, uint8_t id);

    // 更新消息
    static bool modifyMessage(const String& appName, uint8_t id, const String& newMessage);

    // 获取所有消息
    static MessageDataMap getAllMessages(const String& appName);

    // 清空消息管道
    static void removeAllMessages();

    static void removeSpecifiedMessages(const String& appName);

};
using message_pipe=AppMessagePipe;

#endif //LVGL_APPMESSAGEPIPE_H
