#include "Joueur.h"
std::vector<Insecte*> deckDeBase(){
    std::vector<Insecte*> newDeck;
    for (int i = 0; i < 2; ++i) { newDeck.push_back(new Araignee(Hexagon(0, 0))); }  // Araignée x2
    for (int i = 0; i < 2; ++i) { newDeck.push_back(new Scarabee(Hexagon(0, 0))); }  // Scarabée x2
    for (int i = 0; i < 3; ++i) { newDeck.push_back(new Fourmi(Hexagon(0, 0))); }    // Fourmi x3
    for (int i = 0; i < 3; ++i) { newDeck.push_back(new Sauterelle(Hexagon(0, 0))); } // Sauterelle x3
    newDeck.push_back(new Coccinelle(Hexagon(0, 0)));  // Coccinelle x1
    newDeck.push_back(new Moustique(Hexagon(0, 0)));   // Moustique x1
    newDeck.push_back(new ReineAbeille(Hexagon(0, 0)));  // Reine Abeille x1
    return newDeck;
}
void Joueur::afficherDeck() const {
    for (auto it = deck.begin(); it != deck.end(); ++it) {
        std::cout << "N°: " << (it - deck.begin()) + 1
                  << ": " << (*it)->getNom() << std::endl;
    }
}

Insecte* Joueur::getQueen() const {
    for (auto it = deck.begin(); it != deck.end(); ++it) {
        if ((*it)->getNom() == "Reine") {
            return *it; // Retourne un pointeur vers la Reine concrète
        }
    }
    return nullptr;
}
int Joueur::getQueenIndex() const {
    for (size_t i = 0; i < deck.size(); ++i) {
        if (deck[i]->getNom() == "Reine") {
            return i;  // Retourne l'index si la reine est trouvée
        }
    }
    return -1;  // Retourne -1 si la reine n'est pas trouvée dans le deck
}
bool Joueur::hasQueen() const {
    for (const auto& insecte : deck) {
        if (insecte->getNom() == "Reine") {
            return true;
        }
    }
    return false;
}
