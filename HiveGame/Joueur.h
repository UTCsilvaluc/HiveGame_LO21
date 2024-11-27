#pragma once
#ifndef JOUEUR_H
#define JOUEUR_H
#include "Insecte.h"
#include <vector>

std::vector<Insecte*> deckDeBase(Joueur *joueur);
class Joueur
{
private:
    std::string nom;
    std::vector<Insecte*> deck;
public:
    Joueur(const std::string& nom) : nom(nom) , deck(deckDeBase(this)) {}
    Joueur(std::string n, std::vector<Insecte*> d) {
        if (n.empty()) {throw std::invalid_argument("Le nom ne peut pas être vide.");}
        nom = n;
        // Si un deck est fourni, l'utiliser ; sinon, utiliser le deck par défaut. Permet de gérer les extensions en cas de besoin.
        deck = d.empty() ? deckDeBase(this) : d;
    }
    const std::string &getName() const {return nom;}
    const std::vector<Insecte*>& getDeck() const { return deck; }
    Insecte* getQueen() const;
    int getQueenIndex() const;
    bool hasQueen() const;
    void afficherDeck() const;
    std::string toJson() const;
    ~Joueur() {
        for (Insecte* insecte : deck) {
            delete insecte;
        }
    }

    size_t getDeckSize() const {
        return deck.size();
    }

    Insecte *getInsecteByIndex(unsigned int i){
        if (i >= deck.size()){return nullptr;}
        return deck[i];
    }
    void retirerInsecte(unsigned int index) {
        if (index < deck.size()) {
            deck.erase(deck.begin() + index);  // Retirer du deck
        } else {
            std::cout << "Index invalide. Aucune action effectuée." << std::endl;
        }
    }
    Insecte* contientInsecte(const std::string& nomInsecte) const {
        for (Insecte* insecte : deck) {
            if (insecte->getNom() == nomInsecte) {
                return insecte;
            }
        }
        return nullptr;
    }

    void ajouterInsecte(Insecte* insecte) {
        if (insecte == nullptr) {
            std::cerr << "Erreur : Impossible d'ajouter un insecte nul au deck." << std::endl;
            return;
        }
        deck.push_back(insecte);
}



};


#endif // JOUEUR_H
