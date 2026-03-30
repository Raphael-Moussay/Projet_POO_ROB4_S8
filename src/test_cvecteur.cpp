#include "../inc/cvecteur.h"

#include <cmath>
#include <eigen3/Eigen/Dense>
#include <gtest/gtest.h>

#define N 3 // taille du vecteur pour les tests

namespace {

CVecteur<double, N> makeVec3(double x, double y, double z) {
	CVecteur<double, N> v;
	v[0] = x;
	v[1] = y;
	v[2] = z;
	return v;
}

}  // namespace

TEST(CVecteurTest, AccessOperatorReadWrite) {
	CVecteur<double, N> v;
	v[0] = 2.0;
	v[1] = -1.5;
	v[2] = 4.25;

	EXPECT_DOUBLE_EQ(v[0], 2.0);
	EXPECT_DOUBLE_EQ(v[1], -1.5);
	EXPECT_DOUBLE_EQ(v[2], 4.25);
}

TEST(CVecteurTest, AdditionElementWise) {
	const CVecteur<double, N> a = makeVec3(1.0, 2.0, 3.0);
	const CVecteur<double, N> b = makeVec3(4.0, -1.0, 0.5);

	const CVecteur<double, N> sum = a + b;

	EXPECT_NEAR(sum[0], 5.0, 1e-12);
	EXPECT_NEAR(sum[1], 1.0, 1e-12);
	EXPECT_NEAR(sum[2], 3.5, 1e-12);
}

TEST(CVecteurTest, SubtractionElementWise) {
	const CVecteur<double, N> a = makeVec3(5.0, 2.0, -1.0);
	const CVecteur<double, N> b = makeVec3(1.0, -3.0, 2.0);

	const CVecteur<double, N> diff = a - b;

	EXPECT_NEAR(diff[0], 4.0, 1e-12);
	EXPECT_NEAR(diff[1], 5.0, 1e-12);
	EXPECT_NEAR(diff[2], -3.0, 1e-12);
}

TEST(CVecteurTest, ScalarMultiplication) {
	const CVecteur<double, N> v = makeVec3(1.0, -2.0, 0.5);

	const CVecteur<double, N> scaled = v * 3.0;

	EXPECT_NEAR(scaled[0], 3.0, 1e-12);
	EXPECT_NEAR(scaled[1], -6.0, 1e-12);
	EXPECT_NEAR(scaled[2], 1.5, 1e-12);
}

TEST(CVecteurTest, DotAndNormOnCanonicalVectors) {
	const CVecteur<double, N> u = makeVec3(1.0, 0.0, 0.0);
	const CVecteur<double, N> v = makeVec3(0.0, 1.0, 0.0);

	EXPECT_NEAR(u.dot(v), 0.0, 1e-12);
	EXPECT_NEAR(u.norm(), 1.0, 1e-12);
	EXPECT_NEAR(v.norm(), 1.0, 1e-12);
}

TEST(CVecteurTest, DotGeneralCase) {
	const CVecteur<double, N> a = makeVec3(1.0, 2.0, 3.0);
	const CVecteur<double, N> b = makeVec3(4.0, -5.0, 6.0);

	EXPECT_NEAR(a.dot(b), 12.0, 1e-12);  // 1*4 + 2*(-5) + 3*6 = 12
}

TEST(CVecteurTest, ToEigenConversion) {
	const CVecteur<double, N> v = makeVec3(1.0, -2.0, 3.5);
	const Eigen::Matrix<double, N, 1> e = v.toEigen();

	EXPECT_NEAR(e(0), 1.0, 1e-12);
	EXPECT_NEAR(e(1), -2.0, 1e-12);
	EXPECT_NEAR(e(2), 3.5, 1e-12);
}

void test_cvecteur() 
{
    int argc = 1;
    char arg0[] = "run";
    char* argv[] = {arg0, nullptr};
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::GTEST_FLAG(filter) = "CVecteurTest.*";
    std::ignore = RUN_ALL_TESTS();
}