/**
*********************************************************************
*********
* @project_name :lvgl
* @file : AppMessagePipe.cpp
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2024/7/25
*********************************************************************
*********
*/
//

#include "AppMessagePipe.h"
//#include "spdlog/spdlog.h"

multimap<String,MessageDataMap,MESSAGE_NUM>AppMessagePipe:: container;

void AppMessagePipe::addMessage(const String &appName, uint8_t type, const String &message) {
#if FREERTOS
    //进入临界区
#endif
    auto item=container.find(appName);

    if (item!=container.end()){
        //存在则直接替换
        item->second[type]=message;
    }else{
        MessageDataMap subContainer;
        subContainer[type] = message;
        pair<String, MessageDataMap>  make_pair(appName,subContainer);
        container.insert(make_pair);
    }
#if FREERTOS
    //退出临界区
#endif
}

pair<bool, String> AppMessagePipe::getMessage(const String& appName,uint8_t id) {
#if FREERTOS
    //进入临界区
#endif
    auto it= find_if(container.begin(),container.end(),[&appName,&id](const pair<String,map<uint8_t, String,MESSAGE_NUM>>& pair_){
        return pair_.first&&pair_.second.find(id)!=pair_.second.end();
    });
    String get_message=None;
    // 如果找到了元素，返回 true 和对应的值
    if (it != container.end()) {
        get_message=it->second.at(id);
        if (removeMessage(appName,id)){


#if FREERTOS
        //退出临界区
#endif
            etl::pair<bool,String> t(true, get_message);
            return t;
        }
    }

#if FREERTOS
    //退出临界区
#endif
    // 如果没有找到子键，返回 false 和空字符串
    return std::make_pair(false, get_message);
}

bool AppMessagePipe::removeMessage(const String &appName, uint8_t id) {
#if FREERTOS
    //进入临界区
#endif
    // 使用 equal_range 查找与给定键匹配的所有条目
    auto range = container.equal_range(appName);
    bool found = false;

    // 遍历找到的条目
    for (auto it = range.first; it != range.second; ++it) {
        // 查找与给定子键匹配的条目
        auto subIt = it->second.find(id);
        if (subIt != it->second.end()) {
            // 找到了匹配的条目，移除它
            it->second.erase(subIt);
            found = true;
            // 调用消息删除监听器
//            onMessageRemoved(appName, id);
        }
    }
#if FREERTOS
    //退出临界区
#endif
    // 如果找到匹配的条目，则返回 true；否则返回 false
    return found;
}

bool AppMessagePipe::modifyMessage(const String &appName, uint8_t id, const String &newMessage) {
#if FREERTOS
    //进入临界区
#endif
    // 使用 equal_range 查找与给定键匹配的所有条目
    auto range = container.equal_range(appName);
    bool found = false;

    // 遍历找到的条目
    for (auto it = range.first; it != range.second; ++it) {
        // 查找与给定子键匹配的条目
        auto subIt = it->second.find(id);
        if (subIt != it->second.end()) {
            // 找到了匹配的条目，更新其消息内容
            subIt->second = newMessage;
            found = true;
            // 调用消息更新监听器
//            onMessageUpdated(appName, id, newMessage);
        }
    }
#if FREERTOS
    //退出临界区
#endif
    // 如果找到匹配的条目，则返回 true；否则返回 false
    return found;

}


MessageDataMap  AppMessagePipe::getAllMessages(const String &appName) {
    auto range = container.find(appName);
    MessageDataMap dataMap;
    if (range==container.end()){
        return dataMap;
    }
//    vector<MessageDataMap,num> result;

    uint8_t i=0;
    // 遍历找到的条目
    for (auto it=range->second.begin();it!=range->second.end();it++) {
        // 添加每个条目到结果中

        dataMap.insert(pair<uint8_t,String>(it->first,it->second));
         i++;
    }
    removeSpecifiedMessages(appName);
    return dataMap;
}

void AppMessagePipe::removeAllMessages() {
   container.clear();
}

void AppMessagePipe::removeSpecifiedMessages(const String &appName) {
  auto it=container.find(appName);
  it->second.clear();
}

//template<uint8_t message_num>
//void AppMessagePipe::batchAddMessages(const vector<pair<String, MessageDataMap>, message_num> &messages) {
//    for (const auto& message : messages) {
//        // 调用 addMessage 方法添加消息
//        addMessage(message.first, message.second.begin()->first, message.second.begin()->second);
//    }
//}
