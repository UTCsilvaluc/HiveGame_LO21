#ifndef GAMEMASTER_H
#define GAMEMASTER_H

#include "Joueur.h"
#include "Plateau.h"
#include <iostream>
#include <memory>
#include <limits>
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
public:
    bool hasPlayQueen(Joueur *currentPlayer);
    GameMaster() : joueur1(nullptr), joueur2(nullptr) , mode(0) {}
    Insecte* selectionnerInsecte();
    GameMaster(Plateau plateau) : joueur1(nullptr), joueur2(nullptr) , mode(0) , plateau(plateau){}
    void startGame();

    void choixExtensions(){}//Objet publique extension qui contient une liste d'extension et propose de les choisir
    void jouer();
    int getInputForAction(Joueur* current);
    bool detectWinner(Joueur *current);
    // Destructeur pour libérer la mémoire
    ~GameMaster();
};



#endif // GAMEMASTER_H
