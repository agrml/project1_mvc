#pragma once

#include "io.hpp"
#include "matrix.hpp"

Image align(Image srcImage,
            bool isPostprocessing,
            std::string postprocessingType,
            bool isInterp,
            bool isMirror);

Image unsharp(Image src_image);

Image gray_world(Image src_image);

// Function custom is useful for making concrete linear filtrations
// like gaussian or sobel. So, we assume that you implement custom
// and then implement other filtrations using this function.
// sobel_x and sobel_y are given as an example.

// implemented
// semantic name: convolution filter
Image custom(Image src_image, Matrix<double> kernel);

Image median(Image src_image, int radius);