#include "align.h"
#include <string>
#include <assert.h>

#include "MatrixMath.hpp"


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
    constexpr ssize_t MaxShiftLen = 15;

    struct Img
    {
        Image r{}, g{}, b{};
    };

    // split
    Img img;
    auto step = srcImage.n_rows / 3;
    img.b = srcImage.submatrix(0, 0, step, srcImage.n_cols);
    img.g = srcImage.submatrix(step, 0, step, srcImage.n_cols);
    img.r = srcImage.submatrix(2 * step, 0, step, srcImage.n_cols);

    // calc
    // fixme
    auto gAlignment = calcAlignmentForPair(img.r, img.g, MaxShiftLen);
    auto bAlignment = calcAlignmentForPair(img.r, img.b, MaxShiftLen);

    // colorize (3 red images -> 1 RGB image)
    assert(img.r.n_cols == img.g.n_cols && img.g.n_cols == img.b.n_cols);
    assert(img.r.n_rows == img.g.n_rows && img.g.n_rows == img.b.n_rows);
    for (size_t i = 0; i < img.r.n_rows; i++) {
        for (size_t j = 0; j < img.r.n_cols; j++) {
            auto g = std::get<0>(img.g(norm(i - gAlignment.vertShift, img.r.n_rows - 1),
                                       norm(j - gAlignment.horShift, img.r.n_cols - 1)));
            auto b = std::get<0>(img.b(norm(i - bAlignment.vertShift, img.r.n_rows - 1),
                                       norm(j - bAlignment.horShift, img.r.n_cols - 1)));
            img.r(i, j) = std::make_tuple(std::get<0>(img.r(i, j)),
                                          g,
                                          b);
        }
    }

    // crop
    auto row = std::max({ssize_t(0), gAlignment.vertShift, bAlignment.vertShift});
    auto col = std::max({ssize_t(0), gAlignment.horShift, bAlignment.horShift});
    auto rows = std::min({ssize_t(img.r.n_rows - row),
                            img.r.n_rows + gAlignment.vertShift,
                            img.r.n_rows + bAlignment.vertShift});
    auto cols = std::min({ssize_t(img.r.n_cols - col),
                          img.r.n_cols + gAlignment.horShift,
                          img.r.n_cols + bAlignment.horShift});
    auto ans = img.r.submatrix(row, col, rows, cols);

    // postprocessing
    if (isPostprocessing) {
        if (postprocessingType == "--gray-world") {
            return gray_world(ans);
        }
    }
    return ans;
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

Image gray_world(Image src_image)
{
    Brightness br{};
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
    return src_image.unary_map(GrayWorldOp{br});
}

Image resize(Image src_image, double scale) {
    return src_image;
}

//Image custom(Image src_image, Matrix<double> kernel)
//{
//    // TODO: use unary map method
//
//    assert(kernel.n_rows == kernel.n_cols);
////    auto r = kernel.n_rows;
////    for (size_t i = 0; i < src_image.n_rows; i++) {
////        for (size_t j = 0; j < src_image.n_cols; j++) {
////            src_image(i, j) = src_image
////        }
////    }
//    return );
//}

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
