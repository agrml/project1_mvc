#pragma once


#include "io.h"

template <typename ResT, typename SrcT>
ResT normalizeNumber(SrcT src,
                     ResT min=std::numeric_limits<ResT>::min(),
                     ResT max=std::numeric_limits<ResT>::max());

// fixme: shit on zero-sized matrix
// Q: определяют же in-place! Потом и не должно собираться?
auto norm (ssize_t idx, uint n) -> decltype(n);


using MetricType = uint64_t;
constexpr uint8_t borderHint = 10;

/// assume same-sized immages
MetricType squareMean(const Image &img1,
                      const Image &img2);

/// assume same-sized immages
MetricType crossCorrelation(const Image &img1,
                            const Image &img2);

//std::tuple<MetricType, Image> calculateMetric(const Image &fixed,
//                                              const Image &movable,
//                                              ssize_t vertShift,
//                                              ssize_t horShift,
//                                              std::function<uint64_t(Image &, Image &, size_t, size_t)> &metric);
Image getSubmatrix(const Image &src,
                    ssize_t vertShift,
                    ssize_t horShift,
                    ssize_t vertLen,
                    ssize_t horLen);

struct ShiftStorage
{
    MetricType metric;
    ssize_t horShift;
    ssize_t vertShift;
};

ShiftStorage calcAlignmentForPair(const Image &fixed, const Image &movable, ssize_t shiftLen);

std::tuple<Image, Image> calcSubmatrixes(const Image &fixed,
                                           const Image &movable,
                                           ssize_t vertShift,
                                           ssize_t horShift);