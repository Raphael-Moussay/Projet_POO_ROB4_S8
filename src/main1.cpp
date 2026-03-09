#include "../inc/inc.h"


int main() {
    //Demande a lutilisateur de choisir un exercice (choix entre 1 et 4) pui lance les exo correspondant
    char choix;
    do {
        colors(F_CYAN);
        std::cout << "Choisissez un exercice (1-4) ou q pour quitter: ";
        colors(RESET);
        std::cin >> choix;
        switch (choix) {
            case '1':
                exo1();
                break;
            case '2':
                //exo2();
                break;
            case '3':
                //exo3();
                break;
            case '4':
                //exo4();
                break;
            case 'q':
                colors(F_GREEN);
                std::cout << "Au revoir!" << std::endl;
                colors(RESET);
                break;
            default:
                colors(F_RED);
                std::cout << "Choix invalide, essayez à nouveau." << std::endl;
                colors(RESET);
        }
    } while (choix != 'q');
    return 0;
}

