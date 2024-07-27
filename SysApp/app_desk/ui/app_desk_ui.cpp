#include "app_desk_ui.h"
#include "ChipArch/ChipArchChild/ChipArch.h"
#include "ChipArch/SysApp/app_desk/assets/icon_app_default.hpp"

app_desk_ui::app_desk_ui(const String &band_app_) : Page(band_app_) {

}
void app_desk_ui::init() {

    initializeDeskUI();

}

void app_desk_ui::exit() {
    deleteResources();
}



void app_desk_ui::initializeDeskUI() {

    draw_desk_attribute.ui_Screen1_=this->now_page_;
    lv_obj_clear_flag(draw_desk_attribute.ui_Screen1_, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
    lv_obj_set_style_bg_color(draw_desk_attribute.ui_Screen1_, lv_color_hex(0x3C3C3C), LV_PART_MAIN | LV_STATE_DEFAULT );
    lv_obj_set_style_bg_opa(draw_desk_attribute.ui_Screen1_, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(draw_desk_attribute. ui_Screen1_, &ui_img_launchbackground1_png, LV_PART_MAIN | LV_STATE_DEFAULT );

    draw_desk_attribute.ui_Panel1_ = lv_obj_create(draw_desk_attribute.ui_Screen1_);
    lv_obj_set_width(draw_desk_attribute.ui_Panel1_, 318);
    lv_obj_set_height(draw_desk_attribute.ui_Panel1_, 30);
    lv_obj_set_x(draw_desk_attribute.ui_Panel1_, 0 );
    lv_obj_set_y(draw_desk_attribute.ui_Panel1_, -109 );
    lv_obj_set_align(draw_desk_attribute.ui_Panel1_, LV_ALIGN_CENTER );
    lv_obj_clear_flag(draw_desk_attribute.ui_Panel1_, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE );    /// Flags

    draw_desk_attribute.ui_Label2_ = lv_label_create(draw_desk_attribute.ui_Screen1_);
    lv_obj_set_width(draw_desk_attribute.ui_Label2_, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(draw_desk_attribute.ui_Label2_, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x(draw_desk_attribute.ui_Label2_, 0 );
    lv_obj_set_y(draw_desk_attribute.ui_Label2_, 60 );
    lv_obj_set_align(draw_desk_attribute.ui_Label2_, LV_ALIGN_CENTER );
    lv_label_set_text(draw_desk_attribute.ui_Label2_, "NULL");

    draw_desk_attribute.ui_Label1_ = lv_label_create(draw_desk_attribute.ui_Panel1_);
    lv_obj_set_width(draw_desk_attribute.ui_Label1_, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(draw_desk_attribute.ui_Label1_, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_align(draw_desk_attribute.ui_Label1_, LV_ALIGN_CENTER );
    lv_label_set_text(draw_desk_attribute.ui_Label1_, "0:14");

    draw_desk_attribute.ui_WIFI_ = lv_img_create(draw_desk_attribute.ui_Panel1_);
    lv_img_set_src(draw_desk_attribute.ui_WIFI_, &ui_img_wifi_png);
    lv_obj_set_width(draw_desk_attribute.ui_WIFI_, 20);
    lv_obj_set_height(draw_desk_attribute. ui_WIFI_, 20);
    lv_obj_set_x(draw_desk_attribute.ui_WIFI_, -3 );
    lv_obj_set_y(draw_desk_attribute.ui_WIFI_, -6 );
    lv_obj_add_flag(draw_desk_attribute.ui_WIFI_, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
    lv_obj_clear_flag(draw_desk_attribute.ui_WIFI_, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

    draw_desk_attribute.ui_BLE_ = lv_img_create(draw_desk_attribute.ui_Panel1_);
    lv_img_set_src(draw_desk_attribute.ui_BLE_, &ui_img_ble_png);
    lv_obj_set_width(draw_desk_attribute.ui_BLE_, 20);
    lv_obj_set_height(draw_desk_attribute. ui_BLE_, 20);
    lv_obj_set_x(draw_desk_attribute.ui_BLE_, 3 );
    lv_obj_set_y(draw_desk_attribute.ui_BLE_, -6 );
    lv_obj_set_align(draw_desk_attribute. ui_BLE_, LV_ALIGN_TOP_RIGHT );
    lv_obj_add_flag(draw_desk_attribute.ui_BLE_, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
    lv_obj_clear_flag(draw_desk_attribute. ui_BLE_, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, draw_desk_attribute.ui_Panel1_);
    lv_anim_set_user_data(&a,this);
    lv_anim_set_exec_cb(&a, [](void * obj, int32_t v) {
        lv_obj_set_y(static_cast<lv_obj_t *>(obj), v);
    });

    lv_anim_set_path_cb(&a, lv_anim_path_bounce);
    lv_anim_set_values(&a, -135, -109);
//    lv_anim_set_time(&a, draw_desk_attribute.AnimTime/2);
//    lv_anim_set_delay(&a, draw_desk_attribute.DelayAnimTime+200);
//    auto read_callback=[](struct _lv_anim_t * a){
//      auto get_user_data=static_cast<app_desk_ui *>(lv_anim_get_user_data(a));
//      get_user_data->setPlankAnim();
//    };
//    lv_anim_set_ready_cb(&a,read_callback);
    lv_anim_start(&a);
}

void app_desk_ui::drawDeskIcon() {


     draw_desk_attribute.plank_= lv_obj_create(now_page_);

    draw_desk_attribute.map_=&ChipArch::getOrCreateChipArch()->getInstalledAppList();

    lv_obj_set_size(draw_desk_attribute.plank_, 320, 150); //设置cont的尺寸： w200, h200  （正方形）
    lv_obj_align(draw_desk_attribute.plank_, LV_ALIGN_CENTER, 0, -20);//让cont垂直水平居中（相对于父级）
    lv_obj_set_flex_flow(draw_desk_attribute.plank_, LV_FLEX_FLOW_ROW);//设置cont的子级的layout: 弹性布局弹性流（flex-flow）(布局+滚动功能)
    lv_obj_set_style_pad_gap(draw_desk_attribute.plank_, 50, 0);

    lv_obj_add_event_cb(draw_desk_attribute.plank_, upDataScrollIcon, LV_EVENT_SCROLL, NULL);//给cont添加event，事件的回调函数、事件类型（Scroll）

    lv_obj_set_style_bg_opa(draw_desk_attribute.plank_, 0, 0);
    lv_obj_set_style_border_opa(draw_desk_attribute.plank_, 0, 0);

    lv_obj_set_style_clip_corner(draw_desk_attribute.plank_, true, 0); //儿子超出部分隐藏
    lv_obj_set_scroll_dir(draw_desk_attribute.plank_, LV_DIR_HOR); //设置Scroll的允许方向direction：垂直方向
    lv_obj_set_scroll_snap_x(draw_desk_attribute.plank_, LV_SCROLL_SNAP_CENTER); //捕捉draw_desk_attribute.plank_ Y方向的子对象，将他们与Container中心对齐 ； snap ：捕获；捕捉
    lv_obj_set_scrollbar_mode(draw_desk_attribute.plank_, LV_SCROLLBAR_MODE_OFF);//隐藏scrollbar

    if (draw_desk_attribute.map_->size()>1) {
        for (auto &item: *draw_desk_attribute.map_) {
            if (!item.second || String(item.second->getAppName()) == home_page_name
            ||!item.second->getAllowDisplayIcon()) {
                continue;
            }
            draw_desk_attribute.app_name_Vec_.push_back(item.first);
            auto image_button = lv_imgbtn_create(draw_desk_attribute.plank_);
            lv_obj_set_size(image_button, icon_size, icon_size);
            lv_obj_add_flag(image_button, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_set_user_data(image_button, (void *) item.first.c_str());
            lv_obj_add_event_cb(image_button, openDeskIcon, LV_EVENT_CLICKED, nullptr);
            loadImage(item.first.c_str(), image_button);
            draw_desk_attribute.buttonVec_.push_back(image_button);
        }
        draw_desk_attribute.initial_loading_flag_ = false;
        auto get = draw_desk_attribute.app_name_Vec_[draw_desk_attribute.control_now_app_index];


        lv_label_set_text(draw_desk_attribute.ui_Label2_, get.c_str());

        lv_event_send(draw_desk_attribute.plank_, LV_EVENT_SCROLL, nullptr);
        lv_obj_scroll_to_view(lv_obj_get_child(draw_desk_attribute.plank_, draw_desk_attribute.control_now_app_index),
                              LV_ANIM_ON);
//        lv_obj_add_flag(draw_desk_attribute.plank_, LV_OBJ_FLAG_HIDDEN);
//            setPlankAnim();
    }

}

void app_desk_ui::upDataScrollIcon(lv_event_t * e) {
    lv_obj_t * obj = lv_event_get_target(e);

    lv_area_t obj_a;
    lv_obj_get_coords(obj, &obj_a);
    int32_t obj_center_x = obj_a.x1 + lv_area_get_width(&obj_a) / 2;
    int32_t r = lv_obj_get_width(obj) * 7 / 10;
    uint32_t child_cnt = lv_obj_get_child_cnt(obj);

    for (uint32_t i = 0; i < child_cnt; i++) {
        lv_obj_t * child = lv_obj_get_child(obj, i);
        lv_area_t child_a;
        lv_obj_get_coords(child, &child_a);
        int32_t child_x_center = child_a.x1 + lv_area_get_width(&child_a) / 2;
        int32_t diff_x = LV_ABS(child_x_center - obj_center_x);

        int32_t y;
        if (diff_x >= r) {
            y = r;
        } else {
            uint32_t y_sqr = r * r - diff_x * diff_x; // 计算垂直偏移量的平方
            lv_sqrt_res_t res;
            lv_sqrt(y_sqr, &res, 0x8000); // 计算垂直偏移量
            y = r - res.i;
        }

        lv_obj_set_style_translate_y(child, y, 0);
        lv_opa_t opa = lv_map(y, 0, r, LV_OPA_TRANSP, LV_OPA_COVER);
        lv_obj_set_style_opa(child, LV_OPA_COVER - opa, 0);
    }
}


void app_desk_ui::openDeskIcon(lv_event_t * e) {
    if (lv_event_get_code(e) == LV_EVENT_CLICKED) {
        lv_obj_t * btn = lv_event_get_target(e);
        const char * user_data = static_cast<const char *>(lv_obj_get_user_data(btn));

        LV_LOG_USER("Click %d\n", lv_event_get_code(e));
        LV_LOG_USER("user_data %s\n", user_data);

        ChipArch * chip_arch = ChipArch::getOrCreateChipArch();
//        auto get_app_pack = chip_arch->getInstalledAppList();
        chip_arch->startApp(user_data);
        chip_arch->closeApp(home_page_name.c_str());
    }
}

void app_desk_ui::loadImage(const String &app_name, lv_obj_t *button, uint8_t defaultWidth, uint8_t defaultHeight) {
    if (draw_desk_attribute.initial_loading_flag_){
        auto image_load=new ImageDescriptor();
        auto icon=draw_desk_attribute.map_->find(app_name)->second->getAppIcon();
        if (icon) {
            image_load->set_src((uint8_t *)icon, defaultWidth, defaultHeight, LV_IMG_CF_TRUE_COLOR_ALPHA);
        } else {
            image_load->set_src(image_data_icon_app_default, defaultWidth, defaultHeight, LV_IMG_CF_TRUE_COLOR_ALPHA);
        }
        draw_desk_attribute.load_picture_[app_name]=image_load;
        lv_obj_set_style_bg_img_src(button,image_load->raw_ptr(),LV_IMGBTN_STATE_RELEASED);
    }
    else{
        auto iterator=draw_desk_attribute.load_picture_.find(app_name);
        lv_obj_set_style_bg_img_src(button,iterator->second->raw_ptr(),LV_IMGBTN_STATE_RELEASED);
    }

}

void app_desk_ui::setPlankAnim() const {
//    lv_obj_clear_flag(draw_desk_attribute.plank_,LV_OBJ_FLAG_HIDDEN);

    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, draw_desk_attribute.plank_);
    lv_anim_set_exec_cb(&a, [](void * obj, int32_t v) {
        lv_obj_set_y(static_cast<lv_obj_t *>(obj), v);
//        lv_obj_set_style_bg_opa(static_cast<lv_obj_t *>(obj),v,0);
    });

    lv_anim_set_path_cb(&a, lv_anim_path_linear);
    lv_anim_set_values(&a,  320,0);
    lv_anim_set_time(&a, draw_desk_attribute.AnimTime);
    lv_anim_set_delay(&a, draw_desk_attribute.DelayAnimTime);
    lv_anim_start(&a);
}


void app_desk_ui::scrollLeft() {
    if (draw_desk_attribute.control_now_app_index < draw_desk_attribute.app_name_Vec_.size() - 1) {
        draw_desk_attribute.control_now_app_index++;
    }
    lv_label_set_text(draw_desk_attribute.ui_Label2_, draw_desk_attribute.app_name_Vec_[draw_desk_attribute.control_now_app_index].c_str());

    lv_obj_t * btn = draw_desk_attribute.buttonVec_[draw_desk_attribute.control_now_app_index];
    lv_obj_scroll_to_view(btn, LV_ANIM_ON);
    lv_event_send(draw_desk_attribute.plank_, LV_EVENT_SCROLL, NULL);
}

void app_desk_ui::scrollRight() {
    if (draw_desk_attribute.control_now_app_index > 0) {
        draw_desk_attribute.control_now_app_index--;
    }
    lv_label_set_text(draw_desk_attribute.ui_Label2_, draw_desk_attribute.app_name_Vec_[draw_desk_attribute.control_now_app_index].c_str());

    lv_obj_t * btn = draw_desk_attribute.buttonVec_[draw_desk_attribute.control_now_app_index];
    lv_obj_scroll_to_view(btn, LV_ANIM_ON);
    lv_event_send(draw_desk_attribute.plank_, LV_EVENT_SCROLL, NULL);
}

void app_desk_ui::scrollOpen() {
    lv_obj_t * btn = draw_desk_attribute.buttonVec_[draw_desk_attribute.control_now_app_index];
    lv_event_send(btn, LV_EVENT_CLICKED, NULL);
}

app_desk_ui::~app_desk_ui() {

}

void app_desk_ui::deleteResources() {
    draw_desk_attribute.app_name_Vec_.clear();
    for(auto &item:draw_desk_attribute.buttonVec_){
        item= nullptr;
    }
    draw_desk_attribute.buttonVec_.clear();
    draw_desk_attribute.map_= nullptr;
}







