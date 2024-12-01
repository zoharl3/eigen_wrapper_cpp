
// implementation

#pragma once

//#include <Eigen/Dense>
#include <Eigen/Core>
#include <Eigen/LU>
#include <Eigen/Geometry>

namespace srcEigen = Eigen;

#define MATRIX_TYPE srcEigen::Matrix<S, R, C>
#define MATRIX_REF_TYPE srcEigen::Ref<MATRIX_TYPE>
#define COMMA_INIT_TYPE srcEigen::CommaInitializer<MATRIX_REF_TYPE>

#include "eigen_wrapper.h"

namespace EigenWrapper {

template <class S, int R, int C>
Matrix<S, R, C>::Matrix() {
    init();
}

template <class S, int R, int C>
Matrix<S, R, C>::Matrix( const S &s1, const S &s2 ) {
    assert( R == 2 && C == 1 );
    init();
    *this << s1, s2;
}

template <class S, int R, int C>
Matrix<S, R, C>::Matrix( const S &s1, const S &s2, const S &s3 ) {
    assert( R == 2 && C == 1 );
    init();
    *this << s1, s2, s3;
}

template <class S, int R, int C>
template <int R2, int C2>
Matrix<S, R, C>::Matrix( Matrix<S, R2, C2> &A ) {
    init();

    if ( A.com() ) {
        if constexpr ( R == R2 && C == C2 ) {
            com() = A.com();
            A.com() = nullptr; // so its d'tor won't delete it
        } else
            assert( 0 );
    } else {
        mat() = new MATRIX_TYPE( *A.m() );
        update_ref();
    }
}

template <class S, int R, int C>
template <int R2, int C2>
Matrix<S, R, C>::Matrix( Matrix<S, R2, C2> &&A ) {
    init();

    if ( A.com() ) { // com
        if constexpr ( R == R2 && C == C2 ) {
            com() = A.com();
            A.com() = nullptr; // so its d'tor won't delete it
        } else
            assert( 0 );

    } else if ( A.mat() || R != R2 || C != C2 ) { // mat
        mat() = new MATRIX_TYPE( *A.m() );
        update_ref();

    } else { //ref
        // transfer ref for make_col_ref() and head(), which return a temporary object that is copied; it should be the same ref that points to the original matrix
        if constexpr ( R == R2 && C == C2 ) {
            m() = A.m();
            A.m() = nullptr; // so its d'tor won't delete it
        }
    }
}

template <class S, int R, int C>
Matrix<S, R, C>::~Matrix() {
    delete mat();
    mat() = nullptr;

    delete m();
    m() = nullptr;

    delete com();
    com() = nullptr;
}

template <class S, int R, int C>
void Matrix<S, R, C>::init() {
    mat() = nullptr;
    m() = nullptr;
    com() = nullptr;
}

template <class S, int R, int C>
void Matrix<S, R, C>::update_ref() {
    delete ref1;
    ref1 = new MATRIX_REF_TYPE( *mat() );
}

template <class S, int R, int C>
template <class E>
Matrix<S, R, C> Matrix<S, R, C>::make_mat( const E &e ) {
    Matrix<S, R, C> P;
    P.mat() = new MATRIX_TYPE( e );
    P.update_ref();
    return P;
}

template <class S, int R, class E>
Matrix<S, R, 1> make_col_ref( const E &e ) {
    Matrix<S, R, 1> P;
    P.m() = new srcEigen::Ref<srcEigen::Matrix<S, R, 1>>( e );
    return P;
}

template <class S, int C, class E>
Matrix<S, 1, C> make_row_ref( E &e ) {
    Matrix<S, 1, C> P;
    P.m() = new srcEigen::Ref<srcEigen::Matrix<S, 1, C>>( e );
    return P;
}

/////

template <class S, int R, int C>
MATRIX_REF_TYPE *&Matrix<S, R, C>::m() {
    if ( !ref1 ) {
        mat() = new MATRIX_TYPE();
        ref1 = new MATRIX_REF_TYPE( *mat() );
    }
    return ref1;
}

template <class S, int R, int C>
MATRIX_REF_TYPE *Matrix<S, R, C>::m() const {
    return ref1;
}

template <class S, int R, int C>
MATRIX_TYPE *&Matrix<S, R, C>::mat() {
    return mat1;
}

template <class S, int R, int C>
COMMA_INIT_TYPE *&Matrix<S, R, C>::com() {
    return com1;
}

/////

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
    assert( mat() );
    if constexpr ( C == -1 ) {
        mat()->resize( r, c );
        update_ref();
    } else
        assert(0);
}

template <class S, int R, int C>
void Matrix<S, R, C>::resize( int n ) {
    m();
    assert( mat() );
    if constexpr ( R == -1 && C == 1 ) {
        mat()->resize( n );
        update_ref();
    } else
        assert(0);
}

template <class S, int R, int C>
void Matrix<S, R, C>::conservativeResize( int n ) {
    m();
    assert( mat() );
    if constexpr ( R == -1 && C == 1 ) {
        mat()->conservativeResize( n );
        update_ref();
    } else
        assert( 0 );
}

template <class S, int R, int C>
void Matrix<S, R, C>::conservativeResize( int r, int c ) {
    assert( mat() );
    if constexpr ( C == -1 ) {
        mat()->conservativeResize( r, c );
        update_ref();
    } else
        assert( 0 );
}

template <class S, int R, int C>
void Matrix<S, R, C>::conservativeResizeLike( const Matrix<S, R, C> &A ) {
    assert( mat() );
    if constexpr ( C == -1 ) {
        mat()->conservativeResizeLike( *A.m() );
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
S *Matrix<S, R, C>::data() {
    return m()->data();
}

template <class S, int R, int C>
S Matrix<S, R, C>::determinant()
    requires( !std::is_integral<S>::value )
{
    return m()->determinant();
}

template <class S, int R, int C>
S Matrix<S, R, C>::norm() {
    return m()->norm();
}

template <class S, int R, int C>
S Matrix<S, R, C>::squaredNorm() {
    return m()->squaredNorm();
}

template <class S, int R, int C>
S Matrix<S, R, C>::dot( const M &A ) {
    if constexpr ( C == 1 )
        return m()->dot( *A.m() );
    else {
        assert( 0 );
        return S();
    }
}

template <class S, int R, int C>
Matrix<S, R, C> Matrix<S, R, C>::inverse() {
    if constexpr ( R == C && std::is_floating_point_v<S> )
        return make_mat( m()->inverse() );
    else {
        assert( 0 );
        return Matrix<S, R, C>();
    }
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
        return make_mat( m()->cross( *v.m() ) );
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
Matrix<S, R, C> Matrix<S, R, C>::cwiseMin( const Matrix<S, R, C> &A ) {
    return make_mat( m()->cwiseMin( *A.m() ) );
}

template <class S, int R, int C>
Matrix<S, R, 1> Matrix<S, R, C>::col( int n ) {
    Matrix<S, R, 1> P( make_col_ref<S, R>( m()->col( n ) ) );
    return P;
}

// template <class S, int R, int C>
// Matrix<S, 1, C> Matrix<S, R, C>::row( int n ) {
//     return make_row_ref( m()->row( n ) );
// }

template <class S, int R, int C>
Matrix<S, R, 1> Matrix<S, R, C>::head( int n ) {
    if constexpr ( C == 1 ) {
        Matrix<S, R, 1> P( make_col_ref<S, R>( m()->head( n ) ) );
        return P;
    } else {
        assert( 0 );
        return Matrix<S, R, 1>();
    }
}

template <class S, int R, int C>
Matrix<S, R, 1> Matrix<S, R, C>::tail( int n ) {
    if constexpr ( C == 1 )
        return make_col_ref<S, R>( m()->tail( n ) );
    else {
        assert( 0 );
        return Matrix<S, R, 1>();
    }
}

template <class S, int R, int C>
S& Matrix<S, R, C>::operator()( int n ) {
    if constexpr ( C == 1 )
        return m()->operator()( n );
    else {
        assert( 0 );
        static S s;
        return s;
    }
}

template <class S, int R, int C>
S& Matrix<S, R, C>::operator()( int r, int c ) {
    if constexpr ( C != 1 )
        return m()->operator()( r, c );
    else {
        assert( 0 );
        static S s;
        return s;
    }
}

template <class S, int R, int C>
S Matrix<S, R, C>::operator()( int n ) const {
    if constexpr ( C == 1 )
        return m()->operator()( n );
    else {
        assert( 0 );
        static S s;
        return s;
    }
}

template <class S, int R, int C>
S Matrix<S, R, C>::operator()( int r, int c ) const {
    if constexpr ( C != 1 )
        return m()->operator()( r, c );
    else {
        assert( 0 );
        static S s;
        return s;
    }
}

template <class S, int R, int C>
template <int R2, int C2>
Matrix<S, R, C>& Matrix<S, R, C>::operator=( const Matrix<S, R2, C2> &A ) {
    *m() = *A.m();
    return *this;
}

template <class S, int R, int C>
Matrix<S, R, C> &Matrix<S, R, C>::operator=( const Matrix<S, R, C> &A ) {
    *m() = *A.m();
    return *this;
}

template <class S, int R, int C>
Matrix<S, R, C> &Matrix<S, R, C>::operator-() {
    *m() = -*m();
    return *this;
}

template <class S, int R, int C>
Matrix<S, R, C> Matrix<S, R, C>::operator<<( const S &s ) {
    Matrix<S, R, C> P;
    P.com() = new COMMA_INIT_TYPE( std::move( *m() << s ) );
    return P;
}

template <class S, int R, int C>
Matrix<S, R, C> Matrix<S, R, C>::operator,( const S &s ) {
    *com(), s;
    return *this;
}

template <class S, int R, int C>
Matrix<S, R, C>& Matrix<S, R, C>::operator/=( const S &s ) {
    *m() /= s;
    return *this;
}

template <class S, int R, int C>
Matrix<S, R, C> Matrix<S, R, C>::Ones( int r, int c ) {
    return make_mat( MATRIX_TYPE::Ones( r, c ) );
}

template <class S, int R, int C>
Matrix<S, R, C> Matrix<S, R, C>::Zero( int n ) {
    if constexpr ( C == 1 )
        return make_mat( MATRIX_TYPE::Zero( n ) );
    else {
        assert(0);
        return Matrix<S, R, C>();
    }
}

template <class S, int R, int C>
Matrix<S, R, C> Matrix<S, R, C>::Identity() {
    if constexpr ( R == C && R != -1 )
        return make_mat( MATRIX_TYPE::Identity() );
    else {
        assert( 0 );
        return Matrix<S, R, C>();
    }
}

// friends
template <class S, int R, int C>
std::ostream& operator<<( std::ostream &os, const Matrix<S, R, C> &mat ) {
    if ( mat.m() )
        os << *mat.m();
    return os;
}

template <class S, int R, int C, class S2, int R2, int C2>
Matrix<S, R, C2> operator*( const Matrix<S, R, C> &A, const Matrix<S2, R2, C2> &B ) {
    Matrix<S, R, C2> P;
    *P.m() = *A.m() * *B.m();
    return P;
}

template <class S, int R, int C, int R2, int C2>
Matrix<S, R, C> operator+( const Matrix<S, R, C> &A, const Matrix<S, R2, C2> &B ) {
    Matrix<S, R, C2> P;
    *P.m() = *A.m() + *B.m();
    return P;
}

template <class S, int R, int C, int R2, int C2>
Matrix<S, R, C> operator-( const Matrix<S, R, C> &A, const Matrix<S, R2, C2> &B ) {
    Matrix<S, R, C2> P;
    *P.m() = *A.m() - *B.m();
    return P;
}

} // namespace EigenWrapper

