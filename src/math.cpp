#include <assert.h>
#include "math.h"

template <typename ResT, typename SrcT>
ResT normalizeNumber(SrcT src,
                     ResT min=std::numeric_limits<ResT>::min(),
                     ResT max=std::numeric_limits<ResT>::max())
{
    if (src < min) {
        return min;
    }
    if (src > max) {
        return max;
    }
    return static_cast<ResT>(src);
}

MetricType squareMean(const Image &img1,
                      const Image &img2,
                      size_t color1=0,
                      size_t color2=0)
{
    size_t res = 0;
    for (size_t i = 0; i < img1.n_rows; i++) {
        for (size_t j = 0; j < img1.n_cols; j++) {
            res += std::pow(std::get<color1>(img1(i, j)) - std::get<color2>(img2(i, j)), 2);
        }
    }
    return res / (img1.n_cols * img2.n_cols);
}

MetricType crossCorrelation(const Image &img1,
                            const Image &img2,
                            size_t color1=0,
                            size_t color2=0)
{
    size_t res = 0;
    for (size_t i = 0; i < img1.n_rows; i++) {
        for (size_t j = 0; j < img1.n_cols; j++) {
            res += std::get<color1>(img1(i, j)) * std::get<color2>(img2(i, j));
        }
    }
    return res;
}

//std::tuple<MetricType, Image> calculateMetric(const Image &fixed,
//                                              const Image &movable,
//                                              ssize_t vertShift,
//                                              ssize_t horShift,
//                                              std::function<uint64_t(Image, Image, size_t, size_t)> &metric)
//{
//    auto fixedSub = fixed.submatrix(vertShift,
//                                    horShift,
//                                    vertShift + fixed.n_rows,
//                                    horShift + fixed.n_cols);
//    auto movableSub = movable.submatrix(-vertShift,
//                                        -horShift,
//                                        -vertShift + movable.n_rows,
//                                        -horShift + movable.n_cols);
//    assert(movableSub.n_rows == fixedSub.n_rows);
//    assert(movableSub.n_cols == fixedSub.n_cols);
//    // TODO: std::finction usage
//    return {fixedSub, metric(fixedSub, movableSub)};
//}