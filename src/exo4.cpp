#include "../inc/cjoint.h"
#include "../inc/cjointprismatic.h"
#include "../inc/cjointrevolute.h"
#include "../inc/cjointrevolute_with_axe.h"
#include "../inc/cbras.h" 
#include "../inc/colors.h"  

#include <pinocchio/multibody/fcl.hpp>
#include <pinocchio/multibody/model.hpp>
#include <pinocchio/multibody/data.hpp>
#include <pinocchio/parsers/urdf.hpp>
#include <pinocchio/algorithm/kinematics.hpp>
#include <pinocchio/algorithm/geometry.hpp>



void exo4()
{
    colors(F_YELLOW);
    std::cout << "====================================================" << std::endl;
    std::cout << "Création du bras 4-DDL..." << std::endl;
    std::cout << "====================================================" << std::endl;
    colors(RESET);
    CBras bras;
    bras.addJoint(std::make_unique<CJointRevolute>(-M_PI, M_PI, 0.0, 0.3)); //Epaule
    bras.addJoint(std::make_unique<CJointRevolute>(-M_PI/2, M_PI/2, 1, 0.25)); //Coude
    bras.addJoint(std::make_unique<CJointPrismatic>(0.0, 0.2, 0.1)); //Ext
    bras.addJoint(std::make_unique<CJointRevolute>(-M_PI, M_PI, 0, 0.05)); //Poignet

    
    colors(F_YELLOW);
    std::cout << "====================================================\n";
    std::cout << "Balayage de l'épaule de -Pi/2 à Pi/2 par pas de Pi/8...\n";
    std::cout << "====================================================\n";

    colors(F_PURPLE);
    std::cout << "Calcul de la matrice de transformation homogène..." << std::endl;
    colors(RESET);
    Eigen::Matrix4d T = bras.computeFK();
    std::cout << "Position de initiale de l'effecteur : \n" << T.block<3,1>(0,3).transpose() << std::endl;
    
    
    for(double q0 = -M_PI/2; q0 <= M_PI/2; q0 += M_PI/8)
    {
        Eigen::VectorXd q = bras.getQ();
        q(0) = q0;
        bras.setQ(q);
        
        // affichage de la position de l'effecteur via T.block<3,1>(0,3).transpose()
        colors(F_PURPLE);
        std::cout << "Calcul de la matrice de transformation homogène..." << std::endl;
        colors(RESET);
        Eigen::Matrix4d T = bras.computeFK();
        std::cout << "Position n°" << (q(0) + M_PI/2) / (M_PI/8) + 1 << " de l'effecteur : \n" << T << std::endl;
        //.block<3,1>(0,3).transpose()
    }
    colors(F_YELLOW);
    std::cout << "====================================================\n";
    std::cout << "Affichage de la configuration du bras...\n";
    std::cout << "====================================================\n";
    colors(RESET);
    std:: cout << bras;
    colors(F_YELLOW);
    std::cout << "====================================================\n";
    std::cout << "Chargement de l'UR5...\n";
    std::cout << "====================================================\n";
    colors(RESET);

    std::string urdf_path = "/opt/openrobots/share/example-robot-data/robots/ur_description/urdf/ur5_robot.urdf";

    pinocchio::Model model;
    pinocchio::urdf::buildModel(urdf_path, model);
    pinocchio::Data data(model);
    Eigen::VectorXd q = pinocchio::randomConfiguration(model);
    std::cout << "Configuration aléatoire de l'UR5 : " << q.transpose() << std::endl;
    pinocchio::forwardKinematics(model, data, q);
    // Eigen::Matrix4d T = data.oMi[4].toHomogeneousMatrix();
    // std::cout << "Position de l'effecteur de l'UR5 : \n" << T.block<3,1>(0,3).transpose() << std::endl;

    std::cout << "====================================================\n";
    std::cout << "Création du bras UR5..." << std::endl;
    std::cout << "====================================================\n";
    CBras UR5_bras;
    UR5_bras.addJoint(std::make_unique<CJointRevoluteWithAxe>(
        -2.0 * M_PI, 2.0 * M_PI, q(0),
        Eigen::Vector3d(0.0, 0.0, 1.0),
        Eigen::Vector3d(0.0, 0.0, 0.089159),
        Eigen::Vector3d(0.0, 0.0, 0.0))); // shoulder_pan_joint

    UR5_bras.addJoint(std::make_unique<CJointRevoluteWithAxe>(
        -2.0 * M_PI, 2.0 * M_PI, q(1),
        Eigen::Vector3d(0.0, 1.0, 0.0),
        Eigen::Vector3d(0.0, 0.13585, 0.0),
        Eigen::Vector3d(0.0, 1.57079632679, 0.0))); // shoulder_lift_joint

    UR5_bras.addJoint(std::make_unique<CJointRevoluteWithAxe>(
        -M_PI, M_PI, q(2),
        Eigen::Vector3d(0.0, 1.0, 0.0),
        Eigen::Vector3d(0.0, -0.1197, 0.425),
        Eigen::Vector3d(0.0, 0.0, 0.0))); // elbow_joint

    UR5_bras.addJoint(std::make_unique<CJointRevoluteWithAxe>(
        -2.0 * M_PI, 2.0 * M_PI, q(3),
        Eigen::Vector3d(0.0, 1.0, 0.0),
        Eigen::Vector3d(0.0, 0.0, 0.39225),
        Eigen::Vector3d(0.0, 1.57079632679, 0.0))); // wrist_1_joint

    UR5_bras.addJoint(std::make_unique<CJointRevoluteWithAxe>(
        -2.0 * M_PI, 2.0 * M_PI, q(4),
        Eigen::Vector3d(0.0, 0.0, 1.0),
        Eigen::Vector3d(0.0, 0.093, 0.0),
        Eigen::Vector3d(0.0, 0.0, 0.0))); // wrist_2_joint

    UR5_bras.addJoint(std::make_unique<CJointRevoluteWithAxe>(
        -2.0 * M_PI, 2.0 * M_PI, q(5),
        Eigen::Vector3d(0.0, 1.0, 0.0),
        Eigen::Vector3d(0.0, 0.0, 0.09465),
        Eigen::Vector3d(0.0, 0.0, 0.0))); // wrist_3_joint


}