#pragma once

#include <limits>
#include <cstdint>
#include "io.h"

using MetricType = uint64_t;

template <typename ResT, typename SrcT>
ResT normalizeNumber(SrcT src,
                     ResT min=std::numeric_limits<ResT>::min(),
                     ResT max=std::numeric_limits<ResT>::max());

// fixme: shit on zero-sized matrix
auto norm (ssize_t idx, uint8_t n) -> decltype(n)
{
    return normalizeNumber<decltype(n)>(idx, 0, n - 1);
};

/// assume same-sized immages
MetricType squareMean(const Image &img1,
                      const Image &img2,
                      size_t color1=0,
                      size_t color2=0);

/// assume same-sized immages
MetricType crossCorrelation(const Image &img1,
                            const Image &img2,
                            size_t color1=0,
                            size_t color2=0);

//std::tuple<MetricType, Image> calculateMetric(const Image &fixed,
//                                              const Image &movable,
//                                              ssize_t vertShift,
//                                              ssize_t horShift,
//                                              std::function<uint64_t(Image &, Image &, size_t, size_t)> &metric);
