/** \file switch.h
 *  \brief Header file for C++ wrapper for lv_switch_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once

#include "../../core/object.h"

#if LV_USE_SWITCH != 0

namespace lvgl::widgets {

    using namespace lvgl::core;

    /** \typedef Switch
     *  \brief Wraps a lv_switch_t object.
     */
//    using Switch = Widget<lv_switch_create>;
    class Switch:public Widget<lv_switch_create>{
    public:
        using Widget::Widget;
//        Switch();
//        Switch(Object & parent);
//        void initialize();
//        void initialize(Object & parent);
    };

}
#endif // LV_USE_SWITCH
