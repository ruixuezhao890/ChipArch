/**
*********************************************************************
*********
* @project_name :new_lib
* @file : Serial.cpp
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2024/9/24 
*********************************************************************
*********
*/


#include "Serial.hpp"
#if !FMT_ENABEL_EXIST
template<uint8_t serial_id>
UART_HandleTypeDef* Serial<serial_id>::instance[6] = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};

Serial<0> Serial1(&g_uart1_handle);

#else


#endif