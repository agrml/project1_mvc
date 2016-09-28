#pragma once

#include "view.hpp"
#include "model.hpp"

class Controller
{
    Model model_;
    View view_;
public:
    Controller(Model &model, View &view) :
    void run();
    OptionsType evalOptions(OptionsType &options);
};