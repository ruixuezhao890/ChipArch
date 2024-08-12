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

* 统一底层功能接口：

  ​	在该系统中，我们采用了C++编程语言，通过定义一个名为`Hal`的抽象类，对底层硬件调用实现了统一的接口。这样的设计策略是为了实现对不同开发板环境的兼容性。在`Hal`抽象类中，我们使用了虚函数来定义对底层功能的访问接口。

  当需要在新的硬件平台上进行开发时，只需继承`Hal`抽象类，并对其中的虚函数进行重写，即可完成平台的迁移。这种方法极大地提高了代码的可移植性和可维护性，同时也降低了系统与硬件之间的耦合度。

  采用了依赖注入的技术，将重写后的子类实例化对象进行绑定，从而实现了对底层硬件的控制。依赖注入技术使得系统在运行时能够动态地替换或者添加新的依赖，进一步提高了系统的灵活性和可扩展性。

  总的来说，通过使用C++的抽象类和虚函数，结合依赖注入技术，成功地实现了一个既灵活又可扩展的硬件抽象层

* 生命周期调度框架：

​		使用状态机的方式对抽象出来的应用程序（AppPackage管理Application创建与释放，图片资源等）进行了管理。

​		通过名为`app_creat_buff_map`的映射来存储和管理所有的应用程序实例。每一个应用程序实例都与一个`AppLifecycle_t`对象关联，该对象包含了应用程序的状态信息和对应的应用程序对象。

​	

* c++风格的面向对象的lvgl：

	* 其他：

		1. lvgl中存在log(日志)，我将其使用c++风格进行管理，通过虚函数控制接口可以实现log输出的输出接口，该日志默认输出接口是printf，但是在单片机中，如arduino中串口输出为serial时我们可以在log进行绑定对应串口输出接口即可真确输出串口（前提是串口正常初始化）
		1. 

## 安装

*  克隆仓库

​	

* 添加文件对应指定路径

* 编写对应底层驱动

## 使用说明

* 如果你想创建一个应用 ，文件夹中存在一个python文件可以自动化完成这一切操作你只需要选择是创建系统应用还是用户应用即可，会自动添加至调用函数中，进行创建与安装。具体操作如下：

​		![image-20240812225106356](D:\lvgl\lvgl_template_v8.3\ChipArch\git_src\git_pic\pic1.png)

右键运行它，运行之后会出现：choice S or U 'S' mean system application 'U' mean user application。这个提示，就是选择系统还是用户，在出现它之前还会提示不要输入一些字符否则会出错，就算出错了，删除生成的文件夹，再次按照正确的步骤进行生成即可。

选择之后会提示输入你想生成的应用的名字，在同样的目录下名字只能出现一次，否则会出现错误，此时重新运行该脚本即可再次创建。

创建完成之后，创建出来的应用目录结构如下：（这里以用户应用desk为例子）

<img src="D:\lvgl\lvgl_template_v8.3\ChipArch\git_src\git_pic\pic2.png" alt="pic2" style="zoom:0%;" />

在创建完成之后会出一个package结尾的类：

<img src="D:\lvgl\lvgl_template_v8.3\ChipArch\git_src\git_pic\pic3.png" alt="pic3" style="zoom: 67%;" />



app本体类：

<img src="D:\lvgl\lvgl_template_v8.3\ChipArch\git_src\git_pic\pic4.png" alt="pic4" style="zoom:50%;" />

app的界面类：

<img src="D:\lvgl\lvgl_template_v8.3\ChipArch\git_src\git_pic\pic5.png" alt="pic5" style="zoom:67%;" />

依据函数的名称，完成对应的功能，app就算成功了

