# ChipArch

为单片机开发的多应用程序生命周期调度框架，采用工厂模式来结构化应用程序的设计，简化应用程序启动器的设计，并提高代码的复用性。

The multi-application life cycle scheduling framework developed for single-chip microcomputer uses factory pattern to structure the design of application program, simplify the design of application initiator and improve the reusability of code.

---

## 简介
本项目旨在为单片机开发一个多应用程序生命周期调度框架。该框架通过采用工厂模式来结构化应用程序的设计，不仅简化了应用程序启动器的设计，还显著提高了代码的复用性。此外，项目统一了单片机对底层接口的管理，使开发者能够更高效地进行开发和维护。

项目还支持快速进行LVGL（Light and Versatile Graphics Library）的移植与开发。通过对LVGL进行封装，支持C++风格的面向对象开发，使得图形用户界面的开发更加简洁和高效。总体而言，本项目解决了单片机多应用管理复杂、底层接口不统一、图形界面开发困难等问题，为单片机开发者提供了一个高效、易用的开发框架。

---

## SDK目录树

```hxml
├─App&UI
│  ├─AppInstall
│  ├─AppManage
│  │  ├─Application
│  │  └─ApplicationManage
│  ├─PageManage
│  └─utils
│      └─lvglpp                                                                                              
├─ChipArch
│  ├─Display_interface
│  └─Input_device_interface
├─EmbHardware
│  └─Solitude
├─examples
├─SysApp
│  ├─app_desk
│  │  ├─assets
│  │  └─ui
│  ├─app_setting
│  │  ├─assets
│  │  └─ui
│  └─app_template
│      ├─assets
│      └─ui
├─UserApp
│  └─testApp
└─vendor
    ├─ETL                                                                                          
    ├─OtherLib
    └─Tools
```

---

## 功能特性

* 统一接口：

​		

* 生命周期调度框架：



* c++风格的面向对象的lvgl：

​	

## 安装

*  克隆仓库

​	

* 添加文件对应指定路径

* 编写对应底层驱动

## 使用说明

