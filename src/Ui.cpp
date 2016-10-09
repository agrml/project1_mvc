#include "Ui.hpp"


void Cli::run(std::shared_ptr<AppModel> appModel)
{
    appModel_ = appModel;
    textView_->run(appModel_);
}

void Cli::onModelUpdate()
{
    imageView_->updateImage();
    textView_->log("Image is updated");
}

void Cli::runImageView()
{
    imageView_->run(appModel_);
}

Cli::Cli(std::shared_ptr<CliImageView> imageView,
         std::shared_ptr<CliTextView> textView) : imageView_(imageView),
                                               textView_(textView) {}

void Cli::log(const std::string &msg)
{
    textView_->log(msg);
}

std::string Cli::getLine(const std::string &msg)
{
    return textView_->getLine(msg);
}

OptionsType Cli::getOptions()
{
    return textView_->getOptions();
}