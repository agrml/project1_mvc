#pragma once


#include "io.h"

template <typename ResT, typename SrcT>
ResT normalizeNumber(SrcT src,
                     ResT min=std::numeric_limits<ResT>::min(),
                     ResT max=std::numeric_limits<ResT>::max());

// fixme: shit on zero-sized matrix
// Q: определяют же in-place! Потом и не должно собираться?
uint norm (ssize_t idx, int n);


using MetricType = uint64_t;
constexpr uint8_t borderHint = 20;

/// assume same-sized images
/// uses red layer
MetricType squareMean(const Image &img1,
                      const Image &img2);

/// assume same-sized images
/// uses red layer
MetricType crossCorrelation(const Image &img1,
                            const Image &img2);

//Image getSubmatrix(const Image &src,
//                    ssize_t vertShift,
//                    ssize_t horShift,
//                    ssize_t vertLen,
//                    ssize_t horLen);

struct ShiftStorage
{
    MetricType metric;
    ssize_t horShift;
    ssize_t vertShift;
};

ShiftStorage calcAlignmentForPair(const Image &fixed, const Image &movable, ssize_t MaxShiftLen);

/// assume same-sized images
std::tuple<Image, Image> calcSubimages(const Image &fixed,
                                       const Image &movable,
                                       ssize_t vertShift,
                                       ssize_t horShift);

/// matrix operator for unary_map method
class ImageOp
{
public:
    uint radius = 0;
    virtual std::tuple<uint, uint, uint> operator()(const Image &neighbourhood) const = 0;
    virtual ~ImageOp() {};
};

using BrightnessType = double;

struct Brightness
{
    BrightnessType r=0, g=0, b=0;
};

class GrayWorldOp : public ImageOp
{
    Brightness coefs_;
public:
    GrayWorldOp(const Brightness &br);
    std::tuple<uint, uint, uint> operator()(const Image &neighbourhood) const override;
};
