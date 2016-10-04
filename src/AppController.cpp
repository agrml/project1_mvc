#include <sstream>

#include "AppController.hpp"
#include "align.hpp"


void AppController::run()
{
    try {
        ui_->run();
        auto path = ui_->getLine("Specify absolute path to the source image: ");
        model_->setImg(load_image(path.c_str()));

        auto options = ui_->getOptions();
        const std::string &DestImgPath = ui_->getLine("Specify absolute path to place where you wold like to store the result: ");
        ui_->runImageView(DestImgPath);

        processOptions(options);
        ui_->log("All tasks are finished. Goodbye!");
    } catch (const std::string &s) {
        ui_->log(s);
    }
}

void AppController::processOptions(const OptionsType &options)
{
    if (options.at("option") == "align") {
        auto param2 = options.at("isPostprocessing") == "true";
        std::string param3;
        if (param2) {
            param3 = options.at("postprocessingType");
        }
        bool param4 = false;
        if (options.find("isMirror") != options.end()) {
            param4 = options.at("isMirror") == "true";
        }
        model_->setImg(align(model_->getImg(),
                             param2,
                             param3,
                             param4));
    } else if (options.at("option") == "gray-world") {
        model_->setImg(gray_world(model_->getImg()));
    } else if (options.at("option") == "median") {
        // todo: test
        std::stringstream ss{options.at("radius")};
        int radius;
        ss >> radius;
        model_->setImg(median(model_->getImg(), radius));
    } else {
        throw std::string{"AppController::processOptions: Unknown option."};
    }
}

AppController::AppController(std::shared_ptr<AppModel> model,
                             std::shared_ptr<Ui> ui) : model_(model),
                                                       ui_(ui) {}


