#pragma once

#include "io.hpp"

class Model
{
    Image img_;
public:
    Model(const std::string &path);
    Image getImage();
    void setImage(const Image &img);
signals:
    void ModelUpdated();
};
