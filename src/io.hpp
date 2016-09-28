#pragma once

#include "matrix.hpp"
#include "EasyBMP.h"

#include <tuple>

typedef Matrix<std::tuple<uint, uint, uint>> Image;

Image load_image(const char*);
void save_image(const Image&, const char*);

inline bool is(const std::string &lhs,
               const std::string &rhs)
{
    return lhs == rhs;
}