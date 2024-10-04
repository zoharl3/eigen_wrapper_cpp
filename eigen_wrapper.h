
// interface--declaration only

#pragma once

#include <complex>

namespace EigenWrapper {

const int Dynamic = -1;

#ifndef MATRIX_TYPE
#define MATRIX_TYPE void
#define MATRIX_REF_TYPE void
#endif

template <class S, int R, int C>
struct Matrix {
    using M = Matrix<S, R, C>;

    Matrix();
    Matrix( M &A );
    ~Matrix();

    void setZero();
    void setOnes();
    void setIdentity();
    void setConstant( const S& s );
    void resize( int r, int c );
    void resize( int n );
    void conservativeResize( int n );
    void conservativeResize(int r, int c);

    void conservativeResizeLike( const M &A );

    int size();
    int rows();
    int cols();

    S determinant();
    S norm();

    M inverse();
    M transpose();
    M normalized();
    M reshaped( int r, int c );

    Matrix<S, 3, 1> cross( const Matrix<S, 3, 1> &v );

    M cwiseMax( const M &A );

    Matrix<S, R, 1> col( int n );
    //Matrix<S, 1, C> row( int n );
    Matrix<S, R, 1> head( int n );
    Matrix<S, R, 1> tail( int n );

    S &operator()( int n );
    S &operator()( int r, int c );

    M& operator=( const M &A ); 

    // static
    static M Ones( int r, int c );
    static M Zero( int n );

    // friends
    template <class S, int R, int C>
    friend std::ostream &operator<<( std::ostream &os, const Matrix<S, R, C> &mat );

    template <class S, int R, int C, int R2, int C2>
    friend Matrix<S, R, C> operator*( const Matrix<S, R, C> &A, const Matrix<S, R2, C2> &B );

//private:
    MATRIX_REF_TYPE *m(); // returns ref
    MATRIX_REF_TYPE *m() const;

    void update_ref();

    template <class E>
    static M make_mat( const E &e ); // make matrix from eigen type

    template <class E>
    Matrix<S, R, 1> make_col_ref( E &e ); // make ref(-only) matrix from eigen type

    template <class E>
    Matrix<S, 1, C> make_row_ref( E &e );

    MATRIX_TYPE *mat; // may remain null
    MATRIX_REF_TYPE *ref; // may have only a ref
};

typedef std::ptrdiff_t Index;

#include "eigen_typedefs.h"

} // namespace EigenWrapper
