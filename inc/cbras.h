#pragma once
#include "../inc/inc.h"

class CBras{
    private:
        std::vector<std::unique_ptr<CJoint>> tab_joints_;
    public:
        CBras(){};
        
        void addJoint(std::unique_ptr<CJoint> joint){
            tab_joints_.push_back(std::move(joint));
        }


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
                    os << "Revolute q = " << bras.getJoint(i).getQ() << " rad   " ;
                }else{
                    os << "Prismatic  q = "<<bras.getJoint(i).getQ() << " m     " ;
                }
                os << "bornes=["<<bras.getJoint(i).getQMin()<<", "<<bras.getJoint(i).getQMax()<<"]"<<std::endl;
            }
            return os;
        }
};