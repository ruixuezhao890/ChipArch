/**
*********************************************************************
*********
* @project_name :lvgl
* @file : InputDeviceInterface.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/5/9 
*********************************************************************
*********
*/
//
#include "InputDeviceInterface.h"
#include "ChipArch/EmbHardware/Solitude/Solitude.h"
#if COMPUTER
extern const uint8_t mouse_cursor_icon_map[];//鼠标图标资源

void keyBoardInterface::read(lv_indev_data_t *data) {
    HAL::KeyBoardRead(data);
}

keyBoardInterface::keyBoardInterface():KeypadInputDevice() {
   this->update_driver();
}


mouseInterface::mouseInterface():PointerInputDevice() {
    //创建鼠标图片
    mouse_picture_scr_=new ImageDescriptor();
    mouse_picture_=new Image(scr_act());

    mouse_picture_scr_->set_src(mouse_cursor_icon_map,14, 20, LV_IMG_CF_TRUE_COLOR_ALPHA);
    mouse_picture_scr_->raw_ptr()->header.always_zero=0;
    mouse_picture_->set_src(*mouse_picture_scr_);
    this->set_cursor(*mouse_picture_);
    //更新设备
    this->update_driver();
}

//重写回调函数读取
void mouseInterface::read(lv_indev_data_t *data) {
   HAL::MousePointRead(data);
}
#endif


fileSystemInterface::fileSystemInterface(char letter) : FileSystem(letter) {

}

bool fileSystemInterface::ready_cb() {
    return false;
}

void *fileSystemInterface::open_cb(const char *path, lv_fs_mode_t mode) {
    return nullptr;
}

lv_fs_res_t fileSystemInterface::close_cb(void *file_p) {
    return 0;
}

lv_fs_res_t fileSystemInterface::read_cb(void *file_p, void *buf, uint32_t btr, uint32_t *br) {
    return 0;
}

lv_fs_res_t fileSystemInterface::write_cb(void *file_p, const void *buf, uint32_t btw, uint32_t *bw) {
    return 0;
}

lv_fs_res_t fileSystemInterface::seek_cb(void *file_p, uint32_t pos, lv_fs_whence_t whence) {
    return 0;
}

lv_fs_res_t fileSystemInterface::tell_cb(void *file_p, uint32_t *pos_p) {
    return 0;
}

void *fileSystemInterface::dir_open_cb(const char *path) {
    return nullptr;
}

lv_fs_res_t fileSystemInterface::dir_read_cb(void *rddir_p, char *fn) {
    return 0;
}

lv_fs_res_t fileSystemInterface::dir_close_cb(void *rddir_p) {
    return 0;
}





InputDeviceGroup::InputDeviceGroup(Display *setDisplay,char letter) {
    group_=new Group();
#if COMPUTER
    keyBoardInterface_=new keyBoardInterface();
    mouseInterface_=new mouseInterface();
#endif
    if (letter!='0'){
        fileSystemInterface_=new fileSystemInterface(letter);
    }else{
        fileSystemInterface_= nullptr;
    }

//    group_->set_default();

    keyBoardInterface_->set_display(*setDisplay);
    mouseInterface_->set_display(*setDisplay);

    keyBoardInterface_->set_group(*group_);

}

fileSystemInterface *InputDeviceGroup::getFileSystemInterface() const {
    return fileSystemInterface_;
}
#if COMPUTER
keyBoardInterface *InputDeviceGroup::getKeyBoardInterface() const {
    return keyBoardInterface_;
}

mouseInterface *InputDeviceGroup::getMouseInterface() const {
    return mouseInterface_;
}
#else
keyBoardInterface *InputDeviceGroup::getKeyBoardInterface() const {
    return nullptr;
}

mouseInterface *InputDeviceGroup::getMouseInterface() const {
    return nullptr;
}
#endif
Group *InputDeviceGroup::getGroup() const {
    return group_;
}






