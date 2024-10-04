
// implementation

#pragma once

#include <Eigen/Dense>

#define MATRIX_TYPE Eigen::Matrix<S, R, C>
#define MATRIX_REF_TYPE Eigen::Ref<Eigen::Matrix<S, R, C>>

#include "eigen_wrapper.h"

namespace EigenWrapper {

template <class S, int R, int C>
Matrix<S, R, C>::Matrix() {
    mat = nullptr;
    ref = nullptr;
}

template <class S, int R, int C>
Matrix<S, R, C>::Matrix( Matrix<S, R, C> &A ) {
    mat = nullptr;
    ref = nullptr;

    if ( A.mat ) {
        mat = new Eigen::Matrix<S, R, C>( *A.mat );
        update_ref();
    } else {
        // transfer ref for head(); need to used shared_ptr instead
        ref = A.ref;
        A.ref = nullptr;
    }
}

template <class S, int R, int C>
Matrix<S, R, C>::~Matrix() {
    delete mat;
    delete ref;
}

template <class S, int R, int C>
void Matrix<S, R, C>::update_ref() {
    delete ref;
    ref = new Eigen::Ref<Eigen::Matrix<S, R, C>>( *mat );
}

template <class S, int R, int C>
template <class E>
Matrix<S, R, C> Matrix<S, R, C>::make_mat( const E &e ) {
    Matrix<S, R, C> P;
    P.mat = new Eigen::Matrix<S, R, C>( e );
    P.update_ref();
    return P;
}

template <class S, int R, int C>
template <class E>
Matrix<S, R, 1> Matrix<S, R, C>::make_col_ref( E &e ) {
    Matrix<S, R, 1> P;
    P.ref = new Eigen::Ref<Eigen::Matrix<S, R, 1>>( e );
    return P;
}

template <class S, int R, int C>
template <class E>
Matrix<S, 1, C> Matrix<S, R, C>::make_row_ref( E &e ) {
    Matrix<S, 1, C> P;
    P.ref = new Eigen::Ref<Eigen::Matrix<S, 1, C>>( e );
    return P;
}

template <class S, int R, int C>
MATRIX_REF_TYPE *Matrix<S, R, C>::m() {
    if ( !ref ) {
        mat = new Eigen::Matrix<S, R, C>();
        update_ref();
    }
    return ref;
}

template <class S, int R, int C>
MATRIX_REF_TYPE *Matrix<S, R, C>::m() const {
    return ref;
}

template <class S, int R, int C>
void Matrix<S, R, C>::setZero() { 
    m()->setZero(); 
}

template <class S, int R, int C>
void Matrix<S, R, C>::setOnes() {
    m()->setOnes();
}

template <class S, int R, int C>
void Matrix<S, R, C>::setIdentity() {
    m()->setIdentity();
}

template <class S, int R, int C>
void Matrix<S, R, C>::setConstant( const S &s ) {
    m()->setConstant( s );
}

template <class S, int R, int C>
void Matrix<S, R, C>::resize( int r, int c ) {
    m(); // create if needed
    assert( mat );
    if constexpr ( C == -1 ) {
        mat->resize( r, c );
        update_ref();
    } else
        assert(0);
}

template <class S, int R, int C>
void Matrix<S, R, C>::resize( int n ) {
    m();
    assert( mat );
    if constexpr ( R == -1 && C == 1 ) {
        mat->resize( n );
        update_ref();
    } else
        assert(0);
}

template <class S, int R, int C>
void Matrix<S, R, C>::conservativeResize( int n ) {
    m();
    assert( mat );
    if constexpr ( R == -1 && C == 1 ) {
        mat->conservativeResize( n );
        update_ref();
    } else
        assert( 0 );
}

template <class S, int R, int C>
void Matrix<S, R, C>::conservativeResize( int r, int c ) {
    assert( mat );
    if constexpr ( C == -1 ) {
        mat->conservativeResize( r, c );
        update_ref();
    } else
        assert( 0 );
}

template <class S, int R, int C>
void Matrix<S, R, C>::conservativeResizeLike( const Matrix<S, R, C> &A ) {
    assert( mat );
    if constexpr ( C == -1 ) {
        mat->conservativeResizeLike( *A.m() );
        update_ref();
    } else
        assert( 0 );
}

template <class S, int R, int C>
int Matrix<S, R, C>::size() {
    return m()->size();
}

template <class S, int R, int C>
int Matrix<S, R, C>::rows() {
    return m()->rows();
}

template <class S, int R, int C>
int Matrix<S, R, C>::cols() {
    return m()->cols();
}

template <class S, int R, int C>
S Matrix<S, R, C>::determinant() {
    return m()->determinant();
}

template <class S, int R, int C>
S Matrix<S, R, C>::norm() {
    return m()->norm();
}

template <class S, int R, int C>
Matrix<S, R, C> Matrix<S, R, C>::inverse() {
    return make_mat( m()->inverse() );
}

template <class S, int R, int C>
Matrix<S, R, C> Matrix<S, R, C>::transpose() {
    return make_mat( m()->transpose() );
}

template <class S, int R, int C>
Matrix<S, R, C> Matrix<S, R, C>::normalized() {
    return make_mat( m()->normalized() );
}

template <class S, int R, int C>
Matrix<S, R, C> Matrix<S, R, C>::reshaped( int r, int c ) {
    return make_mat( m()->reshaped( r, c ) );
}

template <class S, int R, int C>
Matrix<S, 3, 1> Matrix<S, R, C>::cross( const Matrix<S, 3, 1> &v ) {
    if constexpr ( R == 3 && C == 1 )
        return make_mat( m()->cross( v ) );
    else {
        assert( 0 );
        return Matrix<S, 3, 1>();
    }
}

template <class S, int R, int C>
Matrix<S, R, C> Matrix<S, R, C>::cwiseMax( const Matrix<S, R, C> &A ) {
    return make_mat( m()->cwiseMax( *A.m() ) );
}

template <class S, int R, int C>
Matrix<S, R, 1> Matrix<S, R, C>::col( int n ) {
    return make_col_ref( m()->col( n ) );
}

// template <class S, int R, int C>
// Matrix<S, 1, C> Matrix<S, R, C>::row( int n ) {
//     return make_row_ref( m()->row( n ) );
// }

template <class S, int R, int C>
Matrix<S, R, 1> Matrix<S, R, C>::head( int n ) {
    if constexpr ( C == 1 )
        return make_col_ref( m()->head( n ) );
    else {
        assert( 0 );
        return Matrix<S, R, 1>();
    }
}

template <class S, int R, int C>
Matrix<S, R, 1> Matrix<S, R, C>::tail( int n ) {
    if constexpr ( C == 1 )
        return make_col_ref( m()->tail( n ) );
    else {
        assert( 0 );
        return Matrix<S, R, 1>();
    }
}

template <class S, int R, int C>
S& Matrix<S, R, C>::operator()( int n ) {
    if constexpr ( C == 1 )
        return ref->operator()( n );
    else {
        assert( 0 );
        static S s;
        return s;
    }
}

template <class S, int R, int C>
S& Matrix<S, R, C>::operator()( int r, int c ) {
    if constexpr ( C != 1 )
        return ref->operator()( r, c );
    else {
        assert( 0 );
        static S s;
        return s;
    }
}

template <class S, int R, int C>
//template <int R2, int C2>
Matrix<S, R, C>& Matrix<S, R, C>::operator=( const Matrix<S, R, C> &A ) {
    *m() = *A.m();
    return *this;
}

template <class S, int R, int C>
Matrix<S, R, C> Matrix<S, R, C>::Ones( int r, int c ) {
    return make_mat( Eigen::Matrix<S, R, C>::Ones( r, c ) );
}

template <class S, int R, int C>
Matrix<S, R, C> Matrix<S, R, C>::Zero(int n) {
    if constexpr ( C == 1 )
        return make_mat( Eigen::Matrix<S, R, C>::Zero( n ) );
    else {
        assert(0);
        return Matrix<S, R, C>();
    }
}

// friends
template <class S, int R, int C>
std::ostream& operator<<( std::ostream &os, const Matrix<S, R, C> &mat ) {
    os << *mat.m();
    return os;
}

template <class S, int R, int C, int R2, int C2>
Matrix<S, R, C> operator*( const Matrix<S, R, C> &A, const Matrix<S, R2, C2> &B ) {
    Matrix<S, R, C2> P;
    *P.m() = *A.m() * *B.m();
    return P;
}

} // namespace EigenWrapper

