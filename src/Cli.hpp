#pragma once

#include "view.hpp"

/// The app view (AppView) -- the `view` controlled by the `controller` (AppController class)
/// and represents the `model` -- the state of the app (no the state of the image. it is meaningfull to note that.)
class Cli /*inherit? view? observer?*/
{
    ImageView &imageView_;
    TextView &textView_;
    Model &model_;
public:
    /// calls subviews' `run`s and more
    Cli(ImageView *, TextView *, Model *);

    // note: high-weight method
    void run();
    // own methods
    // now just translators but will be own ones
    void updateImage();
    std::string getPath(const std::string &msg);
    OptionsType getOptions();
    // own ones
};





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
