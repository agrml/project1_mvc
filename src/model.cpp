#include "io.hpp"
#include "model.hpp"

// model storage. may be placed to main

Image Model::getSrc() const
{
    return src_;
}

Image Model::getRes() const
{
    return res_;
}

void Model::setSrc(const Image &img)
{
    src_ = img;
//    emit modelUpdated();
}

void Model::setRes(const Image &img)
{
    res_ = img;
//    emit modelUpdated();
}
