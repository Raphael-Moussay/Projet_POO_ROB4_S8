#include "../inc/cjoint.h"
#include "../inc/cjointprismatic.h"
#include "../inc/cjointrevolute.h"
#include "../inc/cbras.h" 
#include "../inc/colors.h"  


void exo4()
{
    colors(F_YELLOW);
    printf("====================================================\n");
    printf("Création du bras 4-DDL...\n");
    printf("====================================================\n");
    colors(RESET);
    // CJointRevolute Epaule(-M_PI, M_PI, 0.0, 0.3);
    // CJointRevolute Coude(-M_PI/2, M_PI/2, 0.0, 0.25);
    // CJointPrismatic Ext(0.0, 0.2);
    // CJointRevolute Poignet(-M_PI, M_PI, 0.0, 0.05);
    CBras bras;
    // bras.addJoint(std::make_unique<CJointRevolute>(Epaule));
    // bras.addJoint(std::make_unique<CJointRevolute>(Coude));
    // bras.addJoint(std::make_unique<CJointPrismatic>(Ext));
    // bras.addJoint(std::make_unique<CJointRevolute>(Poignet));
    bras.addJoint(std::make_unique<CJointRevolute>(-M_PI, M_PI, 0.0, 0.3));
    bras.addJoint(std::make_unique<CJointRevolute>(-M_PI/2, M_PI/2, 0.0, 0.25));
    bras.addJoint(std::make_unique<CJointPrismatic>(0.0, 0.2, 0.0));
    bras.addJoint(std::make_unique<CJointRevolute>(-M_PI, M_PI, 0.0, 0.05));
    // affichage de la position de l'effecteur via T.block<3,1>(0,3).transpose()
    colors(F_PURPLE);
    std::cout << "Calcul de la matrice de transformation homogène..." << std::endl;
    colors(RESET);
    Eigen::Matrix4d T = bras.computeFK();
    std::cout << "Position de initiale de l'effecteur : " << T.block<3,1>(0,3).transpose() << std::endl;
    // Balayage de l'épaulde de -Pi/2 à Pi/2 par pas de Pi/8
    for(double q = -M_PI/2; q <= M_PI/2; q += M_PI/8){
        bras.setQ(Eigen::Vector4d(q, 0, 0, 0));
        // affichage de la position de l'effecteur via T.block<3,1>(0,3).transpose()
        colors(F_PURPLE);
        std::cout << "Calcul de la matrice de transformation homogène..." << std::endl;
        colors(RESET);
        Eigen::Matrix4d T = bras.computeFK();
        std::cout << "Position n°" << (q + M_PI/2) / (M_PI/8) + 1 << " de l'effecteur : " << T.block<3,1>(0,3).transpose() << std::endl;
    }
    colors(F_YELLOW);
    printf("====================================================\n");
    printf("Affichage de la configuration du bras...\n");
    printf("====================================================\n");
    colors(RESET);
    std:: cout << bras;

}