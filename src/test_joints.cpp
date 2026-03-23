#include "../inc/cjointprismatic.h"
#include "../inc/cjointrevolute.h"
#include "../inc/test_joints.h"

#include <cmath>
#include <utility>

#include <eigen3/Eigen/Dense>
#include <gtest/gtest.h>
#include <pinocchio/spatial/se3.hpp>


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


void exo1() 
{
    int argc = 1;
    char arg0[] = "run";
    char* argv[] = {arg0, nullptr};
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::GTEST_FLAG(filter) = "JointsTest.compareTransforms:JointsTest.testJointLimits";
    std::ignore = RUN_ALL_TESTS();
}

