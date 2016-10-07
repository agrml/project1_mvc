#include "align.hpp"
#include <string>
#include <assert.h>

#include "MatrixMath.hpp"


Image unsharp(Image src_image)
{
    double one = 1;
    Matrix<double> kernel{{-one / 6, -2 * one / 3, -one / 6},
                          {-2 * one / 3, 13 * one / 3, -2 * one / 3},
                          {-one / 6, -2 * one / 3, -one / 6}};
    return custom(src_image, kernel);
}

Image gray_world(Image src_image)
{
    using BrightnessType = double;

    struct Brightness
    {
        BrightnessType r=0, g=0, b=0;
    };

    Brightness br{};

    // calculate coefficients
    // fixme: возможго слишком мощное округление при делении
    auto sz = src_image.n_cols * src_image.n_rows;
    for (size_t i = 0; i < src_image.n_rows; i++) {
        for (size_t j = 0; j < src_image.n_cols; j++) {
            Brightness tmp;
            std::tie(tmp.r, tmp.g, tmp.b) = src_image(i, j);
            br.r += tmp.r / sz;
            br.g += tmp.g / sz;
            br.b += tmp.b / sz;
        }
    }
    BrightnessType mean = (br.r + br.g + br.b) / 3;
    // FIXME: possible zero division error
    br.r = mean / br.r;
    br.g = mean / br.g;
    br.b = mean / br.b;

    // get images
    auto r = custom(src_image, Matrix<double>{br.r});
    auto g = custom(src_image, Matrix<double>{br.g});
    auto b = custom(src_image, Matrix<double>{br.b});

    // transform to 1 image
    for (size_t i = 0; i < src_image.n_rows; i++) {
        for (size_t j = 0; j < src_image.n_cols; j++) {
            r(i, j) = std::make_tuple(std::get<0>(r(i, j)),
                                      std::get<1>(g(i, j)),
                                      std::get<2>(b(i, j)));
        }
    }
    return r;
}

Image custom(Image src_image, Matrix<double> kernel)
{
    assert(kernel.n_rows == kernel.n_cols);
    return src_image.unary_map(ConvolutionOp{kernel});
}


Image median(Image src_image, int radius)
{
    return src_image.unary_map(MedianOp{uint(radius)});
}
