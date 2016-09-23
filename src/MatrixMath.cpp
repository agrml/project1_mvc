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

Image mirror(const Image &src, uint radius)
{
    Image ans{src.n_rows + 2 * radius, src.n_cols + 2 * radius};
    for (uint i = 0; i < ans.n_rows; i++) {
        for (uint j = 0; j < ans.n_cols; j++) {
            long x = std::abs(long(i) - radius);
            long y = std::abs(long(j) - radius);
            if (x >= long(src.n_rows)) {
                x = src.n_rows - (x - src.n_rows) - 1;
            }
            if (y >= long(src.n_cols)) {
                y = src.n_cols - (y - src.n_cols) - 1;
            }
            ans(i, j) = src(x, y);
        }
    }
    return ans;
}


ConvolutionOp::ConvolutionOp(const Matrix<double> &kernel) : kernel_(kernel), radius(kernel.n_rows) {}

std::tuple<uint, uint, uint> ConvolutionOp::operator()(const Image &neighbourhood) const
{
    // matrices "multiplication"
    assert(neighbourhood.n_cols == neighbourhood.n_rows);
    assert(radius == (neighbourhood.n_cols - 1) / 2);

    double r = 0, g = 0, b = 0;
    double sum_r = 0, sum_g = 0, sum_b = 0;
    for (size_t i = 0; i < radius; i++) {
        for (size_t j = 0; j < radius; j++) {
            std::tie(r, g, b) = neighbourhood(i, j);
            sum_r += r * kernel_(i, j);
            sum_g += g * kernel_(i, j);
            sum_b += b * kernel_(i, j);
        }
    }
    return std::make_tuple(normalizeNumber(sum_r, uint8_t(0), std::numeric_limits<uint8_t>::max()),
                           normalizeNumber(sum_g, uint8_t(0), std::numeric_limits<uint8_t>::max()),
                           normalizeNumber(sum_b, uint8_t(0), std::numeric_limits<uint8_t>::max()));
}
