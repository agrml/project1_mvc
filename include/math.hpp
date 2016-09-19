template <typename ResT, typename SrcT>
ResT normalizeNumber(SrcT src,
                     ResT min=std::numeric_limits<ResT>::min(),
                     ResT max=std::numeric_limits<ResT>::max()) {}

/// assume same-sized immages
uint64_t squareMean(Image img1, Image img2, size_t color1, size_t color2) {}

/// assume same-sized immages
uint64_t crossCorrelation(Image img1, Image img2, size_t color1, size_t color2) {}