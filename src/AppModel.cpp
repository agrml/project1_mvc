#include <glog/logging.h>
#include "io.hpp"
#include "AppModel.hpp"

// model storage. may be placed to main

Image AppModel::getImg() const
{
    return *img_;
}

void AppModel::setImg(const Image &img)
{
    *img_ = img;
    // todo: emit modelUpdated

}

AppModel::AppModel() : img_(std::make_shared<Image>()) {}