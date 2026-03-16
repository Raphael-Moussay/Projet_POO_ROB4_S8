#include "../inc/inc.h"

TEST(BrasTest, computeFK){
    CBras bras;
    Eigen::Matrix4d expectedTransform = Eigen::Matrix4d::Identity();

    EXPECT_EQ(bras.computeFK(), expectedTransform);
}

//1 joint rotatif (θ = 0, dx = 0,5 m) : extraire la translation avec T.block<3,1>(0,3) et vérifier l’effecteur en
//(0,5; 0; 0).
TEST(BrasTest, computeFKOneRevoluteJoint){
    CBras bras;
    double theta = 0.0;
    double dx = 0.5;
    bras.addJoint(std::make_unique<CJointRevolute>(-M_PI, M_PI, theta, dx));

    Eigen::Matrix4d expectedTransform = Eigen::Matrix4d::Identity();
    expectedTransform(0, 3) = dx;

    EXPECT_TRUE(bras.computeFK().isApprox(expectedTransform, 1e-6));
}

//getJoint(i) lève std::out_of_range pour i ≥ N
TEST(BrasTest, getJointOutOfRange){
    CBras bras;
    bras.addJoint(std::make_unique<CJointRevolute>(-M_PI, M_PI, 0.0, 0.5));
    bras.addJoint(std::make_unique<CJointPrismatic>(0.0, 100.0, 1.0));

    EXPECT_THROW(bras.getJoint(2), std::out_of_range);
    EXPECT_THROW(bras.getJoint(3), std::out_of_range);
    EXPECT_THROW(bras.getJoint(100), std::out_of_range);
}

void exo3() 
{
    int argc = 1;
    char arg0[] = "run";
    char* argv[] = {arg0, nullptr};
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::GTEST_FLAG(filter) = "BrasTest.computeFK:BrasTest.computeFKOneRevoluteJoint:BrasTest.getJointOutOfRange";
    std::ignore = RUN_ALL_TESTS();
}