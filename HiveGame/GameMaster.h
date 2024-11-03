#ifndef GAMEMASTER_H
#define GAMEMASTER_H

#include "Joueur.h"
#include "Plateau.h"
#include <iostream>
#include <memory>
#include <limits>
int getInput(const std::string& prompt, int minValue, int maxValue);
bool positionEstValide(const Hexagon& position, const std::vector<Hexagon>& deplacementsPossibles);
class GameMaster {
private:
    Plateau plateau;
    Joueur *joueur1;
    Joueur *joueur2;
    unsigned int mode;
    unsigned int tour;
public:
    bool hasPlayQueen(Joueur *currentPlayer);
    GameMaster() : joueur1(nullptr), joueur2(nullptr) , mode(0) {}
    Insecte* selectionnerInsecte();
    GameMaster(Plateau plateau) : joueur1(nullptr), joueur2(nullptr) , mode(0) , plateau(plateau){}
    void startGame() {
        std::cout << "\nDémarrage du jeu HiveGame en cours...\n" << std::endl;
        mode = getInput("Merci de sélectionner le mode de jeu :\n1 - Joueur vs Joueur (JvJ)\n2 - Joueur vs IA (JvIA)\n", 1, 2);
        std::cout << "Vous avez sélectionné le mode : " << (mode == 1 ? "JvJ" : "JvIA") << "\n";
        if (mode == 1) {
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
            joueur2 = new Joueur("IA");
            std::cout << "Joueur cree : " << joueur1->getName() << std::endl;
        }

        jouer();

        /* Générer le plateau */
    }

    void choixExtensions(){}//Objet publique extension qui contient une liste d'extension et propose de les choisir
    void jouer() {
        while (true) {
            Joueur *current = (tour % 2 == 0) ? joueur1 : joueur2;
            std::cout << "\nC'est au tour de : " << current->getName() << std::endl;
            if (!(hasPlayQueen(current))){
                std::cout << "Il vous reste " << 4 - tour << " pour jouer votre reine." <<std::endl;
            }

            // Choix d'action : déplacer un pion ou en placer un
            int choice = 0;
            do {
                std::cout << "Que voulez-vous faire ?\n"
                          << "1 - Déplacer un pion \n";
                if (current->getDeckSize() > 0) {
                    std::cout << "2 - Placer un pion \n";
                }
                std::cin >> choice;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    choice = 0;
                    std::cout << "Merci de saisir 1 ou 2 (si deck disponible).\n";
                }
            } while (choice != 1 && (choice != 2 || current->getDeckSize() == 0));

            // Exécuter l'action choisie
            if (choice == 1) {  // Déplacer un pion
                plateau.afficherPlateau();
                int x = getInput("Abscisse de la position du pion à déplacer : ", plateau.getMinQ(), plateau.getMaxQ());
                int y = getInput("Ordonnée de la position du pion à déplacer : ", plateau.getMinR(), plateau.getMaxR());
                Insecte *currentInsecte = selectionnerInsecte();
                bool deplacementValide = false;
                Hexagon nouvellePosition;
                while (!(deplacementValide)){
                    int newX = getInput("Nouvelle abscisse : ", plateau.getMinQ() - 1, plateau.getMaxQ() + 1);
                    int newY = getInput("Nouvelle ordonnée : ", plateau.getMinR() - 1, plateau.getMaxR() + 1);
                    nouvellePosition = Hexagon(newX, newY);
                    std::vector<Hexagon> deplacementsPossibles = currentInsecte->deplacementsPossibles(plateau.getPlateauMap());
                    // Appeler les extensions pour filtrer deplacementsPossibles
                    if (positionEstValide(nouvellePosition, deplacementsPossibles)){
                        deplacementValide = true;
                    } else {
                        std::cout << "Déplacement invalide. Veuillez choisir une coordonnée valide." << std::endl;
                    }

                }
                plateau.deplacerInsecte(currentInsecte, nouvellePosition);

            } else if (choice == 2) {  // Placer un nouveau pion
                std::cout << "\nVoici votre deck : " << std::endl;
                current->afficherDeck();
                int index = getInput("Quel pion souhaitez-vous poser (index dans le deck) ? ", 1, current->getDeckSize()) - 1;

                Insecte *insecteAPlacer = current->getInsecteByIndex(index);
                if (!insecteAPlacer) {
                    std::cout << "Index de pion invalide. Veuillez réessayer." << std::endl;
                    continue;
                }
                plateau.afficherPlateau();
                int x = getInput("Abscisse pour poser le pion : ", plateau.getMinQ() - 1, plateau.getMaxQ() + 1);
                int y = getInput("Ordonnée pour poser le pion : ", plateau.getMinR() - 1, plateau.getMaxR() + 1);
                plateau.ajouterInsecte(insecteAPlacer);
                current->retirerInsecte(index);  // Retirer le pion du deck après l'avoir posé
            }

            // Incrémenter le compteur de tours et passer au prochain joueur
            tour++;
        }
    }

    // Destructeur pour libérer la mémoire
    ~GameMaster() {
        if (joueur1) delete joueur1;
        if (joueur2) delete joueur2;
    }
};



#endif // GAMEMASTER_H
