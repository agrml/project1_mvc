#include <assert.h>
#include "MatrixMath.hpp"


template <typename ResT, typename SrcT>
ResT normalizeNumber(SrcT src,
                     ResT min,
                     ResT max)
{
    if (max < min) {
        throw std::string{"normalizeNumber: max < min"};
    }
    if (src < min) {
        return min;
    }
    if (src > max) {
        return max;
    }
    return static_cast<ResT>(src);
}

// fixme: shit on zero-sized matrix
// Q: определяют же in-place! Потом и не должно собираться?
uint norm(ssize_t idx, int n)
{
    return normalizeNumber<uint, ssize_t>(idx, 0, std::max({0, n}));
}


MetricType squareMean(const Image &img1,
                      const Image &img2)
{
    MetricType res = 0;
    for (size_t i = borderHint; i < img1.n_rows - borderHint; i++) {
        for (size_t j = borderHint; j < img1.n_cols - borderHint; j++) {
//            std::cout << std::get<0>(img1(i, j)) << " " << std::get<0>(img2(i, j)) << std::endl;
            res += std::pow(ssize_t(std::get<0>(img1(i, j))) - std::get<0>(img2(i, j)), 2);
        }
    }
    return res / (img1.n_cols * img1.n_rows);
}

MetricType crossCorrelation(const Image &img1,
                            const Image &img2)
{
    size_t res = 0;
    for (size_t i = 0; i < img1.n_rows; i++) {
        for (size_t j = 0; j < img1.n_cols; j++) {
            res += std::get<0>(img1(i, j)) * std::get<0>(img2(i, j));
        }
    }
    return res;
}

//Image getsubmatrix(const Image &src,
//                    ssize_t vertShift,
//                    ssize_t horShift,
//                    ssize_t vertLen,
//                    ssize_t horLen)
//{
//    return src.submatrix(norm(vertShift, src.n_rows - 1),
//                         norm(horShift, src.n_cols - 1),
//                         norm(vertLen, src.n_rows - 1 - vertShift),
//                         norm(horLen, src.n_cols - 1 - horShift));
//
//}

ShiftStorage calcAlignmentForPair(const Image &fixed,
                                  const Image &movable,
                                  ssize_t MaxShiftLen)
{
    ShiftStorage shiftStorage{std::numeric_limits<MetricType>::max(), 0, 0};
    for (ssize_t vertShift = -MaxShiftLen; vertShift <= MaxShiftLen; vertShift++) {
        for (ssize_t horShift = -MaxShiftLen; horShift <= MaxShiftLen; horShift++) {
            Image fixedSub, movableSub;
            std::tie(fixedSub, movableSub) = calcSubimages(fixed, movable, vertShift, horShift);
            auto metric = squareMean(fixedSub, movableSub);
            if (metric <= shiftStorage.metric) {
                // store
                shiftStorage.metric = metric;
                shiftStorage.horShift = horShift;
                shiftStorage.vertShift = vertShift;
            }
        }
    }
    return shiftStorage;
}

template <typename T1, typename T2>
auto max(const T1 &a, const T2 &b) -> decltype(a + b)
{
    if (a < b) {
        return b;
    }
    return a;
};

template <typename T1, typename T2>
auto min(const T1 &a, const T2 &b) -> decltype(a + b)
{
    if (a > b) {
        return b;
    }
    return a;
};

std::tuple<Image, Image> calcSubimages(const Image &fixed,
                                       const Image &movable,
                                       ssize_t vertShift,
                                       ssize_t horShift)
{
    assert(fixed.n_cols == movable.n_cols);
    assert(fixed.n_rows == movable.n_rows);

    auto rows = fixed.n_rows;
    auto cols = fixed.n_cols;
    auto fixedSub = fixed.submatrix(max(0, vertShift),
                                 max(0, horShift),
                                    max(0, rows - std::abs(vertShift)),
                                    max(0, cols - std::abs(horShift)));
    auto movableSub = movable.submatrix(max(0, -vertShift),
                                   max(0, -horShift),
                                   max(0, rows - std::abs(vertShift)),
                                   max(0, cols - std::abs(horShift)));

    assert(fixedSub.n_cols == movableSub.n_cols);
    assert(fixedSub.n_rows == movableSub.n_rows);
    return std::tuple<Image, Image>{fixedSub, movableSub};
}

std::tuple<uint, uint, uint> GrayWorldOp::operator()(const Image &neighbourhood) const
{
    auto cell = neighbourhood(0, 0);
    return std::make_tuple(uint(std::get<0>(cell) * coefs_.r),
                           uint(std::get<1>(cell) * coefs_.g),
                           uint(std::get<2>(cell) * coefs_.b));
}

GrayWorldOp::GrayWorldOp(const Brightness &br) : coefs_(br), radius(0) {}
