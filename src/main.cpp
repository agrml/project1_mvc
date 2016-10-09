// parts of standard library
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <initializer_list>
#include <limits>
#include <ctime>

// parts of third-party libraries
#include <glog/logging.h>
#include <QtCore>

// our modules
#include "AppModel.hpp"
#include "SubViews.hpp"
#include "AppController.hpp"
#include "Ui.hpp"

/// init third-party libraries
void init(int argc, char *argv[])
{
    google::InitGoogleLogging(argv[0]);
    google::InstallFailureSignalHandler();
}

int main(int argc, char *argv[])
{
    init(argc, argv);

    // parse argv
    constexpr int MODE_ARGC = 1;
    if (argc != MODE_ARGC + 1) {
        throw std::string{"Expect 1 command line argument, "} + std::to_string(argc - 1) + "given.";
    }
    std::string param{argv[MODE_ARGC]};

    // init view
    std::shared_ptr<Ui> ui;
    auto model = std::make_shared<AppModel>();
    if (param == "--gui") {
//        auto imageView = std::make_shared<GuiImageView>();
//        auto textView = std::make_shared<GuiTextView>();
//        ui = std::make_shared<Gui>(imageView, textView);
        throw "Graphic interface is not fully implemented. Try CLI (--cli).";
    } else if (param == "--cli") {
        auto imageView = std::make_shared<CliImageView>();
        auto textView = std::make_shared<CliTextView>();
        ui = std::make_shared<Cli>(imageView, textView);
    } else {
        throw std::string{"unknown mode"};
    }
    auto controller = std::make_shared<AppController>(model, ui);
    controller->run();

    return 0;
}