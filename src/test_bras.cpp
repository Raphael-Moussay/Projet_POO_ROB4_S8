#include "../inc/cbras.h"
#include "../inc/cjointprismatic.h"
#include "../inc/cjointrevolute.h"
#include "../inc/test_bras.h"

#include <chrono>
#include <cmath>
#include <iostream>
#include <memory>
#include <utility>

#include <eigen3/Eigen/Dense>
#include <gtest/gtest.h>
#include <pinocchio/spatial/se3.hpp>

TEST(BrasTest, CompareOperator) {
    Eigen::Matrix4d A = Eigen::Matrix4d::Random();
    Eigen::Matrix4d B = Eigen::Matrix4d::Random();
    // On compare le temps pour faire la multiplication d'Eigen et une implémentation manuelle

    // Multiplication avec Eigen
    // On mesure le temps pour la multiplication d'Eigen
    auto startEigen = std::chrono::high_resolution_clock::now();
    Eigen::Matrix4d C_eigen = A * B;
    auto endEigen = std::chrono::high_resolution_clock::now();
    std::ignore = C_eigen; // pour éviter un warning de variable non utilisée
    std::chrono::duration<double> durationEigen = endEigen - startEigen;
    std::cout << "Time taken by Eigen multiplication: " << durationEigen.count() << " seconds" << std::endl;

    // Multiplication manuelle
    auto startManual = std::chrono::high_resolution_clock::now();
    Eigen::Matrix4d C_manual = Eigen::Matrix4d::Zero();
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) {
                C_manual(i, j) += A(i, k) * B(k, j);
            }
        }
    }
    auto endManual = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationManual = endManual - startManual;
    std::cout << "Time taken by manual multiplication: " << durationManual.count() << " seconds" << std::endl;

    // On vérifie que les résultats sont approximativement égaux
    std::cout << "C_eigen:\n" << C_eigen << std::endl;
    std::cout << "C_manual:\n" << C_manual << std::endl;
    EXPECT_TRUE(C_eigen.isApprox(C_manual, 1e-3));
}


TEST(BrasTest, testToHomeneousMatrix) {
    double dx = 1.5;
    Eigen::Vector3d translation(dx, 0.0, 0.0);
    Eigen::Matrix3d rotation = Eigen::AngleAxisd(M_PI / 4.0, Eigen::Vector3d::UnitZ()).toRotationMatrix();
    pinocchio::SE3 pose(rotation, translation);
    Eigen::Matrix4d matriceTransformation = pose.toHomogeneousMatrix();

    CJointRevolute joint(-M_PI, M_PI, M_PI / 4, dx);
    Eigen::Matrix4d homogeneousMatrix =joint.getTransform();

    EXPECT_TRUE(matriceTransformation.isApprox(homogeneousMatrix, 1e-6));
}

 
TEST(BrasTest, computeFK){
    CBras bras;
    Eigen::Matrix4d expectedTransform = Eigen::Matrix4d::Identity();

    EXPECT_EQ(bras.computeFK(), expectedTransform);
}


TEST(BrasTest, computeFKOneRevoluteJoint){
    CBras bras;
    double theta = 0.0;
    double dx = 0.5;
    bras.addJoint(std::make_unique<CJointRevolute>(-M_PI, M_PI, theta, dx));

    Eigen::Matrix4d T = bras.computeFK();
    Eigen::Vector3d translation = T.block<3, 1>(0, 3);
    Eigen::Vector3d expectedPosition(dx, 0.0, 0.0);

    EXPECT_TRUE(translation.isApprox(expectedPosition, 1e-6));
}


TEST(BrasTest, getJointOutOfRange){
    CBras bras;
    bras.addJoint(std::make_unique<CJointRevolute>(-M_PI, M_PI, 0.0, 0.5));
    bras.addJoint(std::make_unique<CJointPrismatic>(0.0, 100.0, 1.0));

    EXPECT_THROW(bras.getJoint(2), std::out_of_range);
    EXPECT_THROW(bras.getJoint(3), std::out_of_range);
    EXPECT_THROW(bras.getJoint(100), std::out_of_range);
}


void exo2() 
{
    int argc = 1;
    char arg0[] = "run";
    char* argv[] = {arg0, nullptr};
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::GTEST_FLAG(filter) = "BrasTest.CompareOperator:BrasTest.computeFK:BrasTest.computeFKOneRevoluteJoint:BrasTest.getJointOutOfRange:BrasTest.testToHomeneousMatrix";
    std::ignore = RUN_ALL_TESTS();
}

//test vérifiant l’idempotence : setQ(getQ()) ne modifie pas l’état du bras.
TEST(BrasTest, idempotence)
{
    CBras bras;
    bras.addJoint(std::make_unique<CJointRevolute>(-M_PI, M_PI, 0.0, 0.5));
    bras.addJoint(std::make_unique<CJointPrismatic>(0.0, 100.0, 1.0));

    Eigen::VectorXd q = bras.getQ();
    bras.setQ(bras.getQ());
    Eigen::VectorXd q_after = bras.getQ();

    EXPECT_TRUE(q.isApprox(q_after, 1e-6));
}

TEST(BrasTest, deep_copy)
{
    CBras bras;
    bras.addJoint(std::make_unique<CJointRevolute>(-M_PI, M_PI, 0.0, 0.5));
    
    CBras bras_copy = bras; 
    bras_copy.addJoint(std::make_unique<CJointPrismatic>(0.0, 100.0, 1.0));

    bras.addJoint(std::make_unique<CJointPrismatic>(0.0, 100.0, 1.0));
    bras.addJoint(std::make_unique<CJointRevolute>(-M_PI, M_PI, 0.0, 0.5));
    
    EXPECT_EQ(bras.getNbJoints(),3);
    EXPECT_EQ(bras_copy.getNbJoints(), 2);
}

TEST(BrasTest,move)
{
    CBras bras;
    bras.addJoint(std::make_unique<CJointRevolute>(-M_PI, M_PI, 0.0, 0.5));
    
    CBras bras_moved = std::move(bras); 

    EXPECT_EQ(bras.getNbJoints(),0); 
    EXPECT_EQ(bras_moved.getNbJoints(),1);
}

void exo3_2() 
{
    int argc = 1;
    char arg0[] = "run";
    char* argv[] = {arg0, nullptr};
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::GTEST_FLAG(filter) = "BrasTest.idempotence:BrasTest.deep_copy:BrasTest.move";
    std::ignore = RUN_ALL_TESTS();
}

