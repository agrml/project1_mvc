#include "Ui.hpp"


void Cli::run()
{
    textView_->run();
}

void Cli::onModelUpdate()
{
    imageView_->updateImage();
    textView_->log("Image updated");
}

void Cli::runImageView(const std::string &path)
{
    imageView_->run(appModel_, path);
}

Cli::Cli(std::shared_ptr<ImageView> imageView,
         std::shared_ptr<TextView> textView,
         std::shared_ptr<AppModel> appModel) : imageView_(imageView),
                                               textView_(textView),
                                               appModel_(appModel) {}