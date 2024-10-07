#include "lv_port_indev.h"
#include "EmbHardware/HAL.h"


#if ESP32
#include "Touch_CST328.h"
#elif STM32

#elif COMPUTER
    #include "lv_drivers/sdl/sdl.h"

    lv_indev_t * indev_mouse;       // 鼠标
    lv_indev_t * indev_keypad;      // 键盘
#endif

//lv_indev_t * indev_mouse;       // 鼠标
//lv_indev_t * indev_keypad;      // 键盘
//lv_indev_t * indev_encoder;     // 编码器
//lv_indev_t * indev_button;      // 按钮
#if TOUCH_PORT

lv_indev_t * indev_touchpad;    // 触摸屏

 void touch_pad_init(){


     Touch_Init();

    static lv_indev_drv_t indev_drv;
    
    /* 注册触摸屏输入设备 */
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = HAL::TouchpadPointRead;
    indev_touchpad = lv_indev_drv_register(&indev_drv);
}

#endif

void lv_port_indev_init(void){
#if TOUCH_PORT
        touch_pad_init();
#endif
#if COMPUTER
    lv_group_t * g = lv_group_create();
    lv_group_set_default(g);

    /* Add the mouse as input device
     * Use the 'mouse' driver which reads the PC's mouse*/
    static lv_indev_drv_t indev_drv_1;
    lv_indev_drv_init(&indev_drv_1); /*Basic initialization*/
    indev_drv_1.type = LV_INDEV_TYPE_POINTER;

    /*This function will be called periodically (by the library) to get the mouse position and state*/
    indev_drv_1.read_cb = sdl_mouse_read;
    lv_indev_t *mouse_indev = lv_indev_drv_register(&indev_drv_1);

    static lv_indev_drv_t indev_drv_2;
    lv_indev_drv_init(&indev_drv_2); /*Basic initialization*/
    indev_drv_2.type = LV_INDEV_TYPE_KEYPAD;
    indev_drv_2.read_cb = sdl_keyboard_read;
    kb_indev= lv_indev_drv_register(&indev_drv_2);
    lv_indev_set_group(kb_indev, g);

    static lv_indev_drv_t indev_drv_3;
    lv_indev_drv_init(&indev_drv_3); /*Basic initialization*/
    indev_drv_3.type = LV_INDEV_TYPE_ENCODER;
    indev_drv_3.read_cb = sdl_mousewheel_read;
    lv_indev_t * enc_indev = lv_indev_drv_register(&indev_drv_3);
    lv_indev_set_group(enc_indev, g);

    /*Set a cursor for the mouse*/
    LV_IMG_DECLARE(mouse_cursor_icon); /*Declare the image file.*/
    lv_obj_t * cursor_obj = lv_img_create(lv_scr_act()); /*Create an image object for the cursor */
    lv_img_set_src(cursor_obj, &mouse_cursor_icon);           /*Set the image source*/
    lv_indev_set_cursor(mouse_indev, cursor_obj);             /*Connect the image  object to the driver*/
#endif
    
}