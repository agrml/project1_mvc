#pragma once

#include "Ui.hpp"
#include "AppModel.hpp"

class AppController
{
    AppModel &model_;
    Ui &ui_;
public:
    AppController(AppModel *model, Ui *ui);
    void run();
private:
    /// the main part of working process
    void processOptions(const OptionsType &options);

};