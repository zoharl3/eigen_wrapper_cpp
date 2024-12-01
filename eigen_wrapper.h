
// interface--declaration only

#pragma once

#include <complex>

namespace EigenWrapper {

const int Dynamic = -1;

#ifndef MATRIX_TYPE
#define MATRIX_TYPE void
#define MATRIX_REF_TYPE void
#define COMMA_INIT_TYPE void
#endif

template <class S, int R, int C>
struct Matrix {
    using M = Matrix<S, R, C>;

    Matrix();
    Matrix( const S &s1, const S &s2 );
    Matrix( const S &s1, const S &s2, const S &s3 );

    template <int R2, int C2>
    Matrix( Matrix<S, R2, C2> &A );

    template <int R2, int C2>
    Matrix( Matrix<S, R2, C2> &&A );

    ~Matrix();

    void init();

    void setZero();
    void setOnes();
    void setIdentity();
    void setConstant( const S& s );
    void resize( int r, int c );
    void resize( int n );
    void conservativeResize( int n );
    void conservativeResize( int r, int c );

    void conservativeResizeLike( const M &A );

    int size();
    int rows();
    int cols();

    S* data();

    S determinant()
        requires( !std::is_integral<S>::value );

    S norm();
    S squaredNorm();
    S dot( const M &A );

    M inverse();
    M transpose();
    M normalized();
    M reshaped( int r, int c );

    Matrix<S, 3, 1> cross( const Matrix<S, 3, 1> &v );

    M cwiseMax( const M &A );
    M cwiseMin( const M &A );

    Matrix<S, R, 1> col( int n );
    //Matrix<S, 1, C> row( int n );
    Matrix<S, R, 1> head( int n );
    Matrix<S, R, 1> tail( int n );

    S &operator()( int n );
    S &operator()( int r, int c );

    S operator()( int n ) const;
    S operator()( int r, int c ) const;

    template <int R2, int C2>
    M &operator=( const Matrix<S, R2, C2> &A );

    M &operator=( const Matrix<S, R, C> &A ); // need both

    M &operator-();
    M operator<<( const S &s );
    M operator,( const S &s );
    M &operator/=( const S &s );

    // static
    static M Ones( int r, int c );
    static M Zero( int n );
    static M Identity();

    // friends
    template <class S, int R, int C>
    friend std::ostream &operator<<( std::ostream &os, const Matrix<S, R, C> &mat );

    template <class S, int R, int C, class S2, int R2, int C2>
    friend Matrix<S, R, C2> operator*( const Matrix<S, R, C> &A, const Matrix<S2, R2, C2> &B );

    template <class S, int R, int C, int R2, int C2>
    friend Matrix<S, R, C> operator+( const Matrix<S, R, C> &A, const Matrix<S, R2, C2> &B );

    template <class S, int R, int C, int R2, int C2>
    friend Matrix<S, R, C> operator-( const Matrix<S, R, C> &A, const Matrix<S, R2, C2> &B );

    virtual MATRIX_REF_TYPE *&m(); // returns ref
    virtual MATRIX_REF_TYPE *m() const;

    virtual MATRIX_TYPE *&mat(); // returns mat
    virtual COMMA_INIT_TYPE *&com(); // returns com

// private: // complicates matters--requires to give friend access
    void update_ref();

    template <class E>
    static M make_mat( const E &e ); // make matrix from eigen type

    template <class S, int R, class E>
    friend Matrix<S, R, 1> make_col_ref( const E &e ); // make ref(-only) matrix from eigen type; different template parameters (C=1) means a different class

    template <class S, int C, class E>
    friend Matrix<S, 1, C> make_row_ref( E &e );

private:
    MATRIX_TYPE *mat1; // may remain null
    MATRIX_REF_TYPE *ref1; // may have only a ref
    COMMA_INIT_TYPE *com1;
};

typedef std::ptrdiff_t Index;

#include "eigen_typedefs.h"

} // namespace EigenWrapper
