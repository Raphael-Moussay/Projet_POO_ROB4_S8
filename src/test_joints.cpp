#include "../inc/inc.h"

void exo1() {
    /******************************************************************************* 
    1 . Comparaison des matrices Pinocchio et celle de CJointRevolute::getTransform()
    ********************************************************************************/
    const double theta = M_PI / 4.0;
    const double dx = 0.5;
    std::cout << "Comparaison de la matrice calculé avec GetTransform et celle de pinocchio" << std::endl;
    
    Eigen::AngleAxisd rotation(theta, Eigen::Vector3d::UnitZ());
    Eigen::Vector3d translation(dx, 0, 0); // T_rev définit dx sur l'axe X
    
    pinocchio::SE3 refPinocchio(rotation.toRotationMatrix(), translation);
    Eigen::Matrix4d matPinocchio = refPinocchio.toHomogeneousMatrix();
    std::cout << "Matrice de Pinocchio:\n" << matPinocchio << std::endl;

    CJoint * joint = new CJointRevolute(-M_PI, M_PI, theta, dx);
    std::cout << joint->getTransform() << std::endl;
    delete joint;


    /******************************************************************************* 
    2. Tests unitaires pour les classes CJoint, CJointRevolute et CJointPrismatic
    ********************************************************************************/
    CJoint * joint1 = new CJointPrismatic(0, 100, 1);
    //Test de std::out_of_range
    //joint1->setQ(-5); //! ECHEC : 
    /* 
    terminate called after throwing an instance of 'std::out_of_range'
        what():  Joint angle out of bounds
    Abandon (core dumped)
    */
    // joint1->setQ(101); //!ECHEC
    joint1->setQ(50); //! SUCCES : 50 est dans les limites de [0, 100]

    //Test CJointRevolute::getTransform() : I4 pour θ = 0, dx = 0
    CJoint * joint2 = new CJointRevolute(-M_PI, M_PI, 0, 0);
    std::cout << joint2->getTransform() << std::endl;

    //Test CJointPrismatic::getTransform() : translation d = 1 correcte.
    CJoint * joint3 = new CJointPrismatic(0, 100, 1);
    std::cout << joint3->getTransform() << std::endl;
    
    delete joint1;
    delete joint2;
    delete joint3;
}