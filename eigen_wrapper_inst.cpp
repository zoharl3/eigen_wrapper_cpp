
// instantiation

#include "stdafx.h"

// warning C4244: 'initializing': conversion from 'double' to 'int', possible
// loss of data
#pragma warning(disable : 4244)

#include "eigen_wrapper_impl.h"

namespace EigenWrapper {

#define INST_TYPE int
#include "eigen_wrapper_inst.h"
#undef INST_TYPE

#define INST_TYPE float
#include "eigen_wrapper_inst.h"
#undef INST_TYPE

#define INST_TYPE double
#include "eigen_wrapper_inst.h"
#undef INST_TYPE

} // namespace EigenWrapper





