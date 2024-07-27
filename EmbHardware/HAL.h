/**
*********************************************************************
*********
* @project_name :lvgl
* @file : HAL.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/4/12 
*********************************************************************
*********
*/
//

#ifndef LVGL_HAL_H
#define LVGL_HAL_H


#include "../../ChipArchConfig.h"
#include "ChipArch/vendor/spdlog/include/spdlog/spdlog.h"
#include "ChipArch/vendor/OtherLib/WString.h"
#include "Display_interface/DisplayInterface.h"
#include "Input_device_interface/InputDeviceInterface.h"
#if IMU
struct ImuData_t
{
    float accelX;
    float accelY;
    float accelZ;
};
#endif
class HAL {
private:
    static HAL * hal_;
    ImuData_t imu_data_={};
protected:
    static DisplayInterface * DisplayInterface_;

    static InputDeviceGroup * InputDeviceGroup_;

    static fileSystemInterface * FileInterface_;
public:
    HAL()=default;

    static HAL * getHal();

    static void initInputDevice(char letter);

    static bool check();

    static void destroy();

    static DisplayInterface *getDisplayInterface();

    static InputDeviceGroup *getInputDeviceGroup();

    static String Type(){ return getHal()->type();};
    virtual String type(){ return "Base";};

    virtual void init(){};

    static bool Inject(HAL * inject,char letter='0');//注入

    static void Delay(unsigned long milliseconds);

#if ESP32&&MCU
    virtual void delay_ms(unsigned long milliseconds);
#else
    virtual void delay(unsigned long milliseconds);
#endif
    static void Display(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p) ;
    virtual void display(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p);

    static void KeyBoardRead(lv_indev_data_t * data);
    virtual void keyboard_read( lv_indev_data_t * data);
#if COMPUTER
    static void  MousePointRead(lv_indev_data_t * data);
    virtual void mouse_point_read( lv_indev_data_t * data);
#elif MCU
    static void  TouchpadPointRead(lv_indev_data_t * data);
    virtual void touchpad_point_read( lv_indev_data_t * data);
#endif
    static void UpDate();
    virtual void update();

    static unsigned long Millis() ;
    virtual unsigned long millis();


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
