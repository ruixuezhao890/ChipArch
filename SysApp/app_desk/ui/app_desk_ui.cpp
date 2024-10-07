/**
*********************************************************************
*********
* @project_name :micro_snow
* @file : app_desk_ui.cpp
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2024/10/3 
*********************************************************************
*********
*/


#include "app_desk_ui.hpp"
#include "ChipArch/ChipArch.h"
#include "AppUI/AppManage/Application/app.h"

/* 声明一个变量来存储上次点击的时间 */
static uint32_t last_click_time = 0;
/* 定义双击的最大间隔时间（毫秒） */
#define DOUBLE_CLICK_MAX_INTERVAL 300

app_desk_ui::app_desk_ui(lv_pm_page_t* lv_pm_page_set):SCREEN_BASE(lv_pm_page_set) {

}

app_desk_widget *app_desk_ui::getWidget() {
    return static_cast<app_desk_widget*>(getScreenPacker()->getWidgetStruct());
}
/**
* 事件回调函数
*/
static void scroll_event_cb(lv_event_t * e)
{
    //>>>>>>>>>>>-----------------<!>---Link
    ///E1.----------------------------得到容器
    lv_obj_t * cont = lv_event_get_target(e); //通过绑定了该事件的对象，来获取这个对象
    auto desk_ui= (app_desk_ui *)lv_event_get_user_data(e);
    ///E2.---------------------------通过一定算法，得到容器的y轴中心位置（目的：用于后面与子元素按钮进行y轴中心偏差比较）
    lv_area_t cont_a; //区域 cont_area
    lv_obj_get_coords(cont, &cont_a); //将cont的坐标赋值给cont_a (将cont_a约束为container的大小（200 * 200)  coords：坐标(x1,y1); (x2,y1); (x1,y2); (x2,y2)

    lv_coord_t cont_y_center = cont_a.y1 + lv_area_get_height(&cont_a) / 2; //获取Container的y轴中心

    lv_coord_t r = lv_obj_get_height(cont) * 7 / 10; // 200*7 / 10 = 140

    uint32_t i;
    uint32_t child_cnt = lv_obj_get_child_cnt(cont); //child_cnt : child count 儿子数量 获取container里面元素个数

    ///E3.------------------遍历容器里面的子元素（按钮），以便操作这些元素的属性（用户垂直滚动时候，按钮发生水平偏移，并且设置不同的透明度）
    for(i = 0; i < child_cnt; i++)  //遍历Buttons
    {
        lv_obj_t * child = lv_obj_get_child(cont, i); //获取container的第i个button
        lv_area_t child_a; //创建一个属于儿子区域
        lv_obj_get_coords(child, &child_a); //将child_a约束为button的大小（200 * 200）
        lv_coord_t child_y_center = child_a.y1 + lv_area_get_height(&child_a) / 2; //计算得到button的y轴中心

        lv_coord_t diff_y = child_y_center - cont_y_center; // button的y轴中心 - Container的y轴中心 = Button相对于Container的垂直偏差
        diff_y = LV_ABS(diff_y); // 对偏差取绝对值（ABS）

        ///E3.1------------------根据偏差（按钮相对于容器的y方向中心位置）来产生不同的x值
        /*Get the x of diff_y on a circle.*/
        lv_coord_t x;
        /*If diff_y is out of the circle use the last point of the circle (the radius)*/
        if(diff_y >= r) // diff_y >= 140
        {
            x = r; //x = 140
        }
        else     // diff_y < 140
        {
            /*Use Pythagoras theorem to get x from radius and y*/
            uint32_t x_sqr = r * r - diff_y * diff_y; // 140 * 140  - diff_y的平方
            lv_sqrt_res_t res;
            lv_sqrt(x_sqr, &res, 0x8000);   /*Use lvgl's built in sqrt root function*/
            x = r - res.i;
        }
        ///E3.2--------------------根据x值，将button移动x个单位距离，根据r映射出不同的透明度值，设置按钮不同透明度
        /*Translate the item by the calculated X coordinate*/
        lv_obj_set_style_translate_x(child, x, 0); //将button 移动 x个单位距离

        /*Use some opacity with larger translations*/
        lv_opa_t opa = lv_map(x, 0, r, LV_OPA_TRANSP, LV_OPA_COVER);  //通过r的不同值，动态映射创建不透明度值 opa: opacity
        auto opa_value=LV_OPA_COVER - opa;
        lv_obj_set_style_opa(child, opa_value, 0); //给按钮应用不透明度值  opa: opacity
        if (opa_value==LV_OPA_COVER){
            auto label=desk_ui->getWidget()->app_name_label;
            lv_obj_t * child_label = lv_obj_get_child(child, 0); //button的子类
            auto set_text=lv_label_get_text(child_label);
            lv_label_set_text(label,set_text);
        }
    }
}


void  app_desk_ui::initScreen(lv_obj_t * cont) {
        auto chip_ptr=ChipArch_::ChipArch::getChipArchInstance();

        auto get_widget=getWidget();
        get_widget->app_name_label= lv_label_create(cont);
        lv_obj_align(get_widget->app_name_label,LV_ALIGN_LEFT_MID,5,0);
        lv_label_set_text(get_widget->app_name_label,"NULL");

        ///祖父对象
        //lv_obj_t *screenA = lv_scr_act();
        ///父对象
        auto *container=lv_obj_create(cont); //在屏幕上创建一个container

        lv_obj_set_size(container, 150, 320); //设置container的尺寸： w200, h200  （正方形）
//        lv_obj_center(container);//让container垂直水平居中（相对于父级）
        lv_obj_align(container,LV_ALIGN_RIGHT_MID,0,0);

        lv_obj_set_flex_flow(container, LV_FLEX_FLOW_COLUMN);//设置container的子级的layout: 弹性布局弹性流（flex-flow）(布局+滚动功能)
        ///对象的特性
        //1.添加事件 // Link---<!>----------------------------------->>>>>>>>>>>>
        lv_obj_add_event_cb(container, scroll_event_cb, LV_EVENT_SCROLL, (void *)this);//给container添加event，事件的回调函数、事件类型（Scroll）
        //2.设置样式
//        lv_obj_set_style_radius(container, LV_RADIUS_CIRCLE, 0); //设置矩形圆角 LV_RADIUS_CIRCLE：圆角最大化
        lv_obj_set_style_bg_opa(container,0,LV_PART_MAIN);
        lv_obj_set_style_border_opa(container,0,LV_PART_MAIN);

        lv_obj_set_style_pad_gap(container, 50, 0);

        lv_obj_set_style_clip_corner(container, true, 0); //儿子超出部分隐藏
        lv_obj_set_scroll_dir(container, LV_DIR_VER); //设置Scroll的允许方向direction：垂直方向
        lv_obj_set_scroll_snap_y(container, LV_SCROLL_SNAP_CENTER); //捕捉container Y方向的子对象，将他们与Container中心对齐 ； snap ：捕获；捕捉
        lv_obj_set_scrollbar_mode(container, LV_SCROLLBAR_MODE_OFF);//隐藏scrollbar

        ///子对象

        for(auto &item:chip_ptr->getInstalledAppList()){
            if (item->getAddr()==this->getScreenPacker()->getAppBase()->getAppPacker()){
                continue;
            }
            lv_obj_t * btn = lv_btn_create(container); //在container上创建button
            lv_obj_set_width(btn, lv_pct(100)); //设置button的width = lv_pct(100); //pct : percentage 相对于父亲的宽度100%
            btn->user_data=item;
            lv_obj_add_event_cb(btn,[](lv_event_t * event){
                auto get_btn= lv_event_get_target(event);
                auto code = lv_event_get_code(event);
                auto user_data= (app_desk_ui *)lv_event_get_user_data(event);
                uint32_t current_time = lv_tick_get(); /* 获取当前时间 */
                if(code == LV_EVENT_CLICKED) {
                    /* 检查两次点击之间的时间间隔 */
                    if (current_time - last_click_time < DOUBLE_CLICK_MAX_INTERVAL) {
                        auto chip=ChipArch_::ChipArch::getChipArchInstance();
                        chip->createAndStartApp((ChipArch_::APP_PACKER_BASE *)get_btn->user_data);
                        auto get_app_life=chip->getAppManager().getAppLifecycleList()[0];
                        user_data->getScreenPacker()->getAppBase()->closeApp();
                    }
                }
                last_click_time = current_time;
            },LV_EVENT_CLICKED, this);
            ///孙对象
            lv_obj_t * label = lv_label_create(btn); //在button上创建一个label（标签）
            lv_label_set_text_fmt(label, "%s", item->getAppName().c_str());  //动态设置label的文本内容  fmt: format（格式）

        }

        /*Update the buttons position manually for first*/ //首次手动更新按钮的位置
        lv_event_send(container, LV_EVENT_SCROLL, NULL); //TODO

        /*Be sure the fist button is in the middle*/ //确保第一个按钮处于中间
        lv_obj_scroll_to_view(lv_obj_get_child(container, 0), LV_ANIM_ON); //第一个按钮是否以滚动动画，滚动到指定位置（默认位置）


}
void  app_desk_ui::deInitScreen(lv_obj_t * cont){

}