// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.3
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#ifndef _SQUARELINE_PROJECT_UI_H
#define _SQUARELINE_PROJECT_UI_H

#include "ChipArch/App&UI/PageManage/PageManage.h"
#include "ChipArch/App&UI/AppManage/ApplicationManage/ApplicationManage.h"

class AppPackage;
LV_IMG_DECLARE( ui_img_launchbackground1_png);   // assets\launchBackground1.png
LV_IMG_DECLARE( ui_img_wifi_png);   // assets\WIFI.png
LV_IMG_DECLARE( ui_img_ble_png);   // assets\BLE.png

class ap_desk_ui: public Page{
private:
    struct DeskDraw{
        lv_obj_t * plank_;
        lv_obj_t *ui_Screen1_;
        lv_obj_t *ui_Panel1_;
        lv_obj_t *ui_Label1_;
        lv_obj_t *ui_WIFI_;
        lv_obj_t *ui_BLE_;
        lv_obj_t *ui_Label2_;
        std::vector<lv_obj_t *> buttonVec_;
        std::vector<String> app_name_Vec_;
        std::map<String, ImageDescriptor*> load_picture_;
        etl::map<String, AppPackage*, max_app_num>* map_;
        String control_now_app_;
        uint16_t AnimTime = 1000;
        uint16_t DelayAnimTime = 800;
        uint8_t control_now_app_index = 0;
        bool initial_loading_flag_ = true;
    };
    DeskDraw draw_desk_attribute;

public:
    ap_desk_ui(const String &band_app_);

    void init() override;

    void exit() override;

    bool getScreenOrientation() override;

    ~ap_desk_ui() override;

    String & getNowAppName() override;


protected:

    static const uint8_t icon_size=60;

    void initializeDeskUI();

    void loadImage(const String& app_name, lv_obj_t *button, uint8_t defaultWidth= icon_size, uint8_t defaultHeight= icon_size);

    void setPlankAnim() const;

    static void upDataScrollIcon(lv_event_t *e);

    static void openDeskIcon(lv_event_t * e);

    void deleteResources() ;
public:
    void drawDeskIcon( etl::map<String, AppPackage*, max_app_num> &list);

    void scrollLeft();
    
    void scrollRight();

    void scrollOpen();


};








#endif