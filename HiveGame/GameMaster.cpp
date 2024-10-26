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
