#pragma once

#include "io.hpp"

class AppModel
{
    std::shared_ptr<Image> img_;
public:
    AppModel();
    Image getImg() const;
    void setImg(const Image &img);
//signals:
//    void modelUpdated();
    ~AppModel() {}
};
