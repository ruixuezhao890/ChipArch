#include "Sliding_test.h"
#include "ChipArch/App&UI/AppInstall/AppInstall.hpp"
#include "ChipArch/EmbHardware/Solitude/Solitude.h"
void setp(){
    LV_LOG("Start Up");
    HAL::Inject(new Solitude());

   auto chipArchObtain= ChipArch::chipArchObtain();
   chipArchObtain->init();
   auto desk_package=new app_desk_pakger;
   chipArchObtain->installApp(desk_package);
   chip_arch_install_callback(chipArchObtain);
   chipArchObtain->creatStartApp(desk_package);

}

[[noreturn]]
void loop(){
    auto chipArchObtain= ChipArch::chipArchObtain();
    while (true){
        chipArchObtain->update();
        lv_timer_handler();
        usleep(5 * 1000);
    }
}