#pragma once

#include "io.hpp"

class Model
{
    Image src_;
    Image res_;
public:
//    Model() : src_(Image{}), res_(Image{}) {}
    Image getSrc() const;
    Image getRes() const;
    void setSrc(const Image &img);
    void setRes(const Image &img);
//signals:
//    void ModelUpdated();
};
