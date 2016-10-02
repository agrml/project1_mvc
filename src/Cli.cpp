#include "Cli.hpp"

Cli::Cli(ImageView *imageView,
       TextView *textView,
       Model *model) :  imageView_(*imageView),
                        textView_(*textView),
                        model_(*model) {}

void Cli::run()
{
    textView_.run();
    const std::string &DestImgPath = textView_.getString("Specify absolute path to place where you wold like to store the result: ");
    imageView_.run(&model_, DestImgPath);
}
