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

    // M�thode virtuelle pure pour annuler l'action
    virtual void undo(Plateau& plateau) = 0;
    virtual std::string toJson() const = 0;
};

class PlacementAction : public Action {
private:
    Insecte* insecte;        // L'insecte plac�
    Hexagon position;        // Position o� il a �t� plac�
    Joueur* joueur;          // Joueur propri�taire de l'insecte
    Insecte* insectBelow;    // Insecte en dessous avant le placement, nullptr si aucun

public:
    PlacementAction(Insecte* insecte, const Hexagon& position, Joueur* joueur, Insecte* insectBelow = nullptr)
        : insecte(insecte), position(position), joueur(joueur), insectBelow(insectBelow) {}

    void undo(Plateau& plateau) override {
        if (!insecte) {
            std::cerr << "Erreur : Aucun insecte � annuler pour le placement !" << std::endl;
            return;
        }

        // Supprimer l'insecte du plateau
        plateau.supprimerInsectePlateauCoords(position);

        // Ajouter l'insecte au deck du joueur
        if (joueur) {
            joueur->ajouterInsecte(insecte);
        }

        // Restaurer l'�tat des superpositions si n�cessaire
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
    Insecte* insecte;         // L'insecte d�plac�
    Hexagon oldPosition;      // Position avant le d�placement
    Hexagon newPosition;      // Position apr�s le d�placement
    Insecte* insectBelow;     // Insecte en dessous � l'ancienne position
    Insecte* insectAbove;     // Insecte au-dessus � la nouvelle position

public:
    DeplacementAction(Insecte* insect, const Hexagon& oldPosition, const Hexagon& newPosition,
                      Insecte* insectBelow = nullptr, Insecte* insectAbove = nullptr)
        : insecte(insect), oldPosition(oldPosition), newPosition(newPosition),
          insectBelow(insectBelow), insectAbove(insectAbove) {}

    void undo(Plateau& plateau) override {
        if (!insecte) {
            std::cerr << "Erreur : Aucun insecte � annuler pour le d�placement !" << std::endl;
            return;
        }

        // Restaurer l'insecte � son ancienne position
        plateau.deplacerInsecte(insecte, oldPosition);
        insecte->setCoords(oldPosition);

        // Restaurer l'�tat des superpositions si applicable
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
