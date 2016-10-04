#pragma once

#include "Ui.hpp"
#include "AppModel.hpp"

class AppController
{
    std::shared_ptr<AppModel> model_;
    std::shared_ptr<Ui> ui_;
public:
    AppController(std::shared_ptr<AppModel> model,
                  std::shared_ptr<Ui> ui);
    void run();
private:
    /// the main part of working process
    void processOptions(const OptionsType &options);

};