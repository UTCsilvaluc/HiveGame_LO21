#ifndef GAMEMASTER_H
#define GAMEMASTER_H

#include "Joueur.h"
#include <iostream>
#include <memory>
#include <limits>

class GameMaster {
private:
    Joueur *joueur1;
    Joueur *joueur2;

public:
    GameMaster() : joueur1(nullptr), joueur2(nullptr) {}
    void startGame() {
        std::cout << "\nDémarrage du jeu HiveGame en cours...\n" << std::endl;
        int choice;
        // Choix du mode de jeu
        do {
            std::cout << "Merci de sélectionner le mode de jeu :\n"
                      << "1 - Joueur vs Joueur (JvJ)\n"
                      << "2 - Joueur vs IA (JvIA)\n";
            std::cin >> choice;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                choice = 0;  // Réinitialiser pour forcer un nouveau choix
                std::cout << "Merci de saisir 1 ou 2.\n";
            }

        } while (choice != 1 && choice != 2);

        std::cout << "Vous avez sélectionné le mode : " << (choice == 1 ? "JvJ" : "JvIA") << "\n";
        if (choice == 1) {
            std::string nom;
            std::cout << "\nMerci de saisir le nom du premier Joueur" << std::endl;
            std::cin >> nom;

            joueur1 = new Joueur(nom);  // Créer le joueur 1
            std::cout << "Joueur 1 créé : " << joueur1->getName() << std::endl;

            std::cout << "\nMerci de saisir le nom du second Joueur" << std::endl;
            std::cin >> nom;

            joueur2 = new Joueur(nom);  // Créer le joueur 2
            std::cout << "Joueur 2 créé : " << joueur2->getName() << std::endl;

            std::cout << "\nHiveGame : Le joueur 1 sera " << joueur1->getName()
                      << " et le joueur 2 sera " << joueur2->getName() << ".\n";
        } else {
            std::string nom;
            std::cout << "\nMerci de saisir le nom du Joueur" << std::endl;
            std::cin >> nom;

            joueur1 = new Joueur(nom);  // Créer le joueur
            std::cout << "Joueur créé : " << joueur1->getName() << std::endl;
        }
    }
    // Destructeur pour libérer la mémoire
    ~GameMaster() {
        delete joueur1;
        delete joueur2; //Attention que le joueur soit défini si IA
    }
};

#endif // GAMEMASTER_H
