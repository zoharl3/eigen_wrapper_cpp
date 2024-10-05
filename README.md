
# eigen_wrapper
A wrapper around the [Eigen](https://eigen.tuxfamily.org/)  library to reduce C++ compilation time.

This is the motivation:

https://www.reddit.com/r/cpp/comments/1fmbdl6/functionlevel_make_tool/

I don't understand how I can't find a hundred of such wrappers.

This wrapper is a proof of concept, and I'll add to it functionality when I need it.

An example:

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

It compiles under a second.
When commenting out the `#define USE_EIGEN_WRAPPER`, it compiles 7sec in debug, and I didn't have patience to let it finish compiling in release.

Adding methods is easy enough. However, I'd like to automate it by extracting the public interface of a class (all public functions), and create the necessary code with a script.



