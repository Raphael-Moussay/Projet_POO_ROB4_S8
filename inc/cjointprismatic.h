#pragma once
#include "cjoint.h"

class CJointPrismatic : public CJoint{
    public:
        CJointPrismatic(double qMin=-M_PI, double qMax=M_PI, double q=0):CJoint(qMin, qMax, q){};
        
        /**
         * @brief Calcule la matrice de transformation homogène associée à la configuration prismatique.
         */
        virtual Mat4 getTransform() const override{
            std::cout << "Prismatic transform from derivate class" << std::endl;
            Mat4 transform = Mat4::Identity();
            transform(2,3) = *q_;
            return transform;
        }
        virtual std::string getTypeName() const { return "Prismatic"; };
        virtual std::unique_ptr<CJoint> clone() const { return std::make_unique<CJointPrismatic>(*this); };
};

