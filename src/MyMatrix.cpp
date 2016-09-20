//
// Created by mikhail on 20.09.16.
//

#include "MyMatrix.hpp"

template<typename ValueT>
const MyMatrix<ValueT> MyMatrix<ValueT>::submatrix(ssize_t prow,
                                                   ssize_t pcol,
                                                   ssize_t rows,
                                                   ssize_t cols) const
{
    auto norm = [] (ssize_t idx, uint n) {
        return normalizeNumber<decltype(n)>(idx, 0, n - 1);
    };
    // copying requested data to submatrix.
    MyMatrix<ValueT> tmp(*this);
    make_rw(tmp.n_rows) = norm(rows, this->n_rows);
    make_rw(tmp.n_cols) = norm(cols, this->n_cols);
    make_rw(tmp.pin_row) = norm(pin_row + prow, this->n_rows);
    make_rw(tmp.pin_col) = norm(pin_col + pcol, this->n_cols);
    return tmp;
}