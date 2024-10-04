
#include <iostream>

#define USE_EIGEN_WRAPPER
#ifdef USE_EIGEN_WRAPPER
    #include "eigen_wrapper.h"
    namespace Eigen = EigenWrapper;
#else
    #include <Eigen/Dense>
#endif

using namespace std;

int main() {
    Eigen::VectorXd mx;
    mx.resize( 4 );
    mx.setZero();
    mx( 0 ) = 5;
    mx.conservativeResize( 3 );
    mx.head( 2 )( 1 ) = 2;
    Eigen::Vector3d v3 = mx;
    cout << v3 << endl;

    Eigen::Matrix3d m, m3;
    m3.setConstant( 0.5 );
    m = -m3;
    //m = m * m; // m^2
    m = m * m * m * m * m; // m^5
    //m = m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m; // m^50
    cout << m << endl;

    return 0;
}
