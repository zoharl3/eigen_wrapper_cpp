
// instantiation

// warning C4244: 'initializing': conversion from 'double' to 'int', possible
// loss of data
#pragma warning(disable : 4244)

#include <iostream>

#include "eigen_wrapper_impl.h"

namespace EigenWrapper {

template struct Matrix<double, -1, -1>;
template struct Matrix<double, 2, 1>;
template struct Matrix<double, 3, 3>;
template struct Matrix<double, 4, 4>;

// friends
template std::ostream &operator<<( std::ostream &os, const Matrix<double, -1, -1> &mat );
template std::ostream &operator<<( std::ostream &os, const Matrix<double, 4, 4> &mat );

template Matrix<double, 4, 4> operator*( const Matrix<double, 4, 4> &A, const Matrix<double, 4, 4> &B );

} // namespace EigenWrapper





