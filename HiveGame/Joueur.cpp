#include "Joueur.h"
std::vector<Insecte*> deckDeBase(Joueur *joueur){
    std::vector<Insecte*> newDeck;
    for (int i = 0; i < 2; ++i) { newDeck.push_back(new Araignee(Hexagon(0, 0) , joueur)); }  // Araignée x2
    for (int i = 0; i < 2; ++i) { newDeck.push_back(new Scarabee(Hexagon(0, 0) , joueur)); }  // Scarabée x2
    for (int i = 0; i < 3; ++i) { newDeck.push_back(new Fourmi(Hexagon(0, 0) , joueur)); }    // Fourmi x3
    for (int i = 0; i < 3; ++i) { newDeck.push_back(new Sauterelle(Hexagon(0, 0) , joueur)); } // Sauterelle x3
    newDeck.push_back(new Coccinelle(Hexagon(0, 0) , joueur));  // Coccinelle x1
    newDeck.push_back(new Moustique(Hexagon(0, 0) , joueur));   // Moustique x1
    newDeck.push_back(new ReineAbeille(Hexagon(0, 0) , joueur));  // Reine Abeille x1
    return newDeck;
}
void Joueur::afficherDeck() const {
    for (auto it = deck.begin(); it != deck.end(); ++it) {
        std::cout <<(it - deck.begin()) + 1
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
    return -1;
}
bool Joueur::hasQueen() const {
    for (const auto& insecte : deck) {
        if (insecte->getNom() == "Reine") {
            return true;
        }
    }
    return false;
}

#include <sstream>
std::string Joueur::toJson() const {
    std::stringstream jsonData;
    jsonData << "{\n";
    jsonData << "  \"nom\": \"" << nom << "\",\n";

    jsonData << "  \"deck\": [";
    for (size_t i = 0; i < deck.size(); ++i) {
        if (i != 0) {
            jsonData << ", ";  // Séparateur entre les insectes
        }
        jsonData << deck[i]->toJson();  // Appel de toJson pour chaque Insecte
    }
    jsonData << "]\n";

    jsonData << "}";
    return jsonData.str();
}
