/**
*********************************************************************
*********
* @project_name :lvgl
* @file : HAL.h
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2024/4/12 
*********************************************************************
*********
*/
//

#ifndef LVGL_HAL_H
#define LVGL_HAL_H

#include "lvgl.h"
#include "PubInculde.hpp"
#include "vendor/SimpleString/WString.h"


#if ESP32
bool is_pointer_in_psram(void* ptr);
#endif
#if IMU
struct ImuData_t
{
    float accelX;
    float accelY;
    float accelZ;
};
#endif

LV_FONT_DECLARE(FONT_NAME)

class HAL {
private:
    static HAL * hal_;
    
    static lv_style_t style_font;

    ImuData_t imu_data_={0,0,0};
protected:
    
public:
    HAL()=default;

    static HAL * getHal();

//    static void initInputDevice(char letter);

    static bool check();

    static void destroy();

   

    static String Type(){ return getHal()->type();};
    virtual String type(){ return "Base";};

    virtual void init(){};

    static bool Inject(HAL * inject,char letter='0');//注入

    static void Loadfont();

    static void Setfont(lv_obj_t* set_obj,const char * setchar,lv_color_t value=lv_color_black());


    static void Delay(unsigned long milliseconds);

    static void Os_delay(unsigned long millisenconds);

    virtual void os_delay(unsigned long millisenconds);
#if ESP32&&MCU
    virtual void delay_ms(unsigned long milliseconds);
#else
    virtual void delay(unsigned long milliseconds);
#endif
    static void Display(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p) ;
    virtual void display(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p);

    static void Display_GPU(lv_disp_drv_t * disp_drv, lv_color_t * dest_buf, lv_coord_t dest_width,const lv_area_t * fill_area, lv_color_t color);
    virtual void display_GPU(lv_disp_drv_t * disp_drv, lv_color_t * dest_buf, lv_coord_t dest_width,const lv_area_t * fill_area, lv_color_t color){
//     uint16_t w = ex-sx+1;
//     uint16_t h = ey-sy+1;

//     lcd_set_window(sx, sy, w, h);
//     uint32_t draw_size = w * h;
//     lcd_write_ram_prepare();

//     for(uint32_t i = 0; i < draw_size; i++)
//     {
//         lcd_wr_data(color[i]);
//     }
    };

    static void KeyBoardRead(lv_indev_data_t * data);
    virtual void keyboard_read( lv_indev_data_t * data);
#if COMPUTER
    static void  MousePointRead(lv_indev_data_t * data);
    virtual void mouse_point_read( lv_indev_data_t * data);
#elif MCU

    static void  TouchpadPointRead(lv_indev_drv_t * indev_drv,lv_indev_data_t *data);
    virtual void touchpad_point_read( lv_indev_drv_t * indev_drv,lv_indev_data_t *data);

    static void Toggle_LED(uint8_t id);
    virtual void toggle_LED(uint8_t id);

#endif

    static void Up_Data();
    virtual void up_data_();

    static void  Up_data_lvgl();


    static  void Microseconds_delay(unsigned long milliseconds) ;
    virtual void microseconds_delay(unsigned long milliseconds);


    static void PowerOff() ;
    virtual void powerOff();


    static void Reboot() ;
    virtual void reboot();

    static void VolumeStart( const String& filePath);
    virtual void volumeStart(const String& filePath);

    static void VolumeStop();
    virtual void volumeStop() ;


    static void SetVolume(uint8_t volume);
    virtual void setVolume(uint8_t volume) ;

    static bool CheckSdCard();
    virtual bool checkSdCard();

    //todo 将蓝屏封装为一个软件 通过软件来抛出蓝屏 为了不直接调用底层接口使用lvgl进行抛出蓝屏
    //todo 通过软件调用也符合整体的解耦逻辑 通过设置开启还是关闭的标志位进行抛出
    static void PopFatalError( const String& msg) ;
    virtual void popFatalError(const String& msg);

    static bool GetAnyButton();
    virtual bool getAnyButton();

#if IMU
    static void UpdateImuData();
    virtual void updateImuData();

    static ImuData_t& GetImuData();
    ImuData_t& getImuData();
#endif
};


#endif //LVGL_HAL_H
