
// implementation

#pragma once

#include <Eigen/Core>

#define MATRIX_POINTER_TYPE Eigen::Matrix<S, R, C> *

#include "eigen_wrapper.h"

namespace EigenWrapper {

template <typename S, int R, int C>
Matrix<S, R, C>::Matrix() {
    m = new Eigen::Matrix<S, R, C>();
}

template <typename S, int R, int C>
Matrix<S, R, C>::~Matrix() {
    delete m;
}

template <typename S, int R, int C>
void Matrix<S, R, C>::setZero() { 
    m->setZero(); 
}

template <typename S, int R, int C>
void Matrix<S, R, C>::setConstant( const S &s ) {
    m->setConstant( s );
}

template <typename S, int R, int C>
void Matrix<S, R, C>::resize( int r, int c ) {
    m->resize( r, c );
}

template <typename S, int R, int C>
void Matrix<S, R, C>::conservativeResize( int r, int c ) {
    if constexpr ( R == -1 )
        m->conservativeResize( r, c );
}

template <typename S, int R, int C>
Matrix<S, R, C>& Matrix<S, R, C>::operator=( const Matrix<S, R, C> &A ) {
    *m = *A.m;
    return *this;
}

// friends
template <typename S, int R, int C>
std::ostream &operator<<( std::ostream &os, const Matrix<S, R, C> &mat ) {
    os << *mat.m;
    return os;
}

template <typename S, int R, int C, int R2, int C2>
Matrix<S, R, C> operator*( const Matrix<S, R, C> &A, const Matrix<S, R2, C2> &B ) {
    Matrix<S, R, C2> P;
    *P.m = *A.m * *B.m;
    return P;
}

} // namespace EigenWrapper

