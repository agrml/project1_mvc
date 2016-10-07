#include <sstream>

#include "AppController.hpp"
#include "align.hpp"


void AppController::run()
{
    try {
        QObject::connect(model_.get(), SIGNAL(log(const std::string &)),
                         ui_.get(), SLOT(log(const std::string &)));
        ui_->run();
        auto srcPath = ui_->getLine("Specify absolute path to the source image: ");
        model_->setImg(load_image(srcPath.c_str()));
        QObject::connect(model_.get(), SIGNAL(modelUpdated()),
                         ui_.get(), SLOT(onModelUpdate()));
        auto dstPath = ui_->getLine("Specify absolute path to place where you wold like to store the result: ");
        ui_->runImageView(dstPath);

        auto options = ui_->getOptions();


        processOptions(options);
        ui_->log("All tasks are finished.");
    } catch (const std::string &s) {
        ui_->log(s);
    }
}

void AppController::processOptions(const OptionsType &options)
{
    auto param2 = options.at("isPostprocessing") == "true";
    std::string param3;
    if (param2) {
        param3 = options.at("postprocessingType");
    }
    bool param4 = false;
    if (options.find("isMirror") != options.end()) {
        param4 = options.at("isMirror") == "true";
    }
    model_->align(param2,
                  param3,
                  param4);
}

AppController::AppController(std::shared_ptr<AppModel> model,
                             std::shared_ptr<Ui> ui) : model_(model),
                                                       ui_(ui) {}


