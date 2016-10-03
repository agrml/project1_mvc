#pragma once

#include "io.hpp"

class AppModel
{
    Image *img_;
public:
    AppModel();
    Image getImg() const;
    void setImg(const Image &img);
//signals:
//    void modelUpdated();
    ~AppModel() { delete img_; }
};
