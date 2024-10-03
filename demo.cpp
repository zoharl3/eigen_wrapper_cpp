
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
    Eigen::MatrixXd X;
    X.resize( 2, 3 );
    X.setZero();
    cout << X << endl;

    Eigen::Vector2d v2;
    Eigen::Matrix3d m3;

    Eigen::Matrix4d m;
    m.setConstant( 0.5 );
    //m = m * m * m * m * m; // m^5
    m = m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m; // m^50
    cout << m << endl;

    return 0;
}
