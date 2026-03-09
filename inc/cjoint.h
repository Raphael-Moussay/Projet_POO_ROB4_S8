#pragma once
#include <string>
#include <iostream>
#include <memory>
#include <eigen3/Eigen/Dense>

using namespace Eigen;
using Mat4 = Matrix4d;



class CJoint{
    protected:
        double *q_,*qMin_,*qMax_;
    public:
        //Constructeur
        CJoint(double qMin=-M_PI, double qMax=M_PI,double q=0): q_(new double(q)), qMin_(new double(qMin)), qMax_(new double(qMax)) {
            if(*qMin_ > *qMax_){
                //Lève un flag d'erreur = stop le programme, q_, qMin_ et qMax_ ne sont pas initialisés
                throw std::invalid_argument("qMin must be less than or equal to qMax");
            }else if(*q_ < *qMin_ || *q_ > *qMax_){ 
                throw std::out_of_range("Joint angle out of bounds");
            }
        };

        //Destructeur
        virtual ~CJoint(){
            delete q_;
            delete qMin_;
            delete qMax_;
        };

        //Constructeur de copie
        CJoint(const CJoint& other){
            q_ = new double(*other.q_);
            qMin_ = new double(*other.qMin_);
            qMax_ = new double(*other.qMax_);
        };

        //Setters
        void setQ(double q)
        {
            if(q < *qMin_ || q > *qMax_){
                throw std::out_of_range("Joint angle out of bounds");
            }
            *q_ = q;
        };
        void setQMin(double qMin){qMin_ = new double(qMin);};
        void setQMax(double qMax){qMax_ = new double(qMax);};

        //Getters
        const double& getQ() const {return *q_;};
        const double& getQMin() const {return *qMin_;};
        const double& getQMax() const {return *qMax_;};

        virtual Mat4 getTransform() const = 0;
        virtual std::string getTypeName() const = 0;
        virtual std::unique_ptr<CJoint> clone() const = 0;
};
