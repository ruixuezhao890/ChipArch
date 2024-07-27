/**
*********************************************************************
*********
* @project_name :lvgl
* @file : AppMessagePipe.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/7/25 
*********************************************************************
*********
*/
//

#ifndef LVGL_APPMESSAGEPIPE_H
#define LVGL_APPMESSAGEPIPE_H
#include "ChipArch/ChipArchConfig.h"
#include "ChipArch/vendor/ETL/ETLibrary/include/etl/multimap.h"
#include "ChipArch/vendor/ETL/ETLibrary/include/etl/map.h"
#include "ChipArch/vendor/ETL/ETLibrary/include/etl/vector.h"
#include "ChipArch/vendor/ETL/ETLibrary/include/etl/function.h"
#include "ChipArch/vendor/OtherLib/WString.h"
using namespace etl;
constexpr uint8_t num=8;
const String None("none");
const String Error_APP_Label("blue_screen");
using MessageDataMap=map<uint8_t, String, MESSAGE_NUM>;
template<uint8_t message_num>
using BatchModifyVector=const vector<pair<String, MessageDataMap>, message_num>;

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

//    // 批量添加消息
//    template<uint8_t message_num>//todo 新写一个类来完成这件事情吧
//    static void batchAddMessages(const vector<pair<String, MessageDataMap>,message_num>& messages);

    // 获取所有消息
    static MessageDataMap getAllMessages(const String& appName);

    // 清空消息管道
    static void removeAllMessages();

    static void removeSpecifiedMessages(const String& appName);

};
using message_pipe=AppMessagePipe;

#endif //LVGL_APPMESSAGEPIPE_H
