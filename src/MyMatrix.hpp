//
// Created by mikhail on 20.09.16.
//

//#ifndef ALIGN_PROJECT_MYMATRIX_H
//#define ALIGN_PROJECT_MYMATRIX_H
//
//#endif //ALIGN_PROJECT_MYMATRIX_H


#include "matrix.h"
#include "math.hpp"

template<typename ValueT>
class MyMatrix : public Matrix
{
    // fixme: aaaa
    const MyMatrix<ValueT> submatrix(uint prow,
                                   uint pcol,
                                   uint rows,
                                   uint cols) const = delete;

    const MyMatrix<ValueT> submatrix(ssize_t prow,
                                   ssize_t pcol,
                                   ssize_t rows,
                                   ssize_t cols) const;
};

