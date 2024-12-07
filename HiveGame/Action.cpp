#include "Action.h"
// Ajouter des actions sp�cifiques au gestionnaire
void PlacementAction::executerAction(Plateau& plateau) {
    plateau.ajouterInsecte(insecte, position);
    std::cout<<"placement edddddddddddddddddffectu� bg"<<std::endl;
    if (plateau.getInsecteAt(position)) {
        insectBelow = plateau.getInsecteAt(position);
    }
}

void PlacementAction::undo(Plateau& plateau) {
    if (!insecte) {
        std::cerr << "Erreur : Aucun insecte � annuler pour le placement !" << std::endl;
        return;
    }

    plateau.supprimerInsectePlateauCoords(position);

    if (joueur) {
        joueur->ajouterInsecte(insecte);
    }

    if (insectBelow) {
        insectBelow->setDessus(nullptr);
    }
}

std::string PlacementAction::toJson() const {
    return "{\"type\": \"PlacementAction\", \"position\": " + position.toJson() + "}";
}

void DeplacementAction::executerAction(Plateau& plateau)  {
    plateau.deplacerInsecte(insecte, newPosition);
}

void DeplacementAction::undo(Plateau& plateau)  {
    if (!insecte) {
        std::cerr << "Erreur : Aucun insecte � annuler pour le d�placement !" << std::endl;
        return;
    }
    plateau.deplacerInsecte(insecte, oldPosition);
}

std::string DeplacementAction::toJson() const  {
    return "{\"type\": \"DeplacementAction\", \"oldPosition\": " + oldPosition.toJson() + ", \"newPosition\": " + newPosition.toJson() + "}";
}

void MangerPionAction::executerAction(Plateau& plateau) {
    insectToRemove = plateau.getInsecteAt(newPosition);
    if (insectToRemove) {
        plateau.supprimerInsectePlateauCoords(newPosition);
    }
    plateau.deplacerInsecte(insecte, newPosition);
}

void MangerPionAction::undo(Plateau& plateau) {
    // R�vertir le d�placement de l'insecte � sa position initiale
    plateau.deplacerInsecte(insecte, oldPosition);
    // R�ajouter l'insecte mang� � sa position pr�c�dente
    if (insectToRemove) {
        plateau.ajouterInsecte(insectToRemove, newPosition);
    }
}

std::string MangerPionAction::toJson() const {
    return "{\"type\": \"MangerPionAction\", \"oldPosition\": " + oldPosition.toJson() + ", \"newPosition\": " + newPosition.toJson() + "}";
}
