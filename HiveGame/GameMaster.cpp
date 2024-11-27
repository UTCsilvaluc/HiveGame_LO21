#include "GameMaster.h"
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
                choice = getInputForAction(current);
            }
        }

        // Boucle pour garantir qu'une action valide est choisie avant de passer au tour suivant
        while (true) {
            if (choice == 3) {  // Retour arri�re (annulation)
                if (!actionsPile.empty()) {
                    undoLastAction();  // Annule la derni�re action
                    break;  // Sortir de la boucle apr�s retour arri�re
                } else {
                    std::cout << "Aucune action � annuler, essayez une autre option.\n";
                    choice = getInputForAction(current);  // Demander � nouveau une action
                    continue;  // Redemander le choix de l'action sans avancer au tour suivant
                }
            } else if (choice == 1) {  // D�placer un pion
                deplacerPion(current);
                break;  // Sortir de la boucle apr�s d�placement
            } else if (choice == 2) {  // Placer un nouveau pion
                placerPion(current, needPlayQueen);
                break;  // Sortir de la boucle apr�s placement
            } else {
                std::cout << "Choix invalide. Veuillez r�essayer.\n";
                choice = getInputForAction(current);  // Redemander � nouveau une action valide
            }
        }

        // Incr�menter le compteur de tours apr�s une action valide
        tour++;
    }
}
bool positionEstValide(const Hexagon& position, const std::vector<Hexagon>& deplacementsPossibles) {
    return std::find(deplacementsPossibles.begin(), deplacementsPossibles.end(), position) != deplacementsPossibles.end();
}

void GameMaster::deplacerPion(Joueur* current) {
    plateau.afficherPlateau(joueur1, joueur2);
    Insecte* currentInsecte = selectionnerInsecte();

    // V�rifier si le pion appartient au joueur actuel
    while (!verifierProprietairePion(current, currentInsecte)) {
        currentInsecte = selectionnerInsecte(); // Demander � nouveau la s�lection du pion
    }

    bool deplacementValide = false;
    Hexagon nouvellePosition;

    while (!deplacementValide) {
        std::vector<Hexagon> deplacementsPossibles = currentInsecte->deplacementsPossibles(plateau.getPlateauMap());
        for (const auto &deps:deplacementsPossibles){
            std::cout<< deps<<"";
        }
        int x = getInput("Abscisse pour poser le pion : ", plateau.getMinQ() - 1 , plateau.getMaxQ() + 1);
        int y = getInput("Ordonn�e pour poser le pion : ", plateau.getMinR() - 1, plateau.getMaxR() + 1);
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

void GameMaster::placerPion(Joueur* current, bool needPlayQueen) {
    Insecte* insecteAPlacer = nullptr;
    int index = 0;

    // S�lection du pion � placer
    if (!needPlayQueen) {
        std::cout << "\nVoici votre deck : " << std::endl;
        current->afficherDeck();
        index = getInput("Quel pion souhaitez-vous poser ? ", 1, current->getDeckSize()) - 1;
        insecteAPlacer = current->getInsecteByIndex(index);
    } else {
        insecteAPlacer = current->getQueen();
        index = current->getQueenIndex();
    }

    if (!plateau.plateauEstVide()) {
        plateau.afficherPlateau(joueur1, joueur2);
    }

    Hexagon nouvellePosition;
    bool placementValide = false;

    // Boucle pour garantir un placement valide
    while (!placementValide) {
        int x = getInput("Abscisse pour poser le pion : ", plateau.getMinQ() - 1, plateau.getMaxQ() + 1 , tour);
        int y = getInput("Ordonn�e pour poser le pion : ", plateau.getMinR() - 1, plateau.getMaxR() + 1 , tour);
        nouvellePosition = Hexagon(x, y);

        if (plateau.plateauEstVide()) {
            // Si le plateau est vide, tout placement est valide
            placementValide = true;
        } else {
            // V�rifier les voisins du premier insecte sur le plateau
            if (!plateau.playerCanMoveInsecte(current)) {
                Insecte* seulInsecte = plateau.getSeulInsecteSurPlateau();
                if (!seulInsecte) {
                    std::cout << "Erreur : aucun insecte trouv� sur le plateau." << std::endl;
                    return;
                }

                // R�cup�rer les voisins de l'insecte
                std::vector<Hexagon> deplacementsPossibles = seulInsecte->getCoords().getVoisins();

                // Afficher les voisins
                std::cout << "Les voisins possibles pour le placement sont : " << std::endl;
                for (const Hexagon& voisin : deplacementsPossibles) {
                    std::cout << "Voisin : (" << voisin.getQ() << ", " << voisin.getR() << ")" << std::endl;
                }

                if (std::find(deplacementsPossibles.begin(), deplacementsPossibles.end(), nouvellePosition) != deplacementsPossibles.end()) {
                    placementValide = true;
                } else {
                    std::cout << "Placement invalide. Vous devez �tre adjacent au premier pion du plateau. Essayez � nouveau.\n";
                }
            } else {
                std::vector<Hexagon> voisins = nouvellePosition.getVoisins();
                bool adjacentAllie = false;
                bool toucheEnnemi = false;

                for (const Hexagon& voisin : voisins) {
                    Insecte* insecteVoisin = plateau.getInsecteAtCoords(voisin.getQ(), voisin.getR());
                    if (insecteVoisin) {
                        if (insecteVoisin->getOwner() == current) {
                            adjacentAllie = true;
                        } else {
                            toucheEnnemi = true;
                        }
                    }
                }

                if (adjacentAllie && !toucheEnnemi) {
                    placementValide = true;
                } else {
                    std::cout << "Placement invalide. Votre pion doit �tre adjacent � un de vos pions et ne pas toucher un pion ennemi. Essayez � nouveau.\n";
                }
            }
        }
    }
    insecteAPlacer->setCoords(nouvellePosition);
    plateau.ajouterInsecte(insecteAPlacer);
    current->retirerInsecte(index); // Retirer le pion du deck apr�s placement
    Insecte* insecteEnDessous = plateau.getInsecteAtCoords(nouvellePosition.getQ(), nouvellePosition.getR());
    PlacementAction* action = new PlacementAction(insecteAPlacer, nouvellePosition, current, insecteEnDessous);
    std::cout << "Pion plac� avec succ�s en " << nouvellePosition << "." << std::endl;
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
void GameMaster::undoLastAction() {
    if (actionsPile.empty()) {
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


