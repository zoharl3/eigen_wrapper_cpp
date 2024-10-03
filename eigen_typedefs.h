
#define EIGEN_MAKE_TYPEDEFS(Type, TypeSuffix, Size, SizeSuffix)   \
/** \ingroup matrixtypedefs */                                    \
typedef Matrix<Type, Size, Size> Matrix##SizeSuffix##TypeSuffix;  \
/** \ingroup matrixtypedefs */                                    \
typedef Matrix<Type, Size, 1>    Vector##SizeSuffix##TypeSuffix;  \
/** \ingroup matrixtypedefs */                                    \
typedef Matrix<Type, 1, Size>    RowVector##SizeSuffix##TypeSuffix;

#define EIGEN_MAKE_FIXED_TYPEDEFS(Type, TypeSuffix, Size)         \
/** \ingroup matrixtypedefs */                                    \
typedef Matrix<Type, Size, Dynamic> Matrix##Size##X##TypeSuffix;  \
/** \ingroup matrixtypedefs */                                    \
typedef Matrix<Type, Dynamic, Size> Matrix##X##Size##TypeSuffix;

#define EIGEN_MAKE_TYPEDEFS_ALL_SIZES(Type, TypeSuffix) \
EIGEN_MAKE_TYPEDEFS(Type, TypeSuffix, 2, 2) \
EIGEN_MAKE_TYPEDEFS(Type, TypeSuffix, 3, 3) \
EIGEN_MAKE_TYPEDEFS(Type, TypeSuffix, 4, 4) \
EIGEN_MAKE_TYPEDEFS(Type, TypeSuffix, Dynamic, X) \
EIGEN_MAKE_FIXED_TYPEDEFS(Type, TypeSuffix, 2) \
EIGEN_MAKE_FIXED_TYPEDEFS(Type, TypeSuffix, 3) \
EIGEN_MAKE_FIXED_TYPEDEFS(Type, TypeSuffix, 4)

EIGEN_MAKE_TYPEDEFS_ALL_SIZES(int,                  i)
EIGEN_MAKE_TYPEDEFS_ALL_SIZES(float,                f)
EIGEN_MAKE_TYPEDEFS_ALL_SIZES(double,               d)
EIGEN_MAKE_TYPEDEFS_ALL_SIZES(std::complex<float>,  cf)
EIGEN_MAKE_TYPEDEFS_ALL_SIZES(std::complex<double>, cd)

#undef EIGEN_MAKE_TYPEDEFS_ALL_SIZES
#undef EIGEN_MAKE_TYPEDEFS
#undef EIGEN_MAKE_FIXED_TYPEDEFS

#if EIGEN_HAS_CXX11

#define EIGEN_MAKE_TYPEDEFS(Size, SizeSuffix)                     \
/** \ingroup matrixtypedefs */                                    \
/** \brief \cpp11 */                                              \
template <typename Type>                                          \
using Matrix##SizeSuffix = Matrix<Type, Size, Size>;              \
/** \ingroup matrixtypedefs */                                    \
/** \brief \cpp11 */                                              \
template <typename Type>                                          \
using Vector##SizeSuffix = Matrix<Type, Size, 1>;                 \
/** \ingroup matrixtypedefs */                                    \
/** \brief \cpp11 */                                              \
template <typename Type>                                          \
using RowVector##SizeSuffix = Matrix<Type, 1, Size>;

#define EIGEN_MAKE_FIXED_TYPEDEFS(Size)                           \
/** \ingroup matrixtypedefs */                                    \
/** \brief \cpp11 */                                              \
template <typename Type>                                          \
using Matrix##Size##X = Matrix<Type, Size, Dynamic>;              \
/** \ingroup matrixtypedefs */                                    \
/** \brief \cpp11 */                                              \
template <typename Type>                                          \
using Matrix##X##Size = Matrix<Type, Dynamic, Size>;

EIGEN_MAKE_TYPEDEFS(2, 2)
EIGEN_MAKE_TYPEDEFS(3, 3)
EIGEN_MAKE_TYPEDEFS(4, 4)
EIGEN_MAKE_TYPEDEFS(Dynamic, X)
EIGEN_MAKE_FIXED_TYPEDEFS(2)
EIGEN_MAKE_FIXED_TYPEDEFS(3)
EIGEN_MAKE_FIXED_TYPEDEFS(4)

/** \ingroup matrixtypedefs
  * \brief \cpp11 */
template <typename Type, int Size>
using Vector = Matrix<Type, Size, 1>;

/** \ingroup matrixtypedefs
  * \brief \cpp11 */
template <typename Type, int Size>
using RowVector = Matrix<Type, 1, Size>;

#undef EIGEN_MAKE_TYPEDEFS
#undef EIGEN_MAKE_FIXED_TYPEDEFS

#endif // EIGEN_HAS_CXX11
