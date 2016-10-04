#pragma once

#include "SubViews.hpp"

/// The app view (AppView) -- the `view` controlled by the `controller` (AppController class)
/// and represents the `model` -- the state of the app (no the state of the image. it is meaningfull to note that.)

class Cli /*inherit? view? observer?*/
{
    std::shared_ptr<ImageView> imageView_;
    std::shared_ptr<TextView> textView_;
    std::shared_ptr<AppModel> appModel_;
public:
    /// calls subviews' `run`s and more
    Cli(std::shared_ptr<ImageView> imageView,
        std::shared_ptr<TextView> textView,
        std::shared_ptr<AppModel> appModel);

    void run();
    void runImageView(const std::string &path);
    // using image view
// todo: slot
    void onModelUpdate();

    // using text view
    void write(const std::string &msg) { textView_->write(msg); }
    void log(const std::string &msg) { textView_->log(msg); }
    std::string getLine(const std::string &msg) { return textView_->getLine(msg); }
    OptionsType getOptions() { return textView_->getOptions(); }


};

using Ui = Cli;




// todo:
//class Cli : public Ui
//{
//public:
//    Ui(ImageView *, TextView *);
//
//};
//
//
//class Gui : public Ui
//{
//
//};
