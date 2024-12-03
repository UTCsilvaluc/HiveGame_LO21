#ifndef PLATEAU_H
#define PLATEAU_H
#pragma ONCE
#include <iostream>
#include <map>
#include <vector>
#include "Hexagon.h"
#include "Insecte.h"
#include <limits>
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define BLUE    "\033[34m"
#define YELLOW  "\033[33m"
#define GREEN   "\033[32m"
class Plateau {
private:
    std::map<Hexagon, Insecte*> plateauMap;
    std::vector<Insecte*> insectesSurPlateau; // On peut supprimer et faire un deck de joueur, quand un joueur pose un insecte, alors l'insecte disparait de son deck gr�ce � ajouter Insecte
    //std::vector<Action*> historiqueDesActions;
    //std::vector<Extension*> extensionsActivees;
    int nombreRetoursArriere;
    int minR, maxR, minQ, maxQ;

public:
    Plateau() : nombreRetoursArriere(3), minR(0), maxR(0), minQ(0), maxQ(0) {} // Initialisation par d�faut
    void afficherPlateauAvecPossibilites(const std::vector<Hexagon>& emplacementsPossibles, Joueur* j1, Joueur* j2, Joueur* current);
    void afficherPossibiliteDeplacement(Insecte* insecte, const std::map<Hexagon, Insecte*>& plateau, Joueur* j1, Joueur* j2, Joueur* current);
    std::vector<Hexagon> getPlacementsPossibles(Insecte* insecte);
    void mettreAJourLimites() {
        // Initialiser les limites � des valeurs extr�mes
        minR = std::numeric_limits<int>::max();
        maxR = std::numeric_limits<int>::min();
        minQ = std::numeric_limits<int>::max();
        maxQ = std::numeric_limits<int>::min();
        for (const auto& pair : plateauMap) {
            const auto& coords = pair.first;
            const auto& insecte = pair.second;
            if (coords.getR() < minR) minR = coords.getR();
            if (coords.getR() > maxR) maxR = coords.getR();
            if (coords.getQ() < minQ) minQ = coords.getQ();
            if (coords.getQ() > maxQ) maxQ = coords.getQ();
        }
    }

    void ajouterInsecte(Insecte* insecte, Hexagon position);

    void deplacerInsecte(Insecte* insecte, const Hexagon& nouvellePosition) {
        plateauMap.erase(insecte->getCoords()); // Retirer l'insecte de sa position actuelle
        insecte->setCoords(nouvellePosition); // Mettre � jour les coordonn�es de l'insecte
        plateauMap[nouvellePosition] = insecte; // Ajouter l'insecte � la nouvelle position
        mettreAJourLimites(); // Mettre � jour les limites
    }
    void superposerInsecte(Insecte* currentInsecte, Insecte* newInsecte) {
        newInsecte->setDessous(currentInsecte);
        currentInsecte->setDessus(newInsecte);
        newInsecte->setCoords(currentInsecte->getCoords());
        plateauMap[newInsecte->getCoords()] = newInsecte;
        mettreAJourLimites(); // Mettre � jour les limites lors de la superposition
    }




    void afficherPlateau(Joueur *p1, Joueur *p2) const {
        for (int r = minR; r <= maxR; ++r) {
            // D�calage pour les lignes impaires pour cr�er l'effet hexagonal
            if (r % 2 != 0) {
                std::cout << "   "; // D�calage pour simuler la forme hexagonale
            }

            std::string couleurInsecte = RESET;
            std::string couleurCoord = RESET;
            for (int q = minQ; q <= maxQ; ++q) {
                Hexagon h(q, r);
                couleurInsecte = RESET;
                couleurCoord = RESET;

                // Affiche l'insecte si pr�sent, sinon un point pour une case vide
                if (plateauMap.count(h)) {
                    // R�cup�ration de l'insecte sur la case
                    Insecte *insecte = plateauMap.at(h);
                    std::string nomInsecte = insecte->getNom();

                    // Changer la couleur en fonction du propri�taire de l'insecte
                    if (insecte->getOwner() == p1) {
                        couleurInsecte = RED;
                        couleurCoord = RED;
                    } else if (insecte->getOwner() == p2) {
                        couleurInsecte = BLUE;
                        couleurCoord = BLUE;
                    }

                    // Si c'est un l'affichage des placements/deplacements possibles
                    if (dynamic_cast<InsecteFictif*>(insecte))
                        couleurCoord = GREEN;

                    // Prendre seulement la premi�re lettre pour �viter un affichage trop large
                    std::cout << couleurInsecte << nomInsecte[0] << couleurCoord << "[" << h.getQ() << "," << h.getR() << "] ";
                } else {
                    // Affichage d'un point pour une case vide
                    std::cout << ".      ";
                }
            }

            // Reset de la couleur et retour � la ligne apr�s chaque rang�e
            std::cout << RESET << std::endl << std::endl;
        }
    }


    int getMinR() const { return minR; }
    int getMaxR() const { return maxR; }
    int getMinQ() const { return minQ; }
    int getMaxQ() const { return maxQ; }

    Insecte* getInsecteAtCoords(int q , int r){
        Hexagon h(q , r);
        if (!(plateauMap.count(h))){return nullptr;}
        return plateauMap[h];
    }
    const std::vector<Insecte*>& getInsectesSurPlateau() const {
        return insectesSurPlateau;
    }
    std::map<Hexagon, Insecte*> getPlateauMap() {
        return plateauMap;
    }
    std::vector<Hexagon> getVoisinsInsectePlateau(Insecte *insecte) {
        std::vector<Hexagon> voisins;
        int q = insecte->getCoords().getQ();
        int r = insecte->getCoords().getR();
        if (r % 2 == 0) {  // Colonne paire
            voisins = {
                Hexagon(q - 1, r - 1),
                Hexagon(q, r - 1),
                Hexagon(q + 1, r),
                Hexagon(q, r + 1),
                Hexagon(q - 1, r + 1),
                Hexagon(q - 1, r)
            };
        } else {  // Colonne impaire
            voisins = {
                Hexagon(q, r - 1),
                Hexagon(q + 1, r - 1),
                Hexagon(q+1, r),
                Hexagon(q+1, r+1),
                Hexagon(q, r+1),
                Hexagon(q-1, r)
            };
        }

        // Affichage des voisins pour v�rification
        std::cout << "Voisins de l'insecte (" << q << ", " << r << ") :\n";
        for (const auto& voisin : voisins) {
            std::cout << voisin << " ";
        }
        std::cout << "\n";

        return voisins;
    }


    Insecte* getReineAbeille(Joueur* joueur) const { // ou utiliser insectesSurPlateau
        for (const auto& pair : plateauMap) {
            const auto& value = pair.second;
            if (value->getNom() == "Reine" && value->getOwner() == joueur) {
                return value;
            }
        }
        return nullptr;
    }
    bool estEntouree(Insecte *insecte) {
        std::vector<Hexagon> voisins = getVoisinsInsectePlateau(insecte);
        std::cout << "Voisins de l'insecte (" << insecte->getCoords().getQ() << ", " << insecte->getCoords().getR() << ") :\n";

        for (const Hexagon& voisin : voisins) {
            auto it = plateauMap.find(voisin);

            // Affichage pour debug
            std::cout << "V�rification de la case : " << voisin << " -> ";

            if (it == plateauMap.end()) {
                std::cout << "Case vide (hors du plateau ou non initialis�e).\n";
                return false;
            }

            if (it->second == nullptr) {
                std::cout << "Case pr�sente mais aucun insecte.\n";
                return false;
            }

            // La case est occup�e par un insecte
            std::cout << "Case occup�e par : " << it->second->getNom() << "\n";
        }

        return true; // Toutes les cases voisines sont occup�es
    }


    bool plateauEstVide(){
        return (plateauMap.size() == 0);
    }

    bool playerCanMoveInsecte(Joueur* joueur) {
        for (const auto& pair : plateauMap) {
            const auto& insecte = pair.second;
            if (insecte->getOwner() == joueur && !insecte->deplacementsPossibles(plateauMap).empty()) {
                return true;
            }
        }
        return false;
    }


    Insecte* getSeulInsecteSurPlateau() const {
        if (plateauMap.size() == 1) {
            return plateauMap.begin()->second; // Retourne le premier (et seul) insecte
        }
        return nullptr; // Retourne nullptr si aucun ou plusieurs insectes
    }

    void supprimerInsectePlateauCoords(const Hexagon& position) {
        auto it = plateauMap.find(position);
        if (it == plateauMap.end()) {
            std::cerr << "Erreur : Aucun insecte trouv� � la position (" << position.getQ()
                      << ", " << position.getR() << ")." << std::endl;
            return;
        }
        Insecte* insecteASupprimer = it->second;
        plateauMap.erase(it); // Supprimer l'insecte de la map

        // Retirer l'insecte de la liste des insectes sur le plateau
        auto itInsecte = std::find(insectesSurPlateau.begin(), insectesSurPlateau.end(), insecteASupprimer);
        if (itInsecte != insectesSurPlateau.end()) {
            insectesSurPlateau.erase(itInsecte);
        }
        mettreAJourLimites();
    }

};

#endif // PLATEAU_H
