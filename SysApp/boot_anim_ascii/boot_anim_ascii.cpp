/**
 * @file boot_anim_ascii.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-08-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "boot_anim_ascii.h"
#include "ui/boot_anim_ascii_ui.hpp"
using namespace ChipArch_::APPS;

const std::string BootAnim_ASCII::_chipArch_ascii_logo = R"(
    CCCCC  H   H IIIII  PPPPP AAAAA  RRRRR  CCCCC  H   H
    C      HHHHH   I    P   P A   A  R   R  C      HHHHH
    C      H   H   I    PPPPP AAAAA  RRRRR  C      H   H
    CCCCC  H   H IIIII  P     A   A  R   R  CCCCC  H   H
)";

void *BootAnim_ASCII_Packer::newScreenPacker() {
    return new boot_anim_ascii_ui_packer();
}
