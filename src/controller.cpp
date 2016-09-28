#include "controller.hpp"


void Controller::run(View &view, Model &model)
{
    try {
        auto options = view.getOptions();
        // cout << "What wold you like to do? Enter option (or `help` for help)";
        options = evalOptions(options);
        model.run(option);
    } catch (inputError) {

    }
}

OptionsType Controller::evalOptions(OptionsType &options)
{
    Model{options["path"][0]};
    if (options["option"][0] == "align") {
    }
}
