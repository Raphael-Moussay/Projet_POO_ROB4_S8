#include "../inc/cbras.h"
#include "../inc/cjointprismatic.h"
#include "../inc/cjointrevolute.h"
#include "../inc/colors.h"
#include "../inc/test_bras.h"
#include "../inc/test_joints.h"
#include "../inc/test_cvecteur.h"
#include "../inc/exo4.h"

#include <cmath>
#include <iostream>
#include <memory>


int main() {
    //Demande a lutilisateur de choisir un exercice (choix entre 1 et 4) pui lance les exo correspondant
    char choix;
    do {
        colors(F_CYAN);
        std::cout << "Choisissez ce que vous souhaitez faire :\n\t0 - Exécuter tous les tests\n\t1 - Tests joints\n\t2 - Tests bras\n\t3 - Tests cvecteur\n\t4 - Exo 4\n\tq - Quitter" << std::endl;
        colors(RESET);
        std::cin >> choix;
        switch (choix) 
        {
            case '0':
            {
                test_joints();
                test_bras();
                test_cvecteur();
                break;
            }
            case '1':
            {
                test_joints();
                // CBras bras;
                // bras.addJoint(std::make_unique<CJointRevolute>(-M_PI, M_PI, 0.0, 0.5));
                // bras.addJoint(std::make_unique<CJointRevolute>(-M_PI, M_PI, 0.3, 0.3));
                // bras.addJoint(std::make_unique<CJointPrismatic>(0.0, 0.5, 0.1));
                // std:: cout << bras;
                break; 
            }
            case '2':
            {
                test_bras();
                break;
            }
            case '3':
            {
                test_cvecteur();
                break;
            }
            case '4':
            {
                exo4();
                break;
            }
            case 'q':
            {
                colors(F_GREEN);
                std::cout << "Au revoir!" << std::endl;
                colors(RESET);
                break;
            }
            default:
            {
                colors(F_RED);
                std::cout << "Choix invalide, essayez à nouveau." << std::endl;
                colors(RESET);
                break;
            }
        }
    } while (choix != 'q');
    return 0;
}

