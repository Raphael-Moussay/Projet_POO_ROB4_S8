#include "../inc/cbras.h"
#include "../inc/cjointprismatic.h"
#include "../inc/cjointrevolute.h"
#include "../inc/colors.h"
#include "../inc/test_bras.h"
#include "../inc/test_joints.h"
#include "../inc/test_cvecteur.h"

#include <cmath>
#include <iostream>
#include <memory>


int main() {
    //Demande a lutilisateur de choisir un exercice (choix entre 1 et 4) pui lance les exo correspondant
    char choix;
    do {
        colors(F_CYAN);
        std::cout << "Choisissez un exercice (1-4) ou q pour quitter: ";
        colors(RESET);
        std::cin >> choix;
        switch (choix) 
        {
            case '1':
            {
                // exo1();
                CBras bras;
                bras.addJoint(std::make_unique<CJointRevolute>(-M_PI, M_PI, 0.0, 0.5));
                bras.addJoint(std::make_unique<CJointRevolute>(-M_PI, M_PI, 0.3, 0.3));
                bras.addJoint(std::make_unique<CJointPrismatic>(0.0, 0.5, 0.1));
                std:: cout << bras;
                break; 
            }
            case '2':
            {
                exo2();
                break;
            }
            case '3':
            {
                do
                {                
                    colors(F_CYAN);
                    std::cout << "Choisissez une question (2 - 3) ou q pour quitter: ";
                    colors(RESET);
                    std::cin >> choix;
                    switch (choix) 
                    {
                        case '2':
                        {
                            exo3_2();
                            break;
                        }
                        case '3':
                        {
                            exo3_3();
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
                break;
            }
            case '4':
            {
                //exo4();
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

