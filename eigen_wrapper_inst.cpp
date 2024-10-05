
// instantiation

#include "stdafx.h"

// warning C4244: 'initializing': conversion from 'double' to 'int', possible
// loss of data
#pragma warning(disable : 4244)

#include <iostream>

#include "eigen_wrapper_impl.h"

namespace EigenWrapper {

// matrices
template struct Matrix<double, -1, -1>;
template struct Matrix<double, 2, 2>;
template struct Matrix<double, 3, 3>;

// vectors
template struct Matrix<double, -1, 1>;
template struct Matrix<double, 2, 1>;
template struct Matrix<double, 3, 1>;

// friends
template std::ostream &operator<<( std::ostream &os, const Matrix<double, -1, -1> &mat );
template std::ostream &operator<<( std::ostream &os, const Matrix<double, 3, 3> &mat );

template std::ostream &operator<<( std::ostream &os, const Matrix<double, -1, 1> &mat );
template std::ostream &operator<<( std::ostream &os, const Matrix<double, 3, 1> &mat );

template Matrix<double, 3, 3> operator*( const Matrix<double, 3, 3> &A, const Matrix<double, 3, 3> &B );

template Matrix<double, 3, 1> operator+( const Matrix<double, 3, 1> &A, const Matrix<double, 3, 1> &B );
template Matrix<double, 3, 1> operator+( const Matrix<double, 3, 1> &A, const Matrix<double, -1, 1> &B );

template Matrix<double, 3, 1> operator-( const Matrix<double, 3, 1> &A, const Matrix<double, 3, 1> &B );
template Matrix<double, 3, 1> operator-( const Matrix<double, 3, 1> &A, const Matrix<double, -1, 1> &B );

// conversion 'ctor
template Matrix<double, 3, 1>::Matrix( Matrix<double, -1, 1> &A );

} // namespace EigenWrapper





