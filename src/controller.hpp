#pragma once

#include "view.hpp"
#include "model.hpp"

class AppController
{
    Model &model_;
    View &view_;
public:
    AppController(Model *model, View *view);
    void run();
    void processOptions(OptionsType &options);

};