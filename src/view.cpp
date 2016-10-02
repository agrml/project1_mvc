#include <iostream>
#include <sstream>
#include <unistd.h>

#include "view.hpp"
#include "io.hpp"

// todo: ifs in cin>>
OptionsType CliView::getOptions()
{
    OptionsType options;
    std::string opt;
    std::cout << "What would you like to do? [align|gray-world|median]" << std::endl;
    std::cin >> opt;
    options.emplace(std::make_pair("option", opt));
    if (opt == "align") {
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
    } else if (opt == "median") {
        std::cout << "Enter blur radius: " << std::endl;
        std::cin >> opt;
        options.emplace(std::make_pair("radius", opt));
    }
    return options;
}

void CliView::run()
{
    std::cout << "Align Project: Prac Edition. Mikhail Agranovskiy, 321 group" << std::endl << std::endl;
    std::cout << "Welcome to CLI. We have pleasure that you prefer us to GUI." << std::endl;
    std::cout << "We will ask you for further interactions soon." << std::endl;

    /*would you like to run system viewer to see image changes?*/
}

void CliView::output(const Image &res)
{
    auto path = this->getPath("Computation finished. Specify absolute path to place where you wold like to store the result.\n"
                                      "Or enter [no]: image will be saved in a temporary location and opened in a system viewer: ");
    if (!path.empty() && path != "no") {
        save_image(res, path.c_str());
    } else if (!fork()) {
        // fixme: ubuntu specific?
        path = "build/res.bmp";
        std::stringstream ss;
        save_image(res, path.c_str());
        ss << "xdg-open " << path;
        if (std::system(ss.str().c_str())) {};
    }
}

std::string CliView::getPath(const std::string &msg)
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




void CliImageView::run()
{
    // create the file
    this->updateImage();
    if (!fork()) {
        std::stringstream ss;
        // fixme: ubuntu specific?
        ss << "xdg-open " << path_;
        if (std::system(ss.str().c_str())) {};
    }
}

void CliImageView::updateImage()
{
    save_image(model_->getImage(), path_.c_str());
}
