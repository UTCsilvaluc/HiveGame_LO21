#pragma once
#ifndef JOUEUR_H
#define JOUEUR_H
#include "Insecte.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <random>
#include <stdexcept>
#include <map>
#include <limits>

int getInput(const std::string& prompt, int minValue, int maxValue, unsigned int tour);

int getInput(const std::string& prompt, int minValue, int maxValue);

std::vector<Insecte*> deckDeBase(Joueur *joueur);

class Joueur{
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
        if (i >= deck.size()) {return nullptr; }
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

    // Méthodes virtuelles pures
    virtual int getInputForAction() = 0; // Choix entre déplacer, placer ou annuler
    virtual Hexagon getFirstPlacementCoordinates(int minQ, int maxQ, int minR, int maxR, unsigned int tour) = 0; // Coordonnées du premier placement
    virtual int getInputIndexForInsectToMove(std::vector<Insecte*> insectesDuJoueur) = 0; // Choisir un insecte à déplacer
    virtual int getInputForMovement(std::vector<Hexagon> deplacementsPossibles) = 0; // Choisir un mouvement pour un insecte
    virtual int getInputForDeckIndex() = 0; // Choisir un insecte du deck à placer
    virtual int getInputForPlacementIndex(std::vector<Hexagon> placementsPossibles) = 0; // Choisir un emplacement pour placer un insecte
};

class JoueurHumain : public Joueur{

public:
    JoueurHumain(const std::string& nom) : Joueur(nom) {}

    int getInputForAction() {
        int choice = 0;
        while (true) {
            std::cout << "Que voulez-vous faire ?\n"
                      << "1 - D�placer un pion \n"
                      << (getDeckSize() > 0 ? "2 - Placer un pion \n" : "")
                      << "3 - Retour arri�re (Annuler la derni�re action)\n";
            std::cin >> choice;

            if (std::cin.fail() || (choice != 1 && (choice != 2 || getDeckSize() == 0)) && choice != 3) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Merci de saisir 1, 2 (si deck disponible), ou 3 pour retourner en arri�re.\n";
            } else {
                break; // Sortir de la boucle si l'entr�e est valide
            }
        }
        return choice;
    }

    Hexagon getFirstPlacementCoordinates(int minQ, int maxQ, int minR, int maxR, unsigned int tour){
        std::cout << "Le plateau est vide, vous devez entrer les coordonnées directement.\n";
        int x = getInput("Abscisse pour poser le pion : ", minQ - 1, maxQ + 1 , tour);
        int y = getInput("Ordonnée pour poser le pion : ", minR - 1, maxR + 1 , tour);
        return Hexagon(x,y);
    }

    int getInputForDeckIndex(){
        return getInput("Quel pion souhaitez-vous poser ? ", 1, getDeckSize()) - 1;
    }

    int getInputForPlacementIndex(std::vector<Hexagon> placementsPossibles){
        return getInput("Choisissez un emplacement ou entrez -1 pour annuler : ", -1, placementsPossibles.size());
    }

    int getInputIndexForInsectToMove(std::vector<Insecte*> insectesDuJoueur){
        return getInput("Entrez l'index de l'insecte à sélectionner (ou -1 pour annuler) : ", -1, insectesDuJoueur.size() - 1);
    }

    int getInputForMovement(std::vector<Hexagon> deplacementsPossibles){
        return getInput("Choisissez un emplacement ou entrez -1 pour annuler : ", -1, deplacementsPossibles.size());
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

    int getInputForAction() {
    }

    Hexagon getFirstPlacementCoordinates(int minQ, int maxQ, int minR, int maxR, unsigned int tour){
    }

    int getInputForDeckIndex(){
    }

    int getInputForPlacementIndex(std::vector<Hexagon> placementsPossibles){
    }

    int getInputIndexForInsectToMove(std::vector<Insecte*> insectesDuJoueur){
    }

    int getInputForMovement(std::vector<Hexagon> deplacementsPossibles){
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

enum HeuristiqueType { PROTEGER_REINE, ATTAQUER_REINE, COMPACTER_RUCHE, AUCUN_HEURISTIQUE }; // Ajout d'une énumération pour les types d'heuristiques

enum ActionType { PLACER = 1, DEPLACER = 2, AUCUN_ACTION = 0 };

class JoueurIANiveau2 : public JoueurIA {
private:
    ActionType actionChoisie;  // PLACER, DEPLACER, AUCUN
    Hexagon positionChoisie;   // Pour mémoriser la position choisie
    Insecte* insecteChoisi;    // Pour mémoriser l'insecte choisi (peut être dans le deck ou sur le plateau)
public:
    JoueurIANiveau2(std::string nom) : JoueurIA(nom), actionChoisie(AUCUN_ACTION), positionChoisie(), insecteChoisi(nullptr) {}

    int getActionPourGameMaster() const { return static_cast<int>(actionChoisie); }
    Hexagon getPositionChoisie() const { return positionChoisie; }
    Insecte* getInsecteChoisi() const { return insecteChoisi; }

    HeuristiqueType choisirHeuristique(Joueur* joueur, Joueur* adversaire, const std::map<Hexagon, Insecte*>& plateau) {
        // Trouver la Reine du joueur
        Insecte* reine = trouverReine(joueur, plateau);
        Insecte* reineAdverse = trouverReine(adversaire, plateau);

        if (reine == nullptr || reineAdverse == nullptr) {
            return AUCUN_HEURISTIQUE;
        }

        // Récupérer les voisins de la Reine
        std::vector<Hexagon> voisinsReine = getVoisins(reine->getCoords());
        std::vector<Hexagon> ennemisVoisins = reine->getVoisinsEnnemis(voisinsReine, plateau);

        // Si la Reine est en danger (trop de voisins ennemis), choisir de la protéger
        if (ennemisVoisins.size() > 3) {
            return PROTEGER_REINE;
        }

        // Vérifier si l'un des insectes alliés peut atteindre la Reine adverse
        for (const auto& [position, insecte] : plateau) {
            if (insecte != nullptr && insecte->getOwner() == joueur) {
                std::vector<Hexagon> deplacementsPossibles = insecte->deplacementsPossibles(plateau);
                if (std::find(deplacementsPossibles.begin(), deplacementsPossibles.end(), reineAdverse->getCoords()) != deplacementsPossibles.end()) {
                    return ATTAQUER_REINE;
                }
            }
        }

        // Sinon, jouer de manière défensive pour compacter la ruche
        return COMPACTER_RUCHE;
    }

    void choisirAction(std::map<Hexagon, Insecte*>& plateau) {
        // Supposons que vous ayez des pointeurs vers le joueur et l'adversaire
        Joueur* joueur = this;
        Joueur* adversaire = nullptr; // Initialiser correctement l'adversaire

        // Choisir l'heuristique en utilisant la fonction déterministe
        HeuristiqueType heuristique = choisirHeuristique(joueur, adversaire, plateau);

        // Ensuite, appliquer la logique associée à l'heuristique choisie
        switch (heuristique) {
            case PROTEGER_REINE:
                deplacerPourProtegerReine(trouverReine(joueur, plateau), plateau);
                break;
            case ATTAQUER_REINE:
                // Implémenter la logique d'attaque de la Reine adverse
                break;
            case COMPACTER_RUCHE:
                // Implémenter la logique pour compacter la ruche
                break;
            default:
                // Si aucune heuristique particulière ne s'applique, faire un coup aléatoire
                defaultAction(plateau);
                break;
        }
    }

    void defaultAction(std::map<Hexagon, Insecte*>& plateau) {
        // Choisir aléatoirement entre déplacer ou placer un insecte
        if (randomChoice()==1) {
            actionChoisie = PLACER;
            insecteChoisi = getInsecteByIndex(randomDeckChoice());
            std::vector<Hexagon> placementsPossibles = insecteChoisi->getPlacementsPossibles(plateau);
            positionChoisie = randomHexagonChoice(placementsPossibles);
        } else {
            actionChoisie = DEPLACER;
            int position = randomPionIndexChoice(plateau);
            insecteChoisi = getInsectesDuJoueur(plateau)[position];
            std::vector<Hexagon> deplacementsPossibles = insecteChoisi->deplacementsPossibles(plateau);
            positionChoisie = randomHexagonChoice(deplacementsPossibles);
        }
    }

    void deplacerPourProtegerReine(Insecte* reine, std::map<Hexagon, Insecte*>& plateau) {
        // Récupérer les voisins de la Reine et déterminer les ennemis
        std::vector<Hexagon> voisinsReine = getVoisins(reine->getCoords());
        std::vector<Hexagon> ennemisVoisins = reine->getVoisinsEnnemis(voisinsReine, plateau);

        // Vérifier si la Reine elle-même peut être déplacée pour réduire le nombre de voisins ennemis
        if (ennemisVoisins.size() > 3) {
            std::vector<Hexagon> deplacementsReine = reine->deplacementsPossibles(plateau);
            for (const Hexagon& deplacement : deplacementsReine) {
                // Si le déplacement éloigne la Reine de ses ennemis
                std::vector<Hexagon> nouveauxVoisins = getVoisins(deplacement);
                std::vector<Hexagon> nouveauxEnnemisVoisins = reine->getVoisinsEnnemis(nouveauxVoisins, plateau);
                if (nouveauxEnnemisVoisins.size() < ennemisVoisins.size()) {
                    actionChoisie = DEPLACER;
                    insecteChoisi = reine;
                    positionChoisie = deplacement;
                    return;
                }
            }
        }

        // Compter le nombre de voisins alliés
        std::vector<Insecte*> voisinsAllies;
        for (const auto& voisin : voisinsReine) {
            auto it = plateau.find(voisin);
            if (it != plateau.end() && it->second != nullptr) {
                if (it->second->getOwner() == reine->getOwner()) {
                    voisinsAllies.push_back(it->second);
                }
            }
        }

        // Tenter de déplacer un allié pour protéger la Reine
        for (Insecte* allie : voisinsAllies) {
            std::vector<Hexagon> deplacementsPossibles = allie->deplacementsPossibles(plateau);
            for (const Hexagon& deplacement : deplacementsPossibles) {
                // Si le déplacement éloigne l'insecte des voisins de la Reine
                if (std::find(voisinsReine.begin(), voisinsReine.end(), deplacement) == voisinsReine.end()) {
                    // Déterminer le déplacement
                    actionChoisie = DEPLACER;
                    insecteChoisi = allie;
                    positionChoisie = deplacement;
                    return;  // Un seul mouvement suffit
                }
            }
        }

        // Si aucune action n'a été trouvée
        actionChoisie = AUCUN_ACTION;
        insecteChoisi = nullptr;
    }
};




#endif // JOUEUR_H
