#ifndef JOUEUR_H
#define JOUEUR_H
#include "Insecte.h"
class Joueur
{
private:
    std::string nom;
    std::vector<Insecte*> deck;
public:
    Joueur(std::string n, std::vector<Insecte*> d = std::vector<Insecte*>()) {
        if (n.empty()) {throw std::invalid_argument("Le nom ne peut pas être vide.");}
        nom = n;
        // Si un deck est fourni, l'utiliser ; sinon, utiliser le deck par défaut. Permet de gérer les extensions en cvas de besoin.
        if (d.empty()){
            deck.push_back(new ReineAbeille(Hexagon(0, 0)));  // Reine Abeille x1
            for (int i = 0; i < 2; ++i) { deck.push_back(new Araignee(Hexagon(0, 0))); }  // Araignée x2
            for (int i = 0; i < 2; ++i) { deck.push_back(new Scarabee(Hexagon(0, 0))); }  // Scarabée x2
            for (int i = 0; i < 3; ++i) { deck.push_back(new Fourmi(Hexagon(0, 0))); }    // Fourmi x3
            for (int i = 0; i < 3; ++i) { deck.push_back(new Sauterelle(Hexagon(0, 0))); } // Sauterelle x3
            deck.push_back(new Coccinelle(Hexagon(0, 0)));  // Coccinelle x1
            deck.push_back(new Moustique(Hexagon(0, 0)));   // Moustique x1

        }
        deck = d.empty() ? d : d;
    }
    std::string getName() const {return nom;}
    std::vector<Insecte*>& getDeck() { return deck; }
};

#endif // JOUEUR_H
