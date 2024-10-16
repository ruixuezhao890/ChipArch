/**
 * @file boot_anim_ascii.cpp
 * @author ruixuezhao890
 * @brief 
 * @version 0.1
 * @date 2023-08-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "boot_anim_ascii.h"
#include "ui/boot_anim_ascii_ui.hpp"
#include "EmbHardware/HAL.h"
using namespace ChipArch_::APPS;

const std::string BootAnim_ASCII::_chipArch_ascii_logo = R"(
    CCCCC  H   H IIIII  PPPPP AAAAA  RRRRR  CCCCC  H   H
    C      HHHHH   I    P   P A   A  R   R  C      HHHHH
    C      H   H   I    PPPPP AAAAA  RRRRR  C      H   H
    CCCCC  H   H IIIII  P     A   A  R   R  CCCCC  H   H
)";

void BootAnim_ASCII::onRunning() {
    
}

void BootAnim_ASCII::onResume(){
    std::string info="bsp init .";
    fmt::newline_info("{} ok",info);
    auto chip=ChipArch_::ChipArch::getChipArchInstance();
    chip->installApp(ChipArch_::ChipArch::getDeskPointInstance());
    chip->createAndStartApp(ChipArch_::ChipArch::getDeskPointInstance()); 
    destroyApp();
}

void BootAnim_ASCII::onPause() {
    APP_BASE::onPause();
}

void *BootAnim_ASCII_Packer::newScreenPacker() {
    return new boot_anim_ascii_ui_packer();
}
