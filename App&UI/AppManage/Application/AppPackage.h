/**
*********************************************************************
*********
* @project_name :lvgl
* @file : AppPackage.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/4/25 
*********************************************************************
*********
*/
//

#ifndef LVGL_APPPACKAGE_H
#define LVGL_APPPACKAGE_H

struct Page;
class AppPackage {
private:
    void* framework_;
public:
    AppPackage() : framework_(nullptr) {}
    virtual ~AppPackage() {}

    // Framework pointer
    inline void setFramwork(void* userData) { framework_ = userData; }
    inline void* getFramwork() { return framework_; }

    // Self pointer
    inline AppPackage* getAddr() { return this; }

    /* ------------------------------- App factory ------------------------------ */
public:

    virtual void* newApp() { return nullptr; }

    virtual void deleteApp(void* app) {}



    /* -------------------------- Basic app static data ------------------------- */
public:

    virtual const char* getAppName() { return ""; };

    virtual void* getAppIcon() { return nullptr; };

    virtual void* getCustomData() { return nullptr; }
};


#endif //LVGL_APPPACKAGE_H
