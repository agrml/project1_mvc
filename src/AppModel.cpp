#include <glog/logging.h>
#include <assert.h>

#include "io.hpp"
#include "AppModel.hpp"
#include "align.hpp"
#include "MatrixMath.hpp"



// model storage. may be placed to main

Image AppModel::getImg() const
{
    return *img_;
}

void AppModel::setImg(const Image &img)
{
    *img_ = img;
    emit modelUpdated();
}


void AppModel::align(bool isPostprocessing,
            const std::string &postprocessingType,
            bool isMirror)
{
    constexpr ssize_t MaxShiftLen = 15;

    struct Img
    {
        Image r{}, g{}, b{};
    };

    // split
    Img img;
    auto step = img_->n_rows / 3;
    img.b = img_->submatrix(0, 0, step, img_->n_cols);
    img.g = img_->submatrix(step, 0, step, img_->n_cols);
    img.r = img_->submatrix(2 * step, 0, step, img_->n_cols);
    emit log("Image is splited to chenels");

    // calc
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
    this->setImg(ans);
    emit log("Chenels are combined.");

    constexpr uint unsharpMirrorLen = 2;
    // postprocessing
    if (isPostprocessing) {
        if (postprocessingType == "gray-world") {
            ans = gray_world(ans);
        } else if (postprocessingType == "unsharp") {
            bool flag = isMirror && unsharpMirrorLen <= ans.n_cols && unsharpMirrorLen <= ans.n_rows;
            if (flag) {
                ans = mirror(ans, unsharpMirrorLen);
            }
            ans = unsharp(ans);
            if (flag) {
                ans = ans.submatrix(unsharpMirrorLen,
                                    unsharpMirrorLen,
                                    ans.n_rows - 2 * unsharpMirrorLen,
                                    ans.n_cols - 2 * unsharpMirrorLen);
            }
        }
    }
    this->setImg(ans);
    emit log("Postprocessing is done. Alignment is finished.");
}