/**
 * @file boot_anim_ascii.h
 * @author ruixuezao890
 * @brief 
 * @version 0.1
 * @date 2023-08-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "ChipArch/ChipArch.h"
#include "PubInculde.hpp"
#include <cstdio>
#include <iostream>
#include <string>


namespace ChipArch_
{
    namespace APPS
    {
        class BootAnim_ASCII : public APP_BASE
        {
            private:
                static const std::string _chipArch_ascii_logo;

            public:
                static const std::string& getMooncakeASCIILogo() { return _chipArch_ascii_logo; }
                static void printInfos()
                {
                    /* Print logo */
                    fmt::info("{}",BootAnim_ASCII::getMooncakeASCIILogo());
                    fmt::info("\n"
                            "┌{0:─^{2}}┐\n"
                            "│{1: ^{2}}│\n"
                            "└{0:─^{2}}┘\n", "", "Hello, ChipArch!", 30);

                    fmt::newline_info("\n- @author ruixuezao890");
                    fmt::newline_info("- @version {:.1f}",VERSION);
                    fmt::newline_info("- @build at {} {}",__TIME__,__DATE__);
//                      std::cout << "\n- @author ruixuezao890\n";
//                    std::cout << "- @version " << VERSION << "\n";//todo 添加版本号
//                    std::cout << "- @build at " << __TIME__ << " " << __DATE__ << "\n\n";
                }

                void onCreate() override
                {
                    /* Print Info */
                    BootAnim_ASCII::printInfos();

                }
            
            void onResume() override;
            
            void onRunning() override;

            void onPause() override;


        };

        class BootAnim_ASCII_Packer : public APP_PACKER_BASE
        {
            std::string getAppName() override { return "BootAnim_ASCII"; }
            void* newApp() override { return new BootAnim_ASCII; }
            void deleteApp(void *app) override { delete (BootAnim_ASCII*)app; }

        public:
            void *newScreenPacker() override;
        };
    }
}
