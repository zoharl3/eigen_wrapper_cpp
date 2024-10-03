
#include <iostream>

//#define USE_EIGEN_WRAPPER
#ifdef USE_EIGEN_WRAPPER
    #include "eigen_wrapper.h"
    namespace Eigen = EigenWrapper;
#else
    #include <Eigen/Core>
#endif

using namespace std;

int main() {
    Eigen::Matrix<double, -1, -1> x;
    x.resize( 2, 1 );
    x.setZero();
    cout << x << endl;

    Eigen::Matrix<double, 2, -1> v2;
    Eigen::Matrix<double, 3, 3> m3;

    Eigen::Matrix<double, 4, 4> m;
    m.setConstant( 0.5 );
    //m = m * m * m * m * m; // m^5
    m = m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m; // m^50
    cout << m << endl;

    return 0;
}
