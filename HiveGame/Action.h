#ifndef ACTION_H
#define ACTION_H

#include "Hexagon.h"
#include "Insecte.h"
#include "Plateau.h"
#include "Joueur.h"

// Classe de base abstraite pour les actions
class Action {
public:
    virtual ~Action() = default;

    // Méthode virtuelle pure pour annuler l'action
    virtual void undo(Plateau& plateau) = 0;
    virtual std::string toJson() const = 0;
};

class PlacementAction : public Action {
private:
    Insecte* insecte;        // L'insecte placé
    Hexagon position;        // Position où il a été placé
    Joueur* joueur;          // Joueur propriétaire de l'insecte
    Insecte* insectBelow;    // Insecte en dessous avant le placement, nullptr si aucun

public:
    PlacementAction(Insecte* insecte, const Hexagon& position, Joueur* joueur, Insecte* insectBelow = nullptr)
        : insecte(insecte), position(position), joueur(joueur), insectBelow(insectBelow) {}

    void undo(Plateau& plateau) override {
        if (!insecte) {
            std::cerr << "Erreur : Aucun insecte à annuler pour le placement !" << std::endl;
            return;
        }

        // Supprimer l'insecte du plateau
        plateau.supprimerInsectePlateauCoords(position);

        // Ajouter l'insecte au deck du joueur
        if (joueur) {
            joueur->ajouterInsecte(insecte);
        }

        // Restaurer l'état des superpositions si nécessaire
        if (insectBelow) {
            insectBelow->setDessus(nullptr);
        }
    }
    std::string toJson() const override {
        std::string json = "{";
        json += "\"type\": \"PlacementAction\",";
        json += "\"insecte\": " + (insecte ? insecte->toJson() : "null") + ",";
        json += "\"position\": " + position.toJson() + ",";
        json += "\"joueur\": " + (joueur ? joueur->toJson() : "null") + ",";
        json += "\"insectBelow\": " + (insectBelow ? insectBelow->toJson() : "null");
        json += "}";
        return json;
    }

};

class DeplacementAction : public Action {
private:
    Insecte* insecte;         // L'insecte déplacé
    Hexagon oldPosition;      // Position avant le déplacement
    Hexagon newPosition;      // Position après le déplacement
    Insecte* insectBelow;     // Insecte en dessous à l'ancienne position
    Insecte* insectAbove;     // Insecte au-dessus à la nouvelle position

public:
    DeplacementAction(Insecte* insect, const Hexagon& oldPosition, const Hexagon& newPosition,
                      Insecte* insectBelow = nullptr, Insecte* insectAbove = nullptr)
        : insecte(insect), oldPosition(oldPosition), newPosition(newPosition),
          insectBelow(insectBelow), insectAbove(insectAbove) {}

    void undo(Plateau& plateau) override {
        if (!insecte) {
            std::cerr << "Erreur : Aucun insecte à annuler pour le déplacement !" << std::endl;
            return;
        }

        // Restaurer l'insecte à son ancienne position
        plateau.deplacerInsecte(insecte, oldPosition);
        insecte->setCoords(oldPosition);

        // Restaurer l'état des superpositions si applicable
        if (insectBelow) {
            insectBelow->setDessus(insecte);
        }
        if (insectAbove) {
            insectAbove->setDessous(nullptr);
        }
    }
    std::string toJson() const override{
        std::string json = "{";
        json += "\"type\": \"DeplacementAction\",";
        json += "\"insecte\": " + (insecte ? insecte->toJson() : "null") + ",";
        json += "\"oldPosition\": " + oldPosition.toJson() + ",";
        json += "\"newPosition\": " + newPosition.toJson() + ",";
        json += "\"insectBelow\": " + (insectBelow ? insectBelow->toJson() : "null") + ",";
        json += "\"insectAbove\": " + (insectAbove ? insectAbove->toJson() : "null");
        json += "}";
        return json;
    }

};


#endif // ACTION_H
