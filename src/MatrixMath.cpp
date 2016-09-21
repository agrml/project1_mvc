#include "MatrixMath.hpp"


template <typename ResT, typename SrcT>
ResT normalizeNumber(SrcT src,
                     ResT min,
                     ResT max)
{
    if (max < min) {
        throw std::string{"max < min"};
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
auto norm(ssize_t idx, uint n) -> decltype(n)
{
    return normalizeNumber<decltype(n), ssize_t>(idx, 0, n - 1);
}


/// uses red layer
MetricType squareMean(const Image &img1,
                      const Image &img2)
{
    size_t res = 0;
    for (size_t i = borderHint; i < img1.n_rows - borderHint; i++) {
        for (size_t j = borderHint; j < img1.n_cols - borderHint; j++) {
            res += std::pow(std::get<0>(img1(i, j)) - std::get<0>(img2(i, j)), 2);
        }
    }
    return res / (img1.n_cols * img2.n_cols);
}

/// uses red layer
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

Image getSubmatrix(const Image &src,
                    ssize_t vertShift,
                    ssize_t horShift,
                    ssize_t vertLen,
                    ssize_t horLen)
{
    return src.submatrix(norm(vertShift, src.n_rows - 1),
                         norm(horShift, src.n_cols - 1),
                         norm(vertLen, src.n_rows - 1 - vertShift /*todo: max(0, ...)*/),
                         norm(horLen, src.n_cols - 1 - horShift));

}

ShiftStorage calcAlignmentForPair(const Image &fixed, const Image &movable, ssize_t shiftLen)
{
    ShiftStorage shiftStorage{std::numeric_limits<MetricType>::max(), 0, 0};
    for (ssize_t horShift = -shiftLen; horShift <= shiftLen; horShift++) {
        for (ssize_t vertShift = -shiftLen; vertShift <= shiftLen; vertShift++) {
            Image fixedCopy, movableCopy;
            std::tie(fixedCopy, movableCopy) = calcSubmatrixes(fixed, movable, vertShift, horShift);
            // FIXME: what if zero-sized image?
            // --FIXME: there are non-same-sized images. Use min and max.

            auto metric = squareMean(fixedCopy, movableCopy);
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

// FIXME: разного размера как-то они получаются
std::tuple<Image, Image> calcSubmatrixes(const Image &fixed,
                                        const Image &movable,
                                        ssize_t vertShift,
                                        ssize_t horShift)
{
    auto fixedSub = getSubmatrix(fixed,
                                 vertShift,
                                 horShift,
                                 vertShift + fixed.n_rows,
                                 horShift + fixed.n_cols);
    auto movableSub = getSubmatrix(movable,
                                   -vertShift,
                                   -horShift,
                                   -vertShift + movable.n_rows,
                                   -horShift + movable.n_cols);
//        assert(fixedSub.n_rows == movableSub.n_rows);
//        assert(fixedSub.n_rows == movableSub.n_cols);
    return std::tuple<Image, Image>{fixedSub, movableSub};
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