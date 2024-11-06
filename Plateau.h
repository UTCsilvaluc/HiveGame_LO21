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
    std::vector<Insecte*> insectesSurPlateau; // On peut supprimer et faire un deck de joueur, quand un joueur pose un insecte, alors l'insecte disparait de son deck gr�ce � ajouter Insecte
    //std::vector<Action*> historiqueDesActions;
    //std::vector<Extension*> extensionsActivees;
    int nombreRetoursArriere;
    int nombreTours;
    int minR, maxR, minQ, maxQ;

public:
    Plateau() : nombreRetoursArriere(3), nombreTours(0), minR(0), maxR(0), minQ(0), maxQ(0) {} // Initialisation par d�faut

    void mettreAJourLimites() {
        // Initialiser les limites � des valeurs extr�mes
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
        plateauMap[insecte->getCoords()] = insecte; // Ajouter � la carte
        insectesSurPlateau.push_back(insecte); // Garder une r�f�rence � l'insecte
        mettreAJourLimites(); // Mettre � jour les limites lors de l'ajout
    }

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

        std::string couleur = RESET;
        for (int q = minQ; q <= maxQ; ++q) {
            Hexagon h(q, r);
            couleur = RESET;

            // Affiche l'insecte si pr�sent, sinon un point pour une case vide
            if (plateauMap.count(h)) {
                // R�cup�ration de l'insecte sur la case
                Insecte *insecte = plateauMap.at(h);
                std::string nomInsecte = insecte->getNom();

                // Changer la couleur en fonction du propri�taire de l'insecte
                if (insecte->getOwner() == p1) {
                    couleur = RED;
                } else if (insecte->getOwner() == p2) {
                    couleur = BLUE;
                }

                // Prendre seulement la premi�re lettre pour �viter un affichage trop large
                std::cout << couleur << nomInsecte[0] << couleur << "[" << h.getQ() << "," << h.getR() << "] ";
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
    // Ajout dans la section publique de Plateau
    const std::vector<Insecte*>& getInsectesSurPlateau() const {
        return insectesSurPlateau;
    }
    std::map<Hexagon, Insecte*> getPlateauMap() {
        return plateauMap;
    }
    std::vector<Hexagon> getVoisinsInsectePlateau(Insecte *insecte){
        Hexagon coords = insecte->getCoords();
        std::vector<Hexagon> voisins; // a refaire d�pend des lignes paires / impaires
        voisins.push_back(Hexagon(coords.getQ()+1, coords.getR()));
        voisins.push_back(Hexagon(coords.getQ()-1, coords.getR()));
        voisins.push_back(Hexagon(coords.getQ()+1, coords.getR()-1));
        voisins.push_back(Hexagon(coords.getQ()-1, coords.getR()-1));
        voisins.push_back(Hexagon(coords.getQ(), coords.getR()-1));
        voisins.push_back(Hexagon(coords.getQ(), coords.getR()+1));
        return voisins;
    }
    Insecte *getReineAbeille(Joueur *joueur) const{
        for (const auto& [key, value] : plateauMap){ // https://en.cppreference.com/w/cpp/container/map
            if (value->getNom() == "Reine" && value->getOwner() == joueur){
                return value;
            }
        }
        return nullptr;
    }
    bool estEntouree(Insecte *insecte) {
        std::vector<Hexagon> voisins = getVoisinsInsectePlateau(insecte);
        for (const Hexagon& voisin : voisins) {
            // V�rifiez si la case voisine est occup�e
            if (plateauMap.find(voisin) == plateauMap.end()) {
                return false; // Si une case voisine est vide, la reine n'est pas entour�e
            }
        }
        return true; // Toutes les cases voisines sont occup�es
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
};

#endif // PLATEAU_H
