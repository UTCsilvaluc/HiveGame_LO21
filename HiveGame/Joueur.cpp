#include "Joueur.h"
std::vector<Insecte*> deckDeBase(){
    std::vector<Insecte*> newDeck;
    newDeck.push_back(new ReineAbeille(Hexagon(0, 0)));  // Reine Abeille x1
    for (int i = 0; i < 2; ++i) { newDeck.push_back(new Araignee(Hexagon(0, 0))); }  // Araignée x2
    for (int i = 0; i < 2; ++i) { newDeck.push_back(new Scarabee(Hexagon(0, 0))); }  // Scarabée x2
    for (int i = 0; i < 3; ++i) { newDeck.push_back(new Fourmi(Hexagon(0, 0))); }    // Fourmi x3
    for (int i = 0; i < 3; ++i) { newDeck.push_back(new Sauterelle(Hexagon(0, 0))); } // Sauterelle x3
    newDeck.push_back(new Coccinelle(Hexagon(0, 0)));  // Coccinelle x1
    newDeck.push_back(new Moustique(Hexagon(0, 0)));   // Moustique x1
    return newDeck;
}
