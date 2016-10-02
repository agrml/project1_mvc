#include <sstream>

#include "controller.hpp"
#include "align.hpp"


void AppController::run()
{
    try {
        auto path = view_.getPath("Specify absolute path to source image: ");
        model_.setSrc(load_image(path.c_str()));
        auto options = view_.getOptions();
        processOptions(options);
//        auto howToShow = view_.howToShowResult();
        view_.output(model_.getRes());
    } catch (std::string) {
        // todo: LOG
    }
}

void AppController::processOptions(OptionsType &options)
{
    if (options["option"] == "align") {
        model_.setRes(align(model_.getSrc(),
                            options["isPostprocessing"] == "true",
                            options["postprocessingType"],
                            options["isMirror"] == "true"));
    } else if (options["option"] == "gray-world") {
        model_.setRes(gray_world(model_.getSrc()));
    } else if (options["option"] == "median") {
        // todo: test
        std::stringstream ss{options["radius"]};
        int radius;
        ss >> radius;
        model_.setRes(median(model_.getSrc(), radius));
    } else {
        throw std::string{"AppController::processOptions: Unknown option."};
    }
}

AppController::AppController(Model *model, View *view) : model_(*model), view_(*view) {}

