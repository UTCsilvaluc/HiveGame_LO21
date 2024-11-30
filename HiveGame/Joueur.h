#pragma once
#ifndef JOUEUR_H
#define JOUEUR_H
#include "Insecte.h"
#include "Plateau.h" //besoin des données du plateau pour implémenter une IA
#include <vector>
#include <cstdlib>
#include <ctime>

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

    // Fonctions virtuelles pour l'IA
    virtual int randomChoice() {
        throw std::logic_error("La méthode randomChoice() n'est pas applicable pour un joueur humain.");
    }

    virtual Hexagon randomHexagonChoice(const std::vector<Hexagon>& options) {
        throw std::logic_error("La méthode randomHexagonChoice() n'est pas applicable pour un joueur humain.");
    }

    virtual int randomDeckChoice() {
        throw std::logic_error("La méthode randomDeckChoice() n'est pas applicable pour un joueur humain.");
    }

    virtual Hexagon randomPionChoice(const std::map<Hexagon, Insecte*>& plateauMap) {
        throw std::logic_error("La méthode randomPionChoice() n'est pas applicable pour un joueur humain.");
    }
};

class JoueurIA : public Joueur {
public:
    JoueurIA(const std::string& nom) : Joueur(nom) {
        // Initialiser la graine aléatoire une seule fois
        static bool initialized = false;
        if (!initialized) {
            std::srand(std::time(nullptr));
            initialized = true;
        }
    }

    // Fonction pour choisir aléatoirement entre "poser" ou "déplacer"
    int randomChoice() {
        return (std::rand() % 2) + 1; // Retourne 1 ("poser") ou 2 ("déplacer")
    }

    // Fonction pour choisir un Hexagon aléatoire parmi les options de déplacement disponibles
    Hexagon randomHexagonChoice(const std::vector<Hexagon>& options) {
        if (options.empty()) {
            throw std::runtime_error("Aucun déplacement possible");
        }
        int index = std::rand() % options.size();
        return options[index];
    }

    // Fonction pour choisir un Insecte aléatoire du deck du joueur
    int randomDeckChoice() {
        if (getDeckSize() == 0) {
            throw std::runtime_error("Deck vide");
        }
        return (std::rand() % getDeckSize()) + 1; // Retourne un index entre 1 et la taille du deck
    }

    // Fonction pour choisir aléatoirement un pion du plateau appartenant au joueur
    Hexagon randomPionChoice(const std::map<Hexagon, Insecte*>& plateauMap) {
        // Filtrer les pions appartenant au joueur
        std::vector<Hexagon> pionsJoueur;
        for (const auto& entry : plateauMap) {
            if (entry.second->getOwner() == this) {
                pionsJoueur.push_back(entry.first);
            }
        }

        if (pionsJoueur.empty()) {
            throw std::runtime_error("Aucun pion appartenant au joueur sur le plateau");
        }

        // Choisir un pion aléatoire parmi ceux appartenant au joueur
        int index = std::rand() % pionsJoueur.size();
        return pionsJoueur[index];
    }
};


#endif // JOUEUR_H
