#include "align.h"
#include <string>
#include <assert.h>


using std::string;
using std::cout;
using std::endl;


Image align(Image srcImage,
            bool isPostprocessing,
            std::string postprocessingType,
            double fraction,
            bool isMirror,
            bool isInterp,
            bool isSubpixel,
            double subScale)
{
    constexpr ssize_t shiftLen = 15;
    struct Img
    {
        Image r{}, g{}, b{};
    };

    struct ShiftStorage
    {
        MetricType metric;
        ssize_t horShift;
        ssize_t vertShift;
    };

    Img img;
    img.b = srcImage.submatrix(0, 0, srcImage.n_rows / 3, srcImage.n_cols);
    img.g = srcImage.submatrix(srcImage.n_rows / 3, 0, srcImage.n_rows / 3, srcImage.n_cols);
    img.r = srcImage.submatrix(srcImage.n_rows / 3 * 2, 0, srcImage.n_rows / 3, srcImage.n_cols);

    auto calcSubmatrixes = [] (const Image &fixed,
                               const Image &movable,
                               ssize_t vertShift,
                               ssize_t horShift) -> std::tuple<Image, Image> {
        auto fixedSub = fixed.submatrix(vertShift,
                                        horShift,
                                        vertShift + fixed.n_rows,
                                        horShift + fixed.n_cols);
        auto movableSub = movable.submatrix(-vertShift,
                                            -horShift,
                                            -vertShift + movable.n_rows,
                                            -horShift + movable.n_cols);
        assert(fixedSub.n_rows == movableSub.n_rows);
        assert(fixedSub.n_rows == movableSub.n_cols);
        return {fixedSub, movableSub};
    };

    auto calcAlignmentForPair = [] (const Image &fixed, const Image &movable) {
        ShiftStorage shiftStor{std::numeric_limits<MetricType>::max(), 0, 0};
        for (ssize_t horShift = -shiftLen; horShift <= shiftLen; horShift++) {
            for (ssize_t vertShift = -shiftLen; vertShift <= shiftLen; vertShift++) {
                std::tie(fixed, movable) = calcSubmatrixes(fixed, movable, vertShift, horShift);
                // FIXME: what if zero-sized image?
                // FIXME: there are non-same-sized images. Use min and max.

                auto metric = squareMean(fixed, movable);
                if (metric <= shiftStor.metric) {
                    // store
                    shiftStor.metric = metric;
                    shiftStor.horShift = horShift;
                    shiftStor.vertShift = vertShift;
                }
            }
        }
        return shiftStor;
    };

    /// calc
    auto gAlignment = calcAlignmentForPair(img.r, img.g);
    auto bAlignment = calcAlignmentForPair(img.r, img.b);

    /// colorize
    for (size_t i = 0; i < img.r.n_rows; i++) {
        for (size_t j = 0; j < img.r.n_cols; j++) {
            auto g = std::get<1>(img.g(i + gAlignment.vertShift, j + gAlignment.horShift));
            img.r(i, j) = std::make_tuple(std::get<0>(img.r(i, j)),
                                          g,
                                          b);
        }
    }

    /// crop
    uint8_t left = std::min({0, })








    return img.r;
}

Image sobel_x(Image src_image) {
    Matrix<double> kernel = {{-1, 0, 1},
                             {-2, 0, 2},
                             {-1, 0, 1}};
    return custom(src_image, kernel);
}

Image sobel_y(Image src_image) {
    Matrix<double> kernel = {{ 1,  2,  1},
                             { 0,  0,  0},
                             {-1, -2, -1}};
    return custom(src_image, kernel);
}

Image unsharp(Image src_image) {
    return src_image;
}

Image gray_world(Image src_image) {
    return src_image;
}

Image resize(Image src_image, double scale) {
    return src_image;
}

Image custom(Image src_image, Matrix<double> kernel) {
    // Function custom is useful for making concrete linear filtrations
    // like gaussian or sobel. So, we assume that you implement custom
    // and then implement other filtrations using this function.
    // sobel_x and sobel_y are given as an example.
    return src_image;
}

Image autocontrast(Image src_image, double fraction) {
    return src_image;
}

Image gaussian(Image src_image, double sigma, int radius)  {
    return src_image;
}

Image gaussian_separable(Image src_image, double sigma, int radius) {
    return src_image;
}

Image median(Image src_image, int radius) {
    return src_image;
}

Image median_linear(Image src_image, int radius) {
    return src_image;
}

Image median_const(Image src_image, int radius) {
    return src_image;
}

Image canny(Image src_image, int threshold1, int threshold2) {
    return src_image;
}
