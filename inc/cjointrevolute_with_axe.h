#ifndef CJOINTREVOLUTE_WITH_AXE_H
#define CJOINTREVOLUTE_WITH_AXE_H

#include "cjoint.h"

#include <cmath>
#include <eigen3/Eigen/Geometry>
#include <memory>
#include <stdexcept>
#include <string>

/**
 * @brief Joint revolute avec axe de rotation explicite.
 *
 * Cette classe généralise CJointRevolute en permettant de choisir
 * un axe de rotation quelconque (x, y, z).
 */
class CJointRevoluteWithAxe : public CJoint {
	private:
		double *dx_;
		Eigen::Vector3d axis_;
		Eigen::Vector3d origin_xyz_;
		Eigen::Vector3d origin_rpy_;

	public:
		/**
		 * @brief Constructeur du joint revolute avec axe.
		 * @param qMin borne minimale de q
		 * @param qMax borne maximale de q
		 * @param q angle initial
		 * @param dx translation le long de x (repere local)
		 * @param axis axe de rotation
		 */
		CJointRevoluteWithAxe(double qMin = -M_PI,
							  double qMax = M_PI,
							  double q = 0.0,
							  double dx = 0.0,
							  const Eigen::Vector3d& axis = Eigen::Vector3d::UnitZ())
			: CJoint(qMin, qMax, q),
			  dx_(new double(dx)),
			  axis_(axis),
			  origin_xyz_(Eigen::Vector3d(dx, 0.0, 0.0)),
			  origin_rpy_(Eigen::Vector3d::Zero()) {
			if (axis_.norm() < 1e-12) {
				throw std::invalid_argument("Joint axis must be non-zero");
			}
			axis_.normalize();
		}

		/**
		 * @brief Constructeur avec origine URDF complete.
		 */
		CJointRevoluteWithAxe(double qMin,
							  double qMax,
							  double q,
							  const Eigen::Vector3d& axis,
							  const Eigen::Vector3d& origin_xyz,
							  const Eigen::Vector3d& origin_rpy)
			: CJoint(qMin, qMax, q),
			  dx_(new double(origin_xyz.x())),
			  axis_(axis),
			  origin_xyz_(origin_xyz),
			  origin_rpy_(origin_rpy) {
			if (axis_.norm() < 1e-12) {
				throw std::invalid_argument("Joint axis must be non-zero");
			}
			axis_.normalize();
		}

		CJointRevoluteWithAxe(const CJointRevoluteWithAxe& other)
			: CJoint(other),
			  dx_(new double(*other.dx_)),
			  axis_(other.axis_),
			  origin_xyz_(other.origin_xyz_),
			  origin_rpy_(other.origin_rpy_) {}

		virtual ~CJointRevoluteWithAxe() {
			delete dx_;
		}

		const double& getDx() const { return *dx_; }
		void setDx(double dx) {
			*dx_ = dx;
			origin_xyz_.x() = dx;
		}

		const Eigen::Vector3d& getAxis() const { return axis_; }
		void setAxis(const Eigen::Vector3d& axis) {
			if (axis.norm() < 1e-12) {
				throw std::invalid_argument("Joint axis must be non-zero");
			}
			axis_ = axis.normalized();
		}

		const Eigen::Vector3d& getOriginXyz() const { return origin_xyz_; }
		const Eigen::Vector3d& getOriginRpy() const { return origin_rpy_; }
		void setOriginXyz(const Eigen::Vector3d& origin_xyz) {
			origin_xyz_ = origin_xyz;
			*dx_ = origin_xyz.x();
		}
		void setOriginRpy(const Eigen::Vector3d& origin_rpy) { origin_rpy_ = origin_rpy; }

		/**
		 * @brief Retourne la transformation homogene du joint.
		 *
		 * Forme retenue (style URDF): T(origin_xyz, origin_rpy) * R(axis, q).
		 */
		virtual Eigen::Matrix4d getTransform() const override {
			Eigen::Matrix4d transform = Eigen::Matrix4d::Identity();
			const Eigen::Matrix3d R_origin =
				(Eigen::AngleAxisd(origin_rpy_(2), Eigen::Vector3d::UnitZ()) *
				 Eigen::AngleAxisd(origin_rpy_(1), Eigen::Vector3d::UnitY()) *
				 Eigen::AngleAxisd(origin_rpy_(0), Eigen::Vector3d::UnitX()))
					.toRotationMatrix();
			const Eigen::Matrix3d R_joint = Eigen::AngleAxisd(*q_, axis_).toRotationMatrix();

			transform.block<3, 3>(0, 0) = R_origin * R_joint;
			transform.block<3, 1>(0, 3) = origin_xyz_;
			return transform;
		}

		virtual std::string getTypeName() const override { return "RevoluteWithAxe"; }
		virtual std::unique_ptr<CJoint> clone() const override {
			return std::make_unique<CJointRevoluteWithAxe>(*this);
		}
};

#endif // CJOINTREVOLUTE_WITH_AXE_H
