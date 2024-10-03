
// interface--declaration only

#pragma once

namespace EigenWrapper {

#ifndef MATRIX_POINTER_TYPE
#define MATRIX_POINTER_TYPE void *
#endif

template <typename S, int R, int C>
struct Matrix {
    Matrix();
    ~Matrix();

    void setZero();
    void setConstant( const S& s );
    void resize( int r, int c );

    Matrix<S, R, C>& operator=( const Matrix<S, R, C> &A ); // must be a pointer; can't use unique_ptr, which requires a known type

    // friends
    template <typename S, int R, int C>
    friend std::ostream &operator<<( std::ostream &os, const Matrix<S, R, C> &mat );

    template <typename S, int R, int C>
    friend Matrix<S, R, C> operator*( const Matrix<S, R, C> &A, const Matrix<S, R, C> &B );

private:
    MATRIX_POINTER_TYPE m; // inner matrix
};

} // namespace EigenWrapper
