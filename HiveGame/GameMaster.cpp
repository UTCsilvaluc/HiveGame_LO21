#include "GameMaster.h"

GameMaster::~GameMaster() {
    delete joueur1;
    delete joueur2;
}

int getInput(const std::string& prompt, int minValue, int maxValue, unsigned int tour) {
    int choice;
    if (tour == 0){
        minValue = std::numeric_limits<int>::min();
        maxValue = std::numeric_limits<int>::max();
    }
    while (true) {
        std::cout << prompt;
        std::cin >> choice;

        if (std::cin.fail() || choice < minValue || choice > maxValue) {
            std::cin.clear(); // R�initialiser l'�tat d'erreur
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignorer les caract�res restants
            std::cout << "S'il vous pla�t, entrez un nombre valide entre " << minValue << " et " << maxValue << ".\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignorer les caract�res restants
            break; // Sortir de la boucle si l'entr�e est valide
        }
    }
    return choice;
}

int getInput(const std::string& prompt, int minValue, int maxValue) {
    int choice;
    while (true) {
        std::cout << prompt;
        std::cin >> choice;

        if (std::cin.fail() || choice < minValue || choice > maxValue) {
            std::cin.clear(); // R�initialiser l'�tat d'erreur
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignorer les caract�res restants
            std::cout << "S'il vous pla�t, entrez un nombre valide entre " << minValue << " et " << maxValue << ".\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignorer les caract�res restants
            break; // Sortir de la boucle si l'entr�e est valide
        }
    }
    return choice;
}

Insecte* GameMaster::selectionnerInsecte() {
    int x = getInput("Abscisse de la position du pion � d�placer : ", plateau.getMinQ(), plateau.getMaxQ());
    int y = getInput("Ordonn�e de la position du pion � d�placer : ", plateau.getMinR(), plateau.getMaxR());

    Insecte* currentInsecte = plateau.getInsecteAtCoords(x, y);
    if (!currentInsecte) {
        std::cout << "Aucun pion � cette position. Veuillez r�essayer." << std::endl;
        return selectionnerInsecte(); // Appel r�cursif jusqu'� obtenir un pion valide
    }
    return currentInsecte;
}

bool positionEstValide(const Hexagon& position, const std::vector<Hexagon>& deplacementsPossibles) {
    return std::find(deplacementsPossibles.begin(), deplacementsPossibles.end(), position) != deplacementsPossibles.end();
}

void GameMaster::startGame() {
    std::cout << "\nD�marrage du jeu HiveGame en cours...\n" << std::endl;
    mode = getInput("Merci de s�lectionner le mode de jeu :\n1 - Joueur vs Joueur (JvJ)\n2 - Joueur vs IA (JvIA)\n", 1, 2);
    std::cout << "Vous avez s�lectionn� le mode : " << (mode == 1 ? "JvJ" : "JvIA") << "\n";

    std::string nom;
    std::cout << "\nMerci de saisir le nom du Joueur" << std::endl;
    std::cin >> nom;

    joueur1 = new Joueur(nom);  // Cr�er le joueur 1

    if (mode == 1) {
        std::cout << "\nMerci de saisir le nom du second Joueur" << std::endl;
        std::cin >> nom;
        joueur2 = new Joueur(nom);  // Cr�er le joueur 2
    } else {
        joueur2 = new Joueur("IA");
    }

    std::cout << "Joueur 1 cr�� : " << joueur1->getName() << std::endl;
    std::cout << "Joueur 2 cr�� : " << joueur2->getName() << std::endl;

    jouer();
}

void GameMaster::jouer() {
    bool hasWinner = false;
    while (!hasWinner) {
        Joueur* current = (plateau.getTour() % 2 == 0) ? joueur1 : joueur2;
        hasWinner = detectWinner(current);
        std::cout << "\nC'est au tour de : " << current->getName() << std::endl;

        if (current->hasQueen()) {
            std::cout << "Il vous reste " << 4 - plateau.getTour() << " pour jouer votre reine." << std::endl;
        }
        int choice = 0;
        bool needPlayQueen = (4 - plateau.getTour() == 0) && current->hasQueen();

        if (needPlayQueen) {
            std::cout << "Vous devez obligatoirement poser votre Reine !\n";
            choice = 2; // Forcer le choix de poser la reine
        } else {
            if (!(plateau.playerCanMoveInsecte(current))){
                choice = 2;
            } else {
                choice = getInputForAction(current);
            }

        }

        // Ex�cuter l'action choisie
        if (choice == 1) {  // D�placer un pion
            deplacerPion(current);
        } else if (choice == 2) {  // Placer un nouveau pion
            placerPion(current, needPlayQueen);
        }

        // Incr�menter le compteur de tours
        plateau.incrementerTour();
    }
}

int GameMaster::getInputForAction(Joueur* current) {
    int choice = 0;
    while (true) {
        std::cout << "Que voulez-vous faire ?\n"
                  << "1 - D�placer un pion \n"
                  << (current->getDeckSize() > 0 ? "2 - Placer un pion \n" : "");
        std::cin >> choice;

        if (std::cin.fail() || (choice != 1 && (choice != 2 || current->getDeckSize() == 0))) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Merci de saisir 1 ou 2 (si deck disponible).\n";
        } else {
            break; // Sortir de la boucle si l'entr�e est valide
        }
    }
    return choice;
}

void GameMaster::deplacerPion(Joueur* current) {
    plateau.afficherPlateau(joueur1 , joueur2);
    Insecte* currentInsecte = selectionnerInsecte();
    plateau.afficherPossibiliteDeplacement(currentInsecte, plateau.getPlateauMap(), joueur1, joueur2);
    bool deplacementValide = false;
    Hexagon nouvellePosition;

    while (!deplacementValide) {
        int x = getInput("Abscisse pour poser le pion : ", plateau.getMinQ() - 1 , plateau.getMaxQ() + 1);
        int y = getInput("Ordonn�e pour poser le pion : ", plateau.getMinR() - 1, plateau.getMaxR() + 1);
        nouvellePosition = Hexagon(x, y);
        std::vector<Hexagon> deplacementsPossibles = currentInsecte->deplacementsPossibles(plateau.getPlateauMap());
        if (positionEstValide(nouvellePosition, deplacementsPossibles)) {
            deplacementValide = true;
        } else {
            std::cout << "D�placement invalide. Veuillez choisir une coordonn�e valide." << std::endl;
        }
    }
    plateau.deplacerInsecte(currentInsecte, nouvellePosition);
}

void GameMaster::placerPion(Joueur* current, bool needPlayQueen) {
    Insecte* insecteAPlacer = nullptr;
    int index = 0;

    if (!needPlayQueen) {
        std::cout << "\nVoici votre deck : " << std::endl;
        current->afficherDeck();
        index = getInput("Quel pion souhaitez-vous poser ? ", 1, current->getDeckSize()) - 1;
        insecteAPlacer = current->getInsecteByIndex(index);
    } else {
        insecteAPlacer = current->getQueen();
        index = current->getQueenIndex();
    }
    if (!(plateau.plateauEstVide())){
        plateau.afficherPlateau(joueur1 , joueur2);
    }

    plateau.afficherPossibilitePlacement(insecteAPlacer, joueur1, joueur2);
    int x = 0;
    int y =0;
    if (plateau.getTour() != 0){
        x = getInput("Abscisse pour poser le pion : ", plateau.getMinQ() - 1 , plateau.getMaxQ() + 1);
        y = getInput("Ordonn�e pour poser le pion : ", plateau.getMinR() - 1, plateau.getMaxR() + 1);
    }
    plateau.ajouterInsecte(insecteAPlacer, Hexagon(x,y));
    current->retirerInsecte(index); // Retirer le pion du deck apr�s l'avoir pos�
}
bool GameMaster::detectWinner(Joueur *current) {
    Insecte* reine = plateau.getReineAbeille(current);
    if (reine == nullptr) {
        return false;
    }
    if (plateau.estEntouree(reine)) {
        std::cout << "Le joueur " << current->getName() << " a perdu ! " << std::endl;
        return true;
    }
    return false;
}

