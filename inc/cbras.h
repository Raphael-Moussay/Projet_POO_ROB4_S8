#ifndef CBRAS_H
#define CBRAS_H

#include "cjoint.h"

#include <cstdlib>
#include <iomanip>
#include <memory>
#include <ostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include <eigen3/Eigen/Dense>

/**
 * @brief Classe représentant un bras robotique composé de plusieurs joints.
 * 
 * Cette classe gère une collection de joints (CJoint) et permet de calculer la cinématique directe du bras, d'afficher les informations sur les joints, et de manipuler les configurations des joints.
 */
class CBras{
    private:
        std::vector<std::unique_ptr<CJoint>> tab_joints_;
    public:
        CBras(){};
        ~CBras() = default;
        CBras(CBras&& other) = default;
        CBras& operator=(CBras&& other) = default;

        
        void addJoint(std::unique_ptr<CJoint> joint){
            tab_joints_.push_back(std::move(joint));
        }

        /**
         * @brief Calcule la matrice de transformation homogène du bras en fonction des configurations des joints.
         * @return La matrice de transformation homogène.
         * La transformation est calculée en multipliant les transformations de chaque joint dans l'ordre.
         */
        Eigen::Matrix4d computeFK()
        {
            Eigen::Matrix4d T = Eigen::Matrix4d::Identity();
            for (int i = 0; i < static_cast<int>(tab_joints_.size()); i++)
                T = tab_joints_[i]->getTransform() * T;
            return T;            
        }
        
        /**
         * Nombre de joints dans le bras
         */
        int getNbJoints(){
            return tab_joints_.size();
        }
        
        /**
         * Get the joints i 
         */
        const CJoint& getJoint(size_t i){
            if(i >= tab_joints_.size()){
                throw std::out_of_range("Joint index out of range");
            }
            return *tab_joints_[i];
            //return *tab_joints_.at(i);
        }
        
        /**
         * Surcharge de l'opérateur << pour afficher 
         */
        friend std::ostream& operator<<(std::ostream& os, CBras& bras){
            int nbJoints = bras.getNbJoints();
            os << "Bras [" << nbJoints << " DDL]" << std::endl;
            for(size_t i =0; i<(size_t)nbJoints; i++){
                os << "    [" << i << "] " ;
                std::string type_i = bras.getJoint(i).getTypeName();
                if(!type_i.compare("Revolute")){
                    os << std::fixed << std::setprecision(3) << "Revolute  q = " << bras.getJoint(i).getQ() << " rad   " ;
                }else{
                    os << std::fixed << std::setprecision(3) << "Prismatic q = "<<bras.getJoint(i).getQ()   << " m     " ;
                }
                os << std::fixed << std::setprecision(3) << "bornes=["<<bras.getJoint(i).getQMin()<<", "<<bras.getJoint(i).getQMax()<<"]"<<std::endl;
            }
            return os;
        }

        /**
         * Constructeur de copie
         */
        CBras(const CBras& other){
            for(size_t i = 0; i < other.tab_joints_.size(); i++){
                tab_joints_.push_back(other.tab_joints_[i]->clone());
            }
        }

        /**
         * Fonction swap utile pour l'implémentation de l'opérateur= par copy-and-swap
         */
        friend void swap(CBras& first, CBras& second)
        {
            std::swap(first.tab_joints_, second.tab_joints_);
        }

        /**
         * Surcharge opérateur = par copy-and-swap
         */
        CBras& operator=(CBras other)
        {
            CBras temp(other);
            swap(*this, temp);
            return *this;
        }
        
        /**
         * Retourne un vecteur de taille N avec les q_ de chaque joint
         */
        Eigen::VectorXd getQ() const {
            Eigen::VectorXd q(tab_joints_.size());
            for(size_t i = 0; i < tab_joints_.size(); i++)
            {
                q(i) = tab_joints_[i]->getQ();
            }
            return q;
        }

        /**
         * Applique q[i] à chaque joint via setQ()
         * Leve std::invalid_argument si q.size != getNbJoints
         */
        void setQ(const Eigen::VectorXd& q){
            if(q.size() != getNbJoints()) throw std::invalid_argument("q size doesn't match with number of joints");
            for(size_t i=0; i < tab_joints_.size(); i++)
            {
                tab_joints_[i]->setQ(q(i));
            }
        }

        /**
         * Tire q[i] uniformément dans [qMin_, qMax_] pour chaque joint
         */
        Eigen::VectorXd randomQ() const{
            Eigen::VectorXd q_tab(tab_joints_.size());
            for(size_t i=0; i < tab_joints_.size(); i++)
            {
                double min =  tab_joints_[i]->getQMin();
                double max =  tab_joints_[i]->getQMax();
                double q = min * ((double) rand() / (double) RAND_MAX) - max;
                tab_joints_[i]->setQ(q);
                q_tab(i) = q;
            }
            return q_tab;
        }
};


#endif // CBRAS_H