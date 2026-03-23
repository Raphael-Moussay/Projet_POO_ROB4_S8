#pragma once

#include "cjoint.h"

#include <cmath>
#include <iostream>
#include <memory>
#include <string>


class CJointRevolute : public CJoint{
    private : 
        double *dx_;
    public:
        CJointRevolute( double qMin=-M_PI, double qMax=M_PI,double q=0, double dx=0): CJoint(qMin, qMax, q){
            dx_ = new double(dx);
        }
        virtual ~CJointRevolute(){
            delete dx_;
        }

        const double& getDx() const { return *dx_; };
        void setDx(double dx) { *dx_ = dx; };

       /**
         * @brief Calcule la matrice de transformation homogène associée à la configuration revolution.
         */
        virtual Eigen::Matrix4d getTransform() const override{
            std::cout << "Revolute transform from derivate class" << std::endl;
            Eigen::Matrix4d transform = Eigen::Matrix4d::Identity();
            double theta = *q_;
            double c = cos(theta);
            double s = sin(theta);
            transform(0,0) = c;
            transform(0,1) = -s;
            transform(1,0) = s;
            transform(1,1) = c;
            transform(0,3) = *dx_;
            return transform;
        }

        virtual std::string getTypeName() const { return "Revolute"; };
        virtual std::unique_ptr<CJoint> clone() const { return std::make_unique<CJointRevolute>(*this); };
};


