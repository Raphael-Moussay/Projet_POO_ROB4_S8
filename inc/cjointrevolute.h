#ifndef CJOINTERREVOLUTE_H
#define CJOINTERREVOLUTE_H

#include "cjoint.h"

#include <cmath>
#include <iostream>
#include <memory>
#include <string>

/**
 * @brief Classe représentant un joint de type revolute, dérivée de CJoint.
 * 
 * Cette classe ajoute un attribut dx_ pour représenter la distance le long de l'axe de rotation.
 * La méthode getTransform() calcule la matrice de transformation homogène en fonction de l'angle de rotation q_ et de la distance dx_.
 */
class CJointRevolute : public CJoint{
    private : 
        double *dx_;
    public:
        /**
         * @brief Constructeur de CJointRevolute
         * @param qMin : angle minimum du joint
         * @param qMax : angle maximum du joint
         * @param q : angle initial du joint
         * @param dx : distance le long de l'axe de rotation
         */
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

#endif // CJOINTERREVOLUTE_H