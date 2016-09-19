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

uint64_t squareMean(Image img1, Image img2, size_t color1, size_t color2)
{
    size_t res = 0;
    for (size_t i = 0; i < img1.n_rows; i++) {
        for (size_t j = 0; j < img1.n_cols; j++) {
            res += std::pow(std::get<color1>(img1(i, j)) - std::get<color2>(img2(i, j)), 2);
        }
    }
    return res / (img1.n_cols * img2.n_cols);
}

uint64_t crossCorrelation(Image img1, Image img2, size_t color1, size_t color2)
{
    size_t res = 0;
    for (size_t i = 0; i < img1.n_rows; i++) {
        for (size_t j = 0; j < img1.n_cols; j++) {
            res += std::get<color1>(img1(i, j)) * std::get<color2>(img2(i, j));
        }
    }
    return res;
}