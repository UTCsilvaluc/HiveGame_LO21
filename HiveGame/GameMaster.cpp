#include "GameMaster.h"
void GameMaster::startGame() {
    displaySaveGame();
    std::cout << "\nD�marrage du jeu HiveGame en cours...\n" << std::endl;
    //choixExtensions();
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

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "GameMaster.h"
#include "Insecte.h"  // Supposons que tu as une classe Insecte avec les coordonnées q, r

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "GameMaster.h"
#include "Insecte.h"  // Supposons que tu as une classe Insecte avec les coordonnées q, r

void GameMaster::displaySaveGame() {
    // Ouvre le fichier save_game.json
    std::ifstream file("game_save2.json");

    if (!file.is_open()) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier game_save2.json" << std::endl;
        return;
    }

    std::stringstream jsonData;
    jsonData << file.rdbuf();  // Lire tout le contenu du fichier dans un stringstream
    file.close();  // Fermer le fichier après la lecture

    std::string jsonContent = jsonData.str();  // Contenu du fichier sous forme de chaîne de caractères

    std::cout << "Affichage des insectes dans le fichier game_save2.json..." << std::endl;

    // Exemple d'extraction et d'affichage de données des insectes
    size_t pos = 0;
    std::string insectPattern = "\"nom\": \"";
    while ((pos = jsonContent.find(insectPattern, pos)) != std::string::npos) {
        size_t startNom = jsonContent.find("\"nom\": \"", pos) + 8;  // Début du nom
        size_t endNom = jsonContent.find("\"", startNom);  // Fin du nom
        std::string nomInsecte = jsonContent.substr(startNom, endNom - startNom);  // Extraire le nom

        // Extraire les coordonnées
        size_t startQ = jsonContent.find("\"q\":", endNom) + 4;
        size_t endQ = jsonContent.find(",", startQ);
        int q = std::stoi(jsonContent.substr(startQ, endQ - startQ));  // Extraire q

        size_t startR = jsonContent.find("\"r\":", endQ) + 4;
        size_t endR = jsonContent.find("}", startR);
        int r = std::stoi(jsonContent.substr(startR, endR - startR));  // Extraire r

        // Extraire le nom du propriétaire
        size_t startOwner = jsonContent.find("\"owner\": \"", endR) + 10;
        size_t endOwner = jsonContent.find("\"", startOwner);
        std::string owner = jsonContent.substr(startOwner, endOwner - startOwner);  // Extraire le propriétaire

        // Afficher les informations de l'insecte
        std::cout << "Insecte : " << nomInsecte << ", Coordonnées (q, r) : (" << q << ", " << r << "), Propriétaire : " << owner << std::endl;

        // Avance la position dans le fichier JSON
        pos = endR;
    }
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

    int x = 0;
    int y = 0;

    while (!deplacementValide) {
        std::vector<Hexagon> deplacementsPossibles = currentInsecte->deplacementsPossibles(plateau.getPlateauMap());
        plateau.afficherPossibiliteDeplacement(currentInsecte, plateau.getPlateauMap(), joueur1, joueur2, current);

        std::cout << "Déplacements possibles pour " << currentInsecte->getNom() << " : \n";
        for (size_t i = 0; i < deplacementsPossibles.size(); ++i) {
            std::cout << i + 1 << ". (" << deplacementsPossibles[i].getQ() << ", " << deplacementsPossibles[i].getR() << ")\n";
        }
        std::cout << "-1. Annuler le déplacement\n";

        if (dynamic_cast<JoueurIA*>(current)) {
            Hexagon position = current->randomHexagonChoice(deplacementsPossibles);
            x = position.getQ();
            y = position.getR();
        } else {
            int choix = getInput("Choisissez un emplacement ou entrez -1 pour annuler : ", -1, deplacementsPossibles.size());

            // Annuler si l'utilisateur entre -1
            if (choix == -1) {
                std::cout << "Déplacement annulé.\n";
                tour--;
                return;
            }

            Hexagon position = deplacementsPossibles[choix - 1];
            x = position.getQ();
            y = position.getR();
        }

        nouvellePosition = Hexagon(x, y);
        if (positionEstValide(nouvellePosition, deplacementsPossibles)) {
            deplacementValide = true;
        } else {
            std::cout << "Déplacement invalide. Veuillez choisir une coordonnée valide." << std::endl;
        }
    }


    actionsPile.push(new DeplacementAction(currentInsecte, currentInsecte->getCoords(), nouvellePosition));

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
            if (!plateau.playerCanMoveInsecte(current)) {
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
                    undoLastTwoActions();
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
        //saveGame();
    }
}

void GameMaster::placerPion(Joueur* current, bool needPlayQueen) {
    Insecte* insecteAPlacer = nullptr;
    int index = 0;

    // Sélection du pion à placer
    if (!needPlayQueen) {
        std::cout << "\nVoici votre deck : " << std::endl;
        current->afficherDeck();
        if (dynamic_cast<JoueurIA*>(current)) {
            index = current->randomDeckChoice();
        }
        else {
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

    int x = 0;
    int y = 0;

    // Boucle pour garantir un placement valide
    while (!placementValide) {
        if (plateau.plateauEstVide()) {
            std::cout << "Le plateau est vide, vous devez entrer les coordonnées directement.\n";
            x = getInput("Abscisse pour poser le pion : ", plateau.getMinQ() - 1, plateau.getMaxQ() + 1 , tour);
            y = getInput("Ordonnée pour poser le pion : ", plateau.getMinR() - 1, plateau.getMaxR() + 1 , tour);
            position = Hexagon(x, y);
        } else {
            std::vector<Hexagon> placementsPossibles = plateau.getPlacementsPossibles(insecteAPlacer);

            plateau.afficherPlateauAvecPossibilites(placementsPossibles, joueur1, joueur2, current);

            std::cout << "Déplacements possibles pour " << insecteAPlacer->getNom() << " : \n";
            for (size_t i = 0; i < placementsPossibles.size(); ++i) {
                std::cout << i + 1 << ". (" << placementsPossibles[i].getQ() << ", " << placementsPossibles[i].getR() << ")\n";
            }
            std::cout << "-1. Annuler le placement\n";

            if (dynamic_cast<JoueurIA*>(current)) {
                position = current->randomHexagonChoice(placementsPossibles);
            } else {
                int choix = getInput("Choisissez un emplacement ou entrez -1 pour annuler : ", -1, placementsPossibles.size());

                if (choix == -1) {
                    std::cout << "Placement annulé.\n";
                    tour--;
                    return;
                }
                position = placementsPossibles[choix - 1];
            }
        }
        if (plateau.plateauEstVide() || std::find(plateau.getPlacementsPossibles(insecteAPlacer).begin(), plateau.getPlacementsPossibles(insecteAPlacer).end(), position) != plateau.getPlacementsPossibles(insecteAPlacer).end()) {
            placementValide = true;
        }
    }

    plateau.ajouterInsecte(insecteAPlacer, position);
    current->retirerInsecte(index);
    Insecte* insecteEnDessous = plateau.getInsecteAtCoords(position.getQ(), position.getR());
    PlacementAction* action = new PlacementAction(insecteAPlacer, position, current, insecteEnDessous);
    if (actionsPile.size() >= maxRetourArriere) {
        Action* actionToDelete = actionsPile.top();
        delete actionToDelete;
        actionsPile.pop();
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
    std::vector<Insecte*> insectesDuJoueur = plateau.getInsectesDuJoueur(current);
    if (insectesDuJoueur.empty()) {
        std::cout << "Aucun insecte du joueur sur le plateau." << std::endl;
        return nullptr;
    }
    std::cout << "Choisissez un insecte par son index :\n";
    for (size_t i = 0; i < insectesDuJoueur.size(); ++i) {
        std::cout << i << ": " << insectesDuJoueur[i]->getNom() << " - Position: ("
                  << insectesDuJoueur[i]->getCoords().getQ() << ", "
                  << insectesDuJoueur[i]->getCoords().getR() << ")\n";
    }
    int indexChoisi = getInput("Entrez l'index de l'insecte à sélectionner (ou -1 pour annuler) : ", -1, insectesDuJoueur.size() - 1);
    if (indexChoisi == -1) {
        std::cout << "Action annulée.\n";
        return nullptr;
    }
    return insectesDuJoueur[indexChoisi];
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


#include <fstream>
#include <sstream>

std::string GameMaster::toJson() const {
    std::stringstream jsonData;
    jsonData << "{\n";

    // Plateau
    jsonData << "  \"plateau\": " << plateau.toJson() << ",\n";

    // Joueur 1
    jsonData << "  \"joueur1\": "
             << (joueur1 ? joueur1->toJson() : "null") << ",\n";

    // Joueur 2
    jsonData << "  \"joueur2\": "
             << (joueur2 ? joueur2->toJson() : "null") << ",\n";

    // Mode
    jsonData << "  \"mode\": " << mode << ",\n";

    // Tour
    jsonData << "  \"tour\": " << tour << ",\n";

    // Max retours arrière
    jsonData << "  \"maxRetourArriere\": " << maxRetourArriere << "\n";

    jsonData << "}";
    return jsonData.str();
}

#include <fstream>
#include <sstream>

bool fileExists(const std::string& fileName) {
    std::ifstream file(fileName);
    return file.good();
}

void GameMaster::saveGame() {
    std::string baseFileName = "game_save";
    std::string fileExtension = ".json";
    std::string fileName = baseFileName + fileExtension;

    // Vérifier si un fichier existe déjà
    int fileIndex = 0;
    while (fileExists(fileName)) {
        ++fileIndex;
        std::ostringstream oss;
        oss << baseFileName << fileIndex << fileExtension;
        fileName = oss.str();
    }

    // Écrire dans le fichier disponible
    std::ofstream file(fileName);
    if (file.is_open()) {
        file << toJson();
        file.close();
        std::cout << "Partie sauvegardée dans le fichier : " << fileName << std::endl;
    } else {
        std::cerr << "Erreur : Impossible de sauvegarder la partie." << std::endl;
    }
}

void GameMaster::undoLastTwoActions() {
    if (actionsPile.size() < 2) {
        std::cout << "Pas assez d'actions dans la pile pour annuler. Minimum requis : 2.\n";
        return;  // Pas assez d'actions à annuler
    }

    for (int i = 0; i < 2; ++i) {
        // Récupérer la dernière action de la pile
        Action* lastAction = actionsPile.top();
        actionsPile.pop();  // Retirer l'action du sommet de la pile

        // Appeler la méthode `undo` de l'action
        lastAction->undo(plateau);  // Passer le plateau pour que undo fonctionne correctement

        delete lastAction;  // Libérer la mémoire de l'action
        std::cout << "Action annulée (" << (i + 1) << "/2).\n";
        tour--;  // Réduire le numéro du tour
    }
}

#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
/*
void GameMaster::loadGame(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        throw std::runtime_error("Erreur : Impossible d'ouvrir le fichier de sauvegarde.");
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string jsonContent = buffer.str();

    // Simple parsing pour extraire les parties de données du JSON
    // Vous devrez probablement ajuster cela pour que ce soit plus robuste

    // Exemple de découpe basique du JSON
    if (jsonContent.find("\"plateau\"") != std::string::npos) {
        // Extraire et reconstruire l'objet Plateau
        size_t startPos = jsonContent.find("\"plateau\":") + 10;
        size_t endPos = jsonContent.find("\"joueur1\":");
        std::string plateauData = jsonContent.substr(startPos, endPos - startPos);

        // Appel de la méthode fromJson pour Plateau
        plateau.fromJson(plateauData); // Implémentez fromJson pour Plateau

        // Extraire et reconstruire les joueurs
        startPos = endPos + 10;
        endPos = jsonContent.find("\"mode\":");
        std::string joueur1Data = jsonContent.substr(startPos, endPos - startPos);

        joueur1->fromJson(joueur1Data); // Implémentez fromJson pour Joueur

        // Idem pour le joueur2 et autres paramètres
        startPos = endPos + 7;
        endPos = jsonContent.find("\"maxRetourArriere\":");
        std::string joueur2Data = jsonContent.substr(startPos, endPos - startPos);

        joueur2->fromJson(joueur2Data);
        mode = std::stoi(jsonContent.substr(endPos + 19, 1)); // Extraction de mode
        tour = std::stoi(jsonContent.substr(endPos + 27, 1)); // Extraction de tour
        maxRetourArriere = std::stoi(jsonContent.substr(endPos + 41, 1)); // Extraction de maxRetourArriere
    }

    file.close();
    std::cout << "Partie chargée avec succès depuis " << fileName << "." << std::endl;
}
*/
