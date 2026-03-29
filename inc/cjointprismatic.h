#ifndef CJOINTPRISMATIC_H
#define CJOINTPRISMATIC_H

#include "cjoint.h"

#include <cmath>
#include <iostream>
#include <memory>
#include <string>

/**
 * @brief Classe représentant un joint de type prismatique, dérivée de CJoint.
 * 
 * Cette classe ne nécessite pas d'attributs supplémentaires, car la transformation est simplement une translation le long de l'axe z en fonction de q_.
 * La méthode getTransform() calcule la matrice de transformation homogène en fonction de la distance q_.
 */
class CJointPrismatic : public CJoint{
    public:
        CJointPrismatic(double qMin=-M_PI, double qMax=M_PI, double q=0):CJoint(qMin, qMax, q){};
        
        /**
         * @brief Calcule la matrice de transformation homogène associée à la configuration prismatique.
         */
        virtual Eigen::Matrix4d getTransform() const override{
            std::cout << "Prismatic transform from derivate class" << std::endl;
            Eigen::Matrix4d transform = Eigen::Matrix4d::Identity();
            transform(2,3) = *q_;
            return transform;
        }
        virtual std::string getTypeName() const { return "Prismatic"; };
        virtual std::unique_ptr<CJoint> clone() const { return std::make_unique<CJointPrismatic>(*this); };
};

#endif // CJOINTPRISMATIC_H