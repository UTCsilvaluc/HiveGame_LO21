#ifndef PLATEAU_H
#define PLATEAU_H

#include <iostream>
#include <map>
#include <vector>
#include "Hexagon.h"
#include "Insecte.h"

class Plateau {
private:
    std::map<Hexagon, Insecte*> plateauMap;
    std::vector<Insecte*> insectesSurPlateau; // On peut supprimer et faire un deck de joueur, quand un joueur pose un insecte, alors l'insecte disparait de son deck grâce à ajouter Insecte
    //std::vector<Action*> historiqueDesActions;
    //std::vector<Extension*> extensionsActivees;
    int nombreRetoursArriere;
    int nombreTours;

public:
    Plateau() : nombreRetoursArriere(3), nombreTours(0) {} // Initialisation par défaut

    void ajouterInsecte(Insecte* insecte) {
        plateauMap[insecte->getCoords()] = insecte; // Ajouter à la carte
        insectesSurPlateau.push_back(insecte); // Garder une référence à l'insecte
    }

    void deplacerInsecte(Insecte* insecte, const Hexagon& nouvellePosition) {
        // Mettre à jour la position de l'insecte
    }
    void superposerInsecte(Insecte* currentInsecte, Insecte* newInsecte) {

    }
    void afficherPlateau() const {
        int minR = 0, maxR = 0, minQ = 0, maxQ = 0;

        // Déterminer les limites du , ses extremités afin de partir du début à la fin.
        for (const auto& [coords, insecte] : plateauMap) {
            if (coords.getQ() < minQ) minQ = coords.getQ();
            if (coords.getQ() > maxQ) maxQ = coords.getQ();
            if (coords.getR() < minR) minR = coords.getR();
            if (coords.getR() > maxR) maxR = coords.getR();
        }
        for (int r = minR; r <= maxR; ++r) {
            if (r % 2 != 0) std::cout << "  "; // pour essayer de faire ressembler à un hexagone ptdr c immonde

            for (int q = minQ; q <= maxQ; ++q) {
                Hexagon h(q, r);
                if (plateauMap.count(h)) {
                    std::cout << plateauMap.at(h)->getNom() << "   "; // L'insecte existe alors je récupère son nom
                } else {
                    std::cout << ".   ";  // Aucun insecte à cet emplacement
                }
            }
            std::cout << std::endl;
        }
    }
};

#endif // PLATEAU_H
