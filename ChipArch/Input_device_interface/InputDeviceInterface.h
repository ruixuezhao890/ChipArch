/**
*********************************************************************
*********
* @project_name :lvgl
* @file : InputDeviceInterface.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/5/9 
*********************************************************************
*********
*/
//

#ifndef LVGL_INPUTDEVICEINTERFACE_H
#define LVGL_INPUTDEVICEINTERFACE_H
#include "lvgl/lvgl.h"
#include "ChipArch/ChipArchConfig.h"
#include "ChipArch/App&UI/utils/lvglpp/core/indev.h"//for input
#include "ChipArch/App&UI/utils/lvglpp/core/object.h"// for Object
#include "ChipArch/App&UI/utils/lvglpp/core/display.h" // for scr_act()
#include "ChipArch/App&UI/utils/lvglpp/core/group.h" // for Group
#include "ChipArch/App&UI/utils/lvglpp/core/event.h" // for event
#include "ChipArch/App&UI/utils/lvglpp/draw/image.h"   //for image
#include "ChipArch/App&UI/utils/lvglpp/misc/color.h" // for color
#include "ChipArch/App&UI/utils/lvglpp/misc/fs.h" // for file
#include "ChipArch/App&UI/utils/lvglpp/misc/timer.h" // for timer
#include "ChipArch/App&UI/utils/lvglpp/misc/anim.h" // for Anim
#include "ChipArch/App&UI/utils/lvglpp/widgets/menu/menu.h" // for Anim

#include "ChipArch/App&UI/utils/lvglpp/widgets/image/image.h" // for image

using namespace lvgl::core;
using namespace lvgl::draw;
using namespace lvgl::widgets;
class fileSystemInterface: public FileSystem{
public:
    fileSystemInterface(char letter);
protected:
    bool ready_cb() override;

    void *open_cb(const char *path, lv_fs_mode_t mode) override;

    lv_fs_res_t close_cb(void *file_p) override;

    lv_fs_res_t read_cb(void *file_p, void *buf, uint32_t btr, uint32_t *br) override;

    lv_fs_res_t write_cb(void *file_p, const void *buf, uint32_t btw, uint32_t *bw) override;

    lv_fs_res_t seek_cb(void *file_p, uint32_t pos, lv_fs_whence_t whence) override;

    lv_fs_res_t tell_cb(void *file_p, uint32_t *pos_p) override;

    void *dir_open_cb(const char *path) override;

    lv_fs_res_t dir_read_cb(void *rddir_p, char *fn) override;

    lv_fs_res_t dir_close_cb(void *rddir_p) override;
};

class keyBoardInterface:public KeypadInputDevice{
#if COMPUTER
public:
    keyBoardInterface();
protected:
    void read(lv_indev_data_t *data) override;
#endif
};
class mouseInterface:public PointerInputDevice{
#if COMPUTER
    ImageDescriptor * mouse_picture_scr_;
    Image * mouse_picture_;
public:
    mouseInterface();

protected:
    void read(lv_indev_data_t *data) override;
#endif
};


class InputDeviceGroup{
private:
    Group * group_;

    keyBoardInterface* keyBoardInterface_;

    mouseInterface* mouseInterface_;

    fileSystemInterface * fileSystemInterface_;
public:
    explicit InputDeviceGroup(Display * setDisplay,char letter='0');

    fileSystemInterface *getFileSystemInterface() const;

    keyBoardInterface *getKeyBoardInterface() const;

    mouseInterface *getMouseInterface() const;

    Group *getGroup() const;
};
#endif //LVGL_INPUTDEVICEINTERFACE_H
