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
    struct Img
    {
        Image r{}, g{}, b{};
    };

    Img img;
    img.b = srcImage.submatrix(0, 0, srcImage.n_rows / 3, srcImage.n_cols);
    img.g = srcImage.submatrix(srcImage.n_rows / 3, 0, srcImage.n_rows / 3, srcImage.n_cols);
    img.r = srcImage.submatrix(srcImage.n_rows / 3 * 2, 0, srcImage.n_rows / 3, srcImage.n_cols);

    auto &fixed = img.r;
    for (auto &movable : {img.b, img.g}) {
        constexpr ssize_t lShift = -15, rShift = 15;
        for (ssize_t horShift = lShift; horShift <= rShift; horShift++) {
            for (ssize_t vertShift = lShift; vertShift <= rShift; vertShift++) {
                auto fixedSub = fixed.submatrix(vertShift,
                                                horShift,
                                                vertShift + fixed.n_rows,
                                                horShift + fixed.n_cols);
                auto movableSub = movable.submatrix(-vertShift,
                                                    -horShift,
                                                    -vertShift + movable.n_rows,
                                                    -horShift + movable.n_cols);
                assert(movableSub.n_rows == fixedSub.n_rows);
                assert(movableSub.n_cols == fixedSub.n_cols);

            }
        }
    }


    for (size_t i = 0; i < img.r.n_rows; i++) {
        for (size_t j = 0; j < img.r.n_cols; j++) {
            img.r(i, j) = std::make_tuple(std::get<0>(img.r(i, j)),
                                          std::get<1>(img.g(i, j)),
                                          std::get<2>(img.b(i, j)));
        }
    }

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
