#include "GameMaster.h"

int getInput(const std::string& prompt, int minValue, int maxValue) {
    int choice;
    do {
        std::cout << prompt;
        std::cin >> choice;

        // Vérifier si l'input est valide
        if (std::cin.fail() || choice < minValue || choice > maxValue) {
            std::cin.clear(); // Réinitialiser l'état d'erreur
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignorer les caractères restants
            choice = minValue - 1; // Forcer une nouvelle saisie
            std::cout << "S'il vous plaît, entrez un nombre valide entre " << minValue << " et " << maxValue << ".\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignorer les caractères restants
        }
    } while (choice < minValue || choice > maxValue);
    return choice;
}

Insecte* GameMaster::selectionnerInsecte() {
    int x = getInput("Abscisse de la position du pion à déplacer : ", plateau.getMinQ(), plateau.getMaxQ());
    int y = getInput("Ordonnée de la position du pion à déplacer : ", plateau.getMinR(), plateau.getMaxR());

    Insecte* currentInsecte = plateau.getInsecteAtCoords(x, y);
    if (!currentInsecte) {
        std::cout << "Aucun pion à cette position. Veuillez réessayer." << std::endl;
        return selectionnerInsecte(); // Appel récursif jusqu'à obtenir un pion valide
    }
    return currentInsecte;
}

bool GameMaster::hasPlayQueen(Joueur *currentPlayer) {
    for (auto it = plateau.getInsectesSurPlateau().begin(); it != plateau.getInsectesSurPlateau().end(); ++it) {
        Insecte* insecte = *it;

        // Vérifiez si l'insecte est de type Reine et appartient au joueur actuel
        if (insecte->getNom() == "Reine" && insecte->getOwner() == currentPlayer) {
            return true;
        }
    }
    return false;
}

bool positionEstValide(const Hexagon& position, const std::vector<Hexagon>& deplacementsPossibles) {
    return std::find(deplacementsPossibles.begin(), deplacementsPossibles.end(), position) != deplacementsPossibles.end();
}
