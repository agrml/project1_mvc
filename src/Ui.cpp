#include "Ui.hpp"

Cli::Cli(ImageView *imageView,
       TextView *textView,
       AppModel *model) :  imageView_(*imageView),
                        textView_(*textView),
                        model_(*model) {}

void Cli::run()
{
    textView_.run();
}

void Cli::onModelUpdate()
{
    imageView_.updateImage();
    textView_.log("Image updated");
}

void Cli::runImageView(const std::string &path)
{
    imageView_.run(&model_, path);
}
