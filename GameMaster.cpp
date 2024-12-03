#include "GameMaster.h"
void GameMaster::startGame() {
    std::cout << "\nD�marrage du jeu HiveGame en cours...\n" << std::endl;
    choixExtensions();
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
        joueur2 = new JoueurIA("IA");
    }

    std::cout << "Joueur 1 cr�� : " << joueur1->getName() << std::endl;
    std::cout << "Joueur 2 cr�� : " << joueur2->getName() << std::endl;
    jouer();
}
GameMaster::~GameMaster() {
    delete joueur1;
    delete joueur2;

    // Lib�rer la m�moire de la pile d'actions
    while (!actionsPile.empty()) {
        delete actionsPile.top();
        actionsPile.pop();
    }
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

int GameMaster::getInputForAction(Joueur* current) {
    int choice = 0;
    while (true) {
        std::cout << "Que voulez-vous faire ?\n"
                  << "1 - D�placer un pion \n"
                  << (current->getDeckSize() > 0 ? "2 - Placer un pion \n" : "")
                  << "3 - Retour arri�re (Annuler la derni�re action)\n";
        std::cin >> choice;

        if (std::cin.fail() || (choice != 1 && (choice != 2 || current->getDeckSize() == 0)) && choice != 3) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Merci de saisir 1, 2 (si deck disponible), ou 3 pour retourner en arri�re.\n";
        } else {
            break; // Sortir de la boucle si l'entr�e est valide
        }
    }
    return choice;
}
bool positionEstValide(const Hexagon& position, const std::vector<Hexagon>& deplacementsPossibles) {
    return std::find(deplacementsPossibles.begin(), deplacementsPossibles.end(), position) != deplacementsPossibles.end();
}

void GameMaster::deplacerPion(Joueur* current) {
    plateau.afficherPlateau(joueur1, joueur2);

    Insecte* currentInsecte = selectionnerInsecte(current);

    bool deplacementValide = false;
    Hexagon nouvellePosition;

    int x=0;
    int y=0;

    while (!deplacementValide) {
        std::vector<Hexagon> deplacementsPossibles = currentInsecte->deplacementsPossibles(plateau.getPlateauMap());
        plateau.afficherPossibiliteDeplacement(currentInsecte, plateau.getPlateauMap(), joueur1, joueur2, current);
        if (dynamic_cast<JoueurIA*>(current)){
            Hexagon position = current->randomHexagonChoice(deplacementsPossibles);
            x = position.getQ();
            y = position.getR();
        }
        else{
            x = getInput("Abscisse pour poser le pion : ", plateau.getMinQ() - 1 , plateau.getMaxQ() + 1);
            y = getInput("Ordonn�e pour poser le pion : ", plateau.getMinR() - 1, plateau.getMaxR() + 1);
        }

        nouvellePosition = Hexagon(x, y);


        if (positionEstValide(nouvellePosition, deplacementsPossibles)) {
            deplacementValide = true;
        } else {
            std::cout << "D�placement invalide. Veuillez choisir une coordonn�e valide." << std::endl;
        }
    }

    // Ajouter l'action � la pile apr�s le d�placement
    actionsPile.push(new DeplacementAction(currentInsecte, currentInsecte->getCoords(), nouvellePosition));

    // Si la pile d�passe la taille max, supprimer l'action la plus ancienne
    if (actionsPile.size() > maxRetourArriere) {
        delete actionsPile.top();
        actionsPile.pop();
    }

    plateau.deplacerInsecte(currentInsecte, nouvellePosition);
}

void GameMaster::jouer() {
    bool hasWinner = false;
    while (!hasWinner) {
        Joueur* current = (tour % 2 == 0) ? joueur1 : joueur2;
        int playerTurn = (tour / 2) + 1; // Tour sp�cifique au joueur
        hasWinner = detectWinner(joueur1, joueur2);

        std::cout << "\nC'est au tour de : " << current->getName() << std::endl;

        if (current->hasQueen()) {
            int remainingTurnsToPlayQueen = 4 - playerTurn;
            std::cout << "Il vous reste " << remainingTurnsToPlayQueen
                      << " tours pour jouer votre reine." << std::endl;
        }

        int choice = 0;
        bool needPlayQueen = (playerTurn >= 4) && current->hasQueen();

        if (needPlayQueen) {
            std::cout << "Vous devez obligatoirement poser votre Reine !\n";
            choice = 2; // Forcer le choix de poser la reine
        } else {
            if (!plateau.playerCanMoveInsecte(current) || !verifierDeplacementsPossiblesPourTousLesInsectes(current)) {
                std::cout << "Aucun mouvement possible, vous devez placer un pion.\n";
                choice = 2;
            } else {
                if (dynamic_cast<JoueurIA*>(current)){
                    choice = current->randomChoice();
                }
                else{
                    choice = getInputForAction(current);
                }
            }
        }
        while (true) {
            if (choice == 3) {
                if (actionsPile.size() >= 2) {
                    undoLastAction();
                    break;
                } else {
                    std::cout << "Aucune action � annuler, essayez une autre option.\n";
                    choice = getInputForAction(current);
                    continue;
                }
            } else if (choice == 1) {
                deplacerPion(current);
                plateau.afficherPlateau(joueur1, joueur2);
                break;
            } else if (choice == 2) {  // Placer un nouveau pion
                placerPion(current, needPlayQueen);
                plateau.afficherPlateau(joueur1, joueur2);
                break;
            } else {
                std::cout << "Choix invalide. Veuillez r�essayer.\n";
                choice = getInputForAction(current);
            }
        }
        tour++;
    }
}

void GameMaster::placerPion(Joueur* current, bool needPlayQueen) {
    Insecte* insecteAPlacer = nullptr;
    int index = 0;

    // S�lection du pion � placer
    if (!needPlayQueen) {
        std::cout << "\nVoici votre deck : " << std::endl;
        current->afficherDeck();
        if (dynamic_cast<JoueurIA*>(current)){
            index = current->randomDeckChoice();
        }
        else{
            index = getInput("Quel pion souhaitez-vous poser ? ", 1, current->getDeckSize()) - 1;
        }
        insecteAPlacer = current->getInsecteByIndex(index);
    } else {
        insecteAPlacer = current->getQueen();
        index = current->getQueenIndex();
    }

    if (!plateau.plateauEstVide()) {
        plateau.afficherPlateau(joueur1, joueur2);
    }

    Hexagon position;
    bool placementValide = false;

    int x=0;
    int y=0;

    // Boucle pour garantir un placement valide
    while (!placementValide) {
        std::vector<Hexagon> placementsPossibles = plateau.getPlacementsPossibles(insecteAPlacer);
        plateau.afficherPlateauAvecPossibilites(placementsPossibles, joueur1, joueur2, current);

        if (dynamic_cast<JoueurIA*>(current)){
            position = current->randomHexagonChoice(placementsPossibles);
        }
        else{
            x = getInput("Abscisse pour poser le pion : ", plateau.getMinQ() - 1, plateau.getMaxQ() + 1 , tour);
            y = getInput("Ordonn�e pour poser le pion : ", plateau.getMinR() - 1, plateau.getMaxR() + 1 , tour);
            position = Hexagon(x, y);
        }

        if (std::find(placementsPossibles.begin(), placementsPossibles.end(), position) != placementsPossibles.end() || plateau.plateauEstVide()){
            placementValide = true;
        }
    }
    plateau.ajouterInsecte(insecteAPlacer, position);
    current->retirerInsecte(index); // Retirer le pion du deck apr�s placement

    Insecte* insecteEnDessous = plateau.getInsecteAtCoords(position.getQ(), position.getR());
    PlacementAction* action = new PlacementAction(insecteAPlacer, position, current, insecteEnDessous);

    if (actionsPile.size() >= maxRetourArriere) {
        // Acc�der � l'�l�ment au sommet (le plus ancien)
        Action* actionToDelete = actionsPile.top();
        delete actionToDelete;  // Lib�rer la m�moire si n�cessaire
        actionsPile.pop();  // Retirer l'�l�ment du sommet
    }

    actionsPile.push(action);
}

bool GameMaster::detectWinner(Joueur *joueur1 , Joueur *joueur2) {
    Insecte* reineP1 = plateau.getReineAbeille(joueur1);
    Insecte* reineP2 = plateau.getReineAbeille(joueur2);
    if (reineP1 && plateau.estEntouree(reineP1)) {
        std::cout << "Le joueur " << joueur1->getName() << " a perdu ! " << std::endl;
        return true;
    }
    if (reineP2 && plateau.estEntouree(reineP2)) {
        std::cout << "Le joueur " << joueur1->getName() << " a perdu ! " << std::endl;
        return true;
    }
    return false;
}

Insecte* GameMaster::selectionnerInsecte(Joueur* current) {
    int x = 0;
    int y = 0;
    Insecte* currentInsecte = nullptr;

    while (true) {
        if (dynamic_cast<JoueurIA*>(current)) {
            Hexagon position = current->randomPionChoice(plateau.getPlateauMap());
            x = position.getQ();
            y = position.getR();
        } else {
            x = getInput("Abscisse de la position du pion à déplacer : ", plateau.getMinQ(), plateau.getMaxQ());
            y = getInput("Ordonnée de la position du pion à déplacer : ", plateau.getMinR(), plateau.getMaxR());
        }

        currentInsecte = plateau.getInsecteAtCoords(x, y);

        // Vérifiez si l'insecte est invalide, appartient à un autre joueur ou ne peut pas se déplacer.
        if (!currentInsecte) {
            std::cout << "Aucun insecte à cette position, réessayez." << std::endl;
            continue; // Demande à nouveau une position.
        }

        if (!verifierProprietairePion(current, currentInsecte)) {
            std::cout << "Ce pion n'appartient pas au joueur actuel, réessayez." << std::endl;
            continue; // Demande à nouveau une position.
        }

        // Si toutes les vérifications sont réussies, on sort de la boucle.
        break;
    }

    return currentInsecte;
}

void GameMaster::undoLastAction() {
    if (actionsPile.size() < 2) {
        std::cout << "Aucune action � annuler, la pile est vide.\n";
        return;  // Aucune action � annuler
    }

    // R�cup�rer la derni�re action de la pile
    Action* lastAction = actionsPile.top();  // Utilisation de top() au lieu de back()
    actionsPile.pop();  // Retirer l'action du sommet de la pile

    // Appeler la m�thode `undo` de l'action
    lastAction->undo(plateau);  // Vous devez passer le plateau pour que undo fonctionne

    delete lastAction;  // Lib�rer la m�moire de l'action
    std::cout << "Derni�re action annul�e.\n";
    tour--;
}

bool GameMaster::verifierProprietairePion(Joueur* current, Insecte* insecte) {
    if (insecte && insecte->getOwner() == current) {
        return true;
    }
    std::cout << "Ce pion ne vous appartient pas. Veuillez s�lectionner un de vos pions.\n";
    return false;
}

bool GameMaster::verifierDeplacementsPossiblesPourTousLesInsectes(Joueur* current) {
    for (Insecte* insecte : current->getDeck()) {
        std::vector<Hexagon> deplacementsPossibles = insecte->deplacementsPossibles(plateau.getPlateauMap());
        if (!deplacementsPossibles.empty()) {
            return true;
        }
    }
    return false;
}



