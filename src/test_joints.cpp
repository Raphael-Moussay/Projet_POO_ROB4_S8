#include "../inc/inc.h"


TEST(JointsTest, compareTransforms) {
    const double theta = M_PI / 4.0;
    const double dx = 0.5;

    Eigen::AngleAxisd rotation(theta, Eigen::Vector3d::UnitZ());
    Eigen::Vector3d translation(dx, 0.0, 0.0);

    pinocchio::SE3 refPinocchio(rotation.toRotationMatrix(), translation);
    Eigen::Matrix4d matPinocchio = refPinocchio.toHomogeneousMatrix();

    CJointRevolute joint(-M_PI, M_PI, theta, dx);
    Eigen::Matrix4d matJoint = joint.getTransform();

    EXPECT_TRUE(matPinocchio.isApprox(matJoint, 1e-6));
}

TEST(JointsTest, testJointLimits) {
    CJointPrismatic joint1(0.0, 100.0, 1.0);
    EXPECT_THROW(joint1.setQ(-5.0), std::out_of_range);
    EXPECT_THROW(joint1.setQ(101.0), std::out_of_range);
    EXPECT_NO_THROW(joint1.setQ(50.0));

    // CJointRevolute::getTransform() : I4 pour theta=0, dx=0
    CJointRevolute joint2(-M_PI, M_PI, 0.0, 0.0);
    EXPECT_TRUE(joint2.getTransform().isApprox(Eigen::Matrix4d::Identity(), 1e-6));

    // CJointPrismatic::getTransform() : translation q=1 sur l'axe z
    CJointPrismatic joint3(0.0, 100.0, 1.0);
    Eigen::Matrix4d expectedTransform = Eigen::Matrix4d::Identity();
    expectedTransform(2, 3) = 1.0;
    EXPECT_TRUE(joint3.getTransform().isApprox(expectedTransform, 1e-6));
}

TEST(CompareOperator, testCompareOperator) {
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

    // On fait la multiplication avec pinocchio pour comparer
    auto startPinocchio = std::chrono::high_resolution_clock::now();
    pinocchio::SE3 se3C = se3A * se3B;
    auto endPinocchio = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationPinocchio = endPinocchio - startPinocchio;
    std::cout << "Time taken by Pinocchio multiplication: " << durationPinocchio.count() << " seconds" << std::endl;

    // On vérifie que les résultats sont approximativement égaux
    std::cout << "C_eigen:\n" << C_eigen << std::endl;
    std::cout << "C_manual:\n" << C_manual << std::endl;
    EXPECT_TRUE(C_eigen.isApprox(C_manual, 1e-3));
    std::cout << "C_pinocchio:\n" << se3C.toHomogeneousMatrix() << std::endl;
    EXPECT_TRUE(C_eigen.isApprox(se3C.toHomogeneousMatrix(), 1e-3));
}
void exo1() 
{
    int argc = 1;
    char arg0[] = "run";
    char* argv[] = {arg0, nullptr};
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::GTEST_FLAG(filter) = "JointsTest.compareTransforms:JointsTest.testJointLimits";
    std::ignore = RUN_ALL_TESTS();
}

void exo2() 
{
    int argc = 1;
    char arg0[] = "run";
    char* argv[] = {arg0, nullptr};
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::GTEST_FLAG(filter) = "CompareOperator.testCompareOperator";
    std::ignore = RUN_ALL_TESTS();
}