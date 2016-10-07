#include <iostream>
#include <sstream>
#include <unistd.h>
#include <glog/logging.h>

#include "SubViews.hpp"

OptionsType CliTextView::getOptions() const
{
    OptionsType options;
    std::string opt;
    std::cout << "Postprocessing? [gray-world|unsharp|no -- to finish]";
    if ((std::cin >> opt) && opt[0] != 'n') {
        options.emplace(std::make_pair("isPostprocessing", "true"));
        options.emplace(std::make_pair("postprocessingType", opt));
    } else {
        options.emplace(std::make_pair("isPostprocessing", "false"));
    }
    if (opt == "unsharp") {
        std::cout << "Would you like to extend image by mirroring before postprocessing? [yes|no]" << std::endl;
        if ((std::cin >> opt) && opt == "yes") {
            options.emplace(std::make_pair("isMirror", "true"));
        } else {
            options.emplace(std::make_pair("isMirror", "false"));
        }
    }
    return options;
}

void CliTextView::run()
{
    std::cout << "Align Project: Prac Edition. Mikhail Agranovskiy, 321 group" << std::endl << std::endl;
    std::cout << "Welcome to CLI. We have pleasure that you prefer us to GUI." << std::endl;
    std::cout << "We will ask you for further interactions soon..." << std::endl;
}

std::string CliTextView::getLine(const std::string &msg) const
{
    if (!msg.empty()) {
        std::cout << msg << std::endl;
    }
    std::string s;
    while (std::isspace(std::cin.get())) {}
    std::cin.unget();
    std::getline(std::cin, s, '\n');
    return s;
}

void CliTextView::write(const std::string &msg) const
{
    std::cout << msg << std::endl;
    // todo: std::flush
}

void CliTextView::log(const std::string &msg) const
{
    LOG(INFO) << msg;
}

void CliImageView::run(std::shared_ptr<AppModel> model,
                       const std::string &path)
{
    model_ = model;
    save_path_ = path;
    // create the file
    this->updateImage();
    /*todo: would you like to run system viewer to see image changes?*/
    if (!fork()) {
        std::stringstream ss;
        // fixme: ubuntu specific?
        ss << "xdg-open " << save_path_;
        if (std::system(ss.str().c_str())) {};
    }
}

void CliImageView::updateImage() const
{
    save_image(model_->getImg(), save_path_.c_str());
}
