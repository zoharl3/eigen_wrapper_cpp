
// instantiation

// matrices
template struct Matrix<INST_TYPE, -1, 1>;
template struct Matrix<INST_TYPE, -1, -1>;

template struct Matrix<INST_TYPE, 2, 1>;
template struct Matrix<INST_TYPE, 2, 2>;

template struct Matrix<INST_TYPE, 3, 1>;
template struct Matrix<INST_TYPE, 3, 3>;

// friends
template std::ostream &operator<<( std::ostream &os, const Matrix<INST_TYPE, -1, 1> &mat );
template std::ostream &operator<<( std::ostream &os, const Matrix<INST_TYPE, -1, -1> &mat );

template std::ostream &operator<<( std::ostream &os, const Matrix<INST_TYPE, 2, 1> &mat );
template std::ostream &operator<<( std::ostream &os, const Matrix<INST_TYPE, 2, 2> &mat );

template std::ostream &operator<<( std::ostream &os, const Matrix<INST_TYPE, 3, 1> &mat );
template std::ostream &operator<<( std::ostream &os, const Matrix<INST_TYPE, 3, 3> &mat );

template Matrix<INST_TYPE, 2, 2> operator*( const Matrix<INST_TYPE, 2, 2> &A, const Matrix<INST_TYPE, 2, 2> &B );
template Matrix<INST_TYPE, 3, 3> operator*( const Matrix<INST_TYPE, 3, 3> &A, const Matrix<INST_TYPE, 3, 3> &B );

template Matrix<INST_TYPE, 2, 1> operator+( const Matrix<INST_TYPE, 2, 1> &A, const Matrix<INST_TYPE, 2, 1> &B );
template Matrix<INST_TYPE, 3, 1> operator+( const Matrix<INST_TYPE, 3, 1> &A, const Matrix<INST_TYPE, 3, 1> &B );
template Matrix<INST_TYPE, 3, 1> operator+( const Matrix<INST_TYPE, 3, 1> &A, const Matrix<INST_TYPE, -1, 1> &B );

template Matrix<INST_TYPE, 2, 1> operator-( const Matrix<INST_TYPE, 2, 1> &A, const Matrix<INST_TYPE, 2, 1> &B );
template Matrix<INST_TYPE, 3, 1> operator-( const Matrix<INST_TYPE, 3, 1> &A, const Matrix<INST_TYPE, 3, 1> &B );
template Matrix<INST_TYPE, 3, 1> operator-( const Matrix<INST_TYPE, 3, 1> &A, const Matrix<INST_TYPE, -1, 1> &B );

// conversion 'ctor
template Matrix<INST_TYPE, 3, 1>::Matrix( Matrix<INST_TYPE, -1, 1> &A );
template Matrix<INST_TYPE, 3, 1>::Matrix( Matrix<INST_TYPE, -1, 1> &&A );







