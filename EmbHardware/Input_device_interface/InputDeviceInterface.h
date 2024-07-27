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
#include "lvgl.h"
#include "../../AppUI/utils/lvglpp/core/log.h"
#include "../../AppUI/utils/lvglpp/core/indev.h"//for input
#include "../../AppUI/utils/lvglpp/core/object.h"// for Object
#include "../../AppUI/utils/lvglpp/core/display.h" // for scr_act()
#include "../../AppUI/utils/lvglpp/core/group.h" // for Group
#include "../../AppUI/utils/lvglpp/core/event.h" // for event
#include "../../AppUI/utils/lvglpp/draw/image.h"   //for image
#include "../../AppUI/utils/lvglpp/misc/color.h" // for color
#include "../../AppUI/utils/lvglpp/misc/fs.h" // for file
#include "../../AppUI/utils/lvglpp/misc/timer.h" // for timer
#include "../../AppUI/utils/lvglpp/misc/anim.h" // for Anim
#include "../../AppUI/utils/lvglpp/widgets/menu/menu.h" // for Anim
#include "../../AppUI/utils/lvglpp/widgets/button/button.h" // for button
#include "../../AppUI/utils/lvglpp/widgets/label/label.h" // for label
#include "../../AppUI/utils/lvglpp/widgets/image/image.h" // for image

using namespace lvgl::core;
using namespace lvgl::draw;
using namespace lvgl::widgets;
class fileSystemInterface: public FileSystem{
public:
    explicit fileSystemInterface(char letter);
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
#if COMPUTER
class keyBoardInterface:public KeypadInputDevice{

public:
    keyBoardInterface();
protected:
    void read(lv_indev_data_t *data) override;

};
class mouseInterface:public PointerInputDevice{

    ImageDescriptor * mouse_picture_scr_;
    Image * mouse_picture_;
public:
    mouseInterface();

protected:
    void read(lv_indev_data_t *data) override;



};
#elif MCU


#endif

class InputDeviceGroup{
private:
    Group * group_;
#if COMPUTER
    keyBoardInterface * keyBoardInterface_;

    mouseInterface* mouseInterface_;
#endif
    fileSystemInterface * fileSystemInterface_;
public:
    explicit InputDeviceGroup(Display * setDisplay,char letter='0');

    fileSystemInterface *getFileSystemInterface() const;
#if COMPUTER
    keyBoardInterface *getKeyBoardInterface() const;

    mouseInterface *getMouseInterface() const;
#endif
    Group *getGroup() const;
};
#endif //LVGL_INPUTDEVICEINTERFACE_H
