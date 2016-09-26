#pragma once

#include "io.hpp"
#include "matrix.hpp"

// implemented
Image align(Image srcImage,
            bool isPostprocessing,  // implemented
            std::string postprocessingType,  // implemented
            double fraction,
            bool isMirror,  // implemented
            bool isInterp,
            bool isSubpixel,
            double subScale);

Image sobel_x(Image src_image);

Image sobel_y(Image src_image);

// implemented
Image unsharp(Image src_image);

// implemented
Image gray_world(Image src_image);

Image resize(Image src_image, double scale);

// Function custom is useful for making concrete linear filtrations
// like gaussian or sobel. So, we assume that you implement custom
// and then implement other filtrations using this function.
// sobel_x and sobel_y are given as an example.

// implemented
// semantic name: convolution filter
Image custom(Image src_image, Matrix<double> kernel);

Image autocontrast(Image src_image, double fraction);

Image gaussian(Image src_image, double sigma, int radius);

Image gaussian_separable(Image src_image, double sigma, int radius);

Image median(Image src_image, int radius);

Image median_linear(Image src_image, int radius);

Image median_const(Image src_image, int radius);

Image canny(Image src_image, int threshold1, int threshold2);