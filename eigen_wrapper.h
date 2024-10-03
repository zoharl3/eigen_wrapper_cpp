
// interface--declaration only

#pragma once

#include <complex>

namespace EigenWrapper {

const int Dynamic = -1;

#ifndef MATRIX_POINTER_TYPE
#define MATRIX_POINTER_TYPE void *
#endif

template <typename S, int R, int C>
struct Matrix {
    Matrix();
    Matrix( Matrix<S, R, C> &A );
    ~Matrix();

    void setZero();
    void setConstant( const S& s );
    void resize( int r, int c );
    void conservativeResize(int r, int c);

    Matrix<S, R, C>& operator=( const Matrix<S, R, C> &A ); 

    // friends
    template <typename S, int R, int C>
    friend std::ostream &operator<<( std::ostream &os, const Matrix<S, R, C> &mat );

    template <typename S, int R, int C, int R2, int C2>
    friend Matrix<S, R, C> operator*( const Matrix<S, R, C> &A, const Matrix<S, R2, C2> &B );

private:
    MATRIX_POINTER_TYPE m; // inner matrix; must be a pointer; can't use unique_ptr, which requires a known type
};

#include "eigen_typedefs.h"

} // namespace EigenWrapper
