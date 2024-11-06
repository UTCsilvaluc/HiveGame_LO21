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
        if (n.empty()) {throw std::invalid_argument("Le nom ne peut pas �tre vide.");}
        nom = n;
        // Si un deck est fourni, l'utiliser ; sinon, utiliser le deck par d�faut. Permet de g�rer les extensions en cas de besoin.
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
            std::cout << "Index invalide. Aucune action effectu�e." << std::endl;
        }
    }

};


#endif // JOUEUR_H
