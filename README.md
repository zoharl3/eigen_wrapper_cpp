
# eigen_wrapper_cpp
A wrapper around the [Eigen](https://eigen.tuxfamily.org/)  library to reduce C++ compilation time.

The wrapper is unobtrusive: It uses the same interface as Eigen, and it can be enabled and disabled with a flag (macro).

Consider the following example:

```cpp
#include <iostream>

#define USE_EIGEN_WRAPPER
#ifdef USE_EIGEN_WRAPPER
    #include "eigen_wrapper.h"
    namespace Eigen = EigenWrapper;
#else
    #include <Eigen/Core>
#endif

using namespace std;

int main() {
    Eigen::Matrix4d m;
    m = m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m; // m^50
    return 0;
}
```

It compiles under a second with the wrapper.
When disabling it, by commenting out the `#define USE_EIGEN_WRAPPER`, it takes seven seconds to compile in debug and two hours(!) in release.

The wrapper isn't comprehensive (don't try to tackle it too much), and I'll add to it functionality (objects and methods) when I need it (send me yours, and I'll add it if it's reasonable).

# Story
I was pondering this idea

https://www.reddit.com/r/cpp/comments/1fmbdl6/functionlevel_make_tool/

I realized that the main issue is the new habit of template inline. There's no more separation of declaration and implementation into header and cpp and worse, functions are usually implemented within the class (inline). This means that for any occurrence of a function, its template is instantiated. 

Ideally, I'd like a tool to separate implementation from headers. In the case of Eigen, it seems tricky, and I used this wrapper instead.

# Performance
The overhead of additional function calls is insignificant. The main problem is allocating memory on the heap (new) for internal Eigen objects even for stack variables. To alleviate that, try when possible to declare variables at hotspot as `thread_local`.

# A real life example
Rather than enabling the wrapper for the whole project, I enable it in the current cpp I'm working on. 

I have a constrained Newton optimization framework that uses auto diff variables. I'm experimenting with the objective function and constraints. Waiting 40 seconds for the build for each tweak was unreasonable, so I put them in a separate file with a wrapper. This file easily exchanges data with the framework in another cpp via:

```cpp
void func( double *p_x, int sz ) {
    VectorXd x( sz );
    memcpy( x.data(), p_x, sz * sizeof( double ) );
}
```
which can be called from another function via
```cpp
VectorXd x( sz );
...
func( x.data(), sz );
```
I'm using FEM, and `x` are the coordinates of an element (rather than the whole mesh).

# To do
- Complete the interface. Adding methods with functionality similar to what I have already should be easy enough.

- Add wrappers for Map and SparseMatrix.


