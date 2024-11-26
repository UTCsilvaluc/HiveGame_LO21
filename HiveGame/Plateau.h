#ifndef PLATEAU_H
#define PLATEAU_H
#pragma ONCE
#include <iostream>
#include <map>
#include <vector>
#include "Hexagon.h"
#include "Insecte.h"
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define BLUE    "\033[34m"
#define YELLOW  "\033[33m"
class Plateau {
private:
    std::map<Hexagon, Insecte*> plateauMap;
    std::vector<Insecte*> insectesSurPlateau; // On peut supprimer et faire un deck de joueur, quand un joueur pose un insecte, alors l'insecte disparait de son deck grâce à ajouter Insecte
    //std::vector<Action*> historiqueDesActions;
    //std::vector<Extension*> extensionsActivees;
    int nombreRetoursArriere;
    int nombreTours;
    int minR, maxR, minQ, maxQ;

public:
    Plateau() : nombreRetoursArriere(3), nombreTours(0), minR(0), maxR(0), minQ(0), maxQ(0) {} // Initialisation par défaut
    unsigned int getTour(){return nombreTours;}
    void incrementerTour(){++nombreTours;}
    void ajouterInsecte(Insecte* insecte, Hexagon position);
    void afficherPlateauAvecPossibilites(const std::vector<Hexagon>& emplacementsPossibles, Joueur* j1, Joueur* j2);
    void afficherPossibiliteDeplacement(Insecte* insecte, const std::map<Hexagon, Insecte*>& plateau, Joueur* j1, Joueur* j2);
    void afficherPossibilitePlacement(Insecte* insecte, Joueur* j1, Joueur* j2);
    void mettreAJourLimites() {
        // Initialiser les limites à des valeurs extrêmes
        minR = std::numeric_limits<int>::max();
        maxR = std::numeric_limits<int>::min();
        minQ = std::numeric_limits<int>::max();
        maxQ = std::numeric_limits<int>::min();
        for (const auto& [coords, insecte] : plateauMap) {
            if (coords.getR() < minR) minR = coords.getR();
            if (coords.getR() > maxR) maxR = coords.getR();
            if (coords.getQ() < minQ) minQ = coords.getQ();
            if (coords.getQ() > maxQ) maxQ = coords.getQ();
        }
    }
    void ajouterInsecte(Insecte* insecte) {
        plateauMap[insecte->getCoords()] = insecte; // Ajouter à la carte
        insectesSurPlateau.push_back(insecte); // Garder une référence à l'insecte
        mettreAJourLimites(); // Mettre à jour les limites lors de l'ajout
    }

    void deplacerInsecte(Insecte* insecte, const Hexagon& nouvellePosition) {
        plateauMap.erase(insecte->getCoords()); // Retirer l'insecte de sa position actuelle
        insecte->setCoords(nouvellePosition); // Mettre à jour les coordonnées de l'insecte
        plateauMap[nouvellePosition] = insecte; // Ajouter l'insecte à la nouvelle position
        mettreAJourLimites(); // Mettre à jour les limites
    }
    void superposerInsecte(Insecte* currentInsecte, Insecte* newInsecte) {
        newInsecte->setDessous(currentInsecte);
        currentInsecte->setDessus(newInsecte);
        newInsecte->setCoords(currentInsecte->getCoords());
        plateauMap[newInsecte->getCoords()] = newInsecte;
        mettreAJourLimites(); // Mettre à jour les limites lors de la superposition
    }




    void afficherPlateau(Joueur *p1, Joueur *p2) const {
        for (int r = minR; r <= maxR; ++r) {
            // Décalage pour les lignes impaires pour créer l'effet hexagonal
            if (r % 2 != 0) {
                std::cout << "   "; // Décalage pour simuler la forme hexagonale
            }

            std::string couleur = RESET;
            for (int q = minQ; q <= maxQ; ++q) {
                Hexagon h(q, r);
                couleur = RESET;

                // Affiche l'insecte si présent, sinon un point pour une case vide
                if (plateauMap.count(h)) {
                    // Récupération de l'insecte sur la case
                    Insecte *insecte = plateauMap.at(h);
                    std::string nomInsecte = insecte->getNom();

                    // Changer la couleur en fonction du propriétaire de l'insecte
                    if (insecte->getOwner() == p1) {
                        couleur = RED;
                    } else if (insecte->getOwner() == p2) {
                        couleur = BLUE;
                    }

                    // Prendre seulement la première lettre pour éviter un affichage trop large
                    std::cout << couleur << nomInsecte[0] << couleur << "[" << h.getQ() << "," << h.getR() << "] ";
                } else {
                    // Affichage d'un point pour une case vide
                    std::cout << ".      ";
                }
            }

            // Reset de la couleur et retour à la ligne après chaque rangée
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

        // Affichage des voisins pour vérification
        std::cout << "Voisins de l'insecte (" << q << ", " << r << ") :\n";
        for (const auto& voisin : voisins) {
            std::cout << voisin << " ";
        }
        std::cout << "\n";

        return voisins;
    }


    Insecte *getReineAbeille(Joueur *joueur) const{// ou utiliser insectesSurPlateau
        for (const auto& [key, value] : plateauMap){ // https://en.cppreference.com/w/cpp/container/map
            if (value->getNom() == "Reine" && value->getOwner() == joueur){
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
            std::cout << "Vérification de la case : " << voisin << " -> ";

            if (it == plateauMap.end()) {
                std::cout << "Case vide (hors du plateau ou non initialisée).\n";
                return false;
            }

            if (it->second == nullptr) {
                std::cout << "Case présente mais aucun insecte.\n";
                return false;
            }

            // La case est occupée par un insecte
            std::cout << "Case occupée par : " << it->second->getNom() << "\n";
        }

        return true; // Toutes les cases voisines sont occupées
    }


    bool plateauEstVide(){
        return (plateauMap.size() == 0);
    }
    bool playerCanMoveInsecte(Joueur *joueur){
        for (const auto& [key, value] : plateauMap){ // https://en.cppreference.com/w/cpp/container/map
            if (value->getOwner() == joueur){
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

};

#endif // PLATEAU_H
