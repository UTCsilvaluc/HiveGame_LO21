#pragma once
#ifndef JOUEUR_H
#define JOUEUR_H
#include "Insecte.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <random>
#include <stdexcept>

std::vector<Insecte*> deckDeBase(Joueur *joueur);

class Joueur
{
private:
    std::string nom;
    std::vector<Insecte*> deck;
public:
    Joueur(const std::string& nom) : nom(nom), deck(deckDeBase(this)) {}
    Joueur(std::string n, std::vector<Insecte*> d) {
        if (n.empty()) { throw std::invalid_argument("Le nom ne peut pas être vide."); }
        nom = n;
        deck = d.empty() ? deckDeBase(this) : d;
    }
    const std::string &getName() const { return nom; }
    const std::vector<Insecte*>& getDeck() const { return deck; }
    Insecte* getQueen() const;
    int getQueenIndex() const;
    bool hasQueen() const;
    void afficherDeck() const;
    std::string toJson() const;
    virtual ~Joueur() {
        for (Insecte* insecte : deck) {
            delete insecte;
        }
    }

    size_t getDeckSize() const {
        return deck.size();
    }

    Insecte* getInsecteByIndex(unsigned int i) {
        if (i >= deck.size()) { std::cout<<"nul a chier"; return nullptr; }
        return deck[i];
    }

    void retirerInsecte(unsigned int index) {
        if (index < deck.size()) {
            deck.erase(deck.begin() + index);
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

    std::vector<Insecte*> getInsectesDuJoueur(const std::map<Hexagon, Insecte*>& plateauMap) const {
        std::vector<Insecte*> insectesDuJoueur;
        for (const auto& pair : plateauMap) {
            Insecte* insecte = pair.second;
            if (insecte->getOwner() == this) {
                insectesDuJoueur.push_back(insecte);
            }
        }
        return insectesDuJoueur;
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

    virtual int randomPionIndexChoice(const std::map<Hexagon, Insecte*>& plateauMap) {
        throw std::logic_error("La méthode randomPionChoice() n'est pas applicable pour un joueur humain.");
    }
};

class JoueurIA : public Joueur {
private:
    std::default_random_engine generator;  // Générateur de nombres aléatoires

public:
    JoueurIA(const std::string& nom) : Joueur(nom) {
        // Initialiser le générateur de nombres aléatoires avec la graine actuelle
        std::random_device rd;
        generator = std::default_random_engine(rd());
    }

    // Fonction pour choisir aléatoirement entre "poser" ou "déplacer"
    int randomChoice() override {
        std::uniform_int_distribution<int> distribution(1, 2);  // Distribution entre 1 et 2
        return distribution(generator);  // Retourne 1 ("poser") ou 2 ("déplacer")
    }

    // Fonction pour choisir un Hexagon aléatoire parmi les options de déplacement disponibles
    Hexagon randomHexagonChoice(const std::vector<Hexagon>& options) override {
        if (options.empty()) {
            throw std::runtime_error("Aucun déplacement possible");
        }
        std::uniform_int_distribution<size_t> distribution(0, options.size() - 1);
        return options[distribution(generator)];
    }

    // Fonction pour choisir un Insecte aléatoire du deck du joueur
    int randomDeckChoice() override {
        if (getDeckSize() == 0) {
            throw std::runtime_error("Deck vide");
        }
        std::uniform_int_distribution<int> distribution(1, getDeckSize());
        return distribution(generator);
    }

    // Fonction pour choisir aléatoirement un pion du plateau appartenant au joueur
    int randomPionIndexChoice(const std::map<Hexagon, Insecte*>& plateauMap) override {
        // Filtrer les pions appartenant au joueur
        std::vector<Insecte*> pionsJoueur = getInsectesDuJoueur(plateauMap);

        if (pionsJoueur.empty()) {
            throw std::runtime_error("Aucun pion appartenant au joueur sur le plateau");
        }

        std::uniform_int_distribution<int> distribution(0,pionsJoueur.size() - 1);
        return distribution(generator);
    }
};

enum ActionType { PLACER = 1, DEPLACER = 2, AUCUN = 0 };

class JoueurIANiveau2 : public JoueurIA {
private:
    ActionType actionChoisie;  // PLACER, DEPLACER, AUCUN
    Hexagon positionChoisie;   // Pour mémoriser la position choisie
    Insecte* insecteChoisi;    // Pour mémoriser l'insecte choisi (peut être dans le deck ou sur le plateau)
public:
    JoueurIANiveau2(std::string nom) : JoueurIA(nom), actionChoisie(AUCUN), positionChoisie(), insecteChoisi(nullptr) {}

    void choisirAction(std::map<Hexagon, Insecte*>& plateau);
    void choisirDeplacementOuPlacement(std::map<Hexagon, Insecte*>& plateau);

    int getActionPourGameMaster() const { return static_cast<int>(actionChoisie); }
    Hexagon getPositionChoisie() const { return positionChoisie; }
    Insecte* getInsecteChoisi() const { return insecteChoisi; }
};

#endif // JOUEUR_H
