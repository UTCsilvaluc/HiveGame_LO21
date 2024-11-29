#ifndef GAMEMASTER_H
#define GAMEMASTER_H

#include "Joueur.h"
#include "Plateau.h"
#include "Action.h"
#include <iostream>
#include <memory>
#include <limits>
#include <stack>

int getInput(const std::string& prompt, int minValue, int maxValue);
bool positionEstValide(const Hexagon& position, const std::vector<Hexagon>& deplacementsPossibles);
class GameMaster {
private:
    Plateau plateau;
    Joueur *joueur1;
    Joueur *joueur2;
    unsigned int mode;
    unsigned int tour;
    void deplacerPion(Joueur* current);
    void placerPion(Joueur* current, bool b);
    std::stack<Action*> actionsPile;
    unsigned int maxRetourArriere;
public:
    bool hasPlayQueen(Joueur *currentPlayer);
    GameMaster() : joueur1(nullptr), joueur2(nullptr) , mode(0) {}
    Insecte* selectionnerInsecte();
    GameMaster(Plateau plateau, unsigned int maxRetourArriere = 5)
        : joueur1(nullptr), joueur2(nullptr), mode(0), tour(0), plateau(plateau), maxRetourArriere(maxRetourArriere) {}
    void startGame();
    void choixExtensions(){}//Objet publique extension qui contient une liste d'extension et propose de les choisir
    void jouer();
    int getInputForAction(Joueur* current);
    bool detectWinner(Joueur *joueur1 , Joueur *joueur2);
    void saveGame();
    bool verifierProprietairePion(Joueur* current, Insecte* insecte);
    bool verifierDeplacementsPossiblesPourTousLesInsectes(Joueur* current);
    void undoLastAction();
    // Destructeur pour libérer la mémoire
    ~GameMaster();
};



#endif // GAMEMASTER_H
