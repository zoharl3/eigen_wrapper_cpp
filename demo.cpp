
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
    Eigen::VectorXd x;
    x.resize( 4 );
    x.setZero();
    x( 0 ) = 5;
    x.conservativeResize( 3 );
    x.head( 2 )( 1 ) = 2;
    cout << x << endl;

    Eigen::Matrix4d m, m4;
    m4.setConstant( 0.5 );
    m = m4;
    //m = m * m; // m^2
    //m = m * m * m * m * m; // m^5
    m = m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m * m; // m^50
    cout << m << endl;

    return 0;
}
