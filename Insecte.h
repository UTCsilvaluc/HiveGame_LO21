#pragma once
#ifndef INSECTE_H
#define INSECTE_H
#include "Hexagon.h"
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

class Joueur; // Déclaration anticipée de Joueur pour éviter l'inclusion circulaire

class Insecte
{
private:
    Hexagon coords;
    Insecte *dessus = nullptr;
    Insecte *dessous = nullptr;
    Joueur *owner;
    std::string nom;

public:
    Insecte& operator =(const Insecte &i){
        if(this != &i){
            coords = i.getCoords();
            dessus = i.dessus;
            dessous = i.dessous;
            owner = i.owner;
            nom = i.getNom();
        }
        return *this;
    }

    // Constructeur modifié pour inclure le propriétaire `owner`
    Insecte(std::string nom, Hexagon coords, Joueur *owner) : coords(coords), nom(nom), owner(owner) {}

    Hexagon getCoords() const { return coords; }
    std::string getNom() const { return nom; }
    Joueur* getOwner() { return owner; }

    void setDessus(Insecte *insecte){
        dessus = insecte;
    }
    void setDessous(Insecte *insecte){
        dessous = insecte;
    }
    void setCoords(Hexagon newCoords){
        coords = newCoords;
    }
    std::string toJson() const;

    virtual std::vector<Hexagon> deplacementsPossibles(std::map<Hexagon, Insecte*> p) = 0;

    std::string getFirstCarac() {
        return std::string(1, this->nom[0]);
    }
};

// Adaptation des constructeurs pour chaque classe d'insecte dérivée
class ReineAbeille : public Insecte {
public:
    ReineAbeille(Hexagon coords, Joueur *owner) : Insecte("Reine", coords, owner) {}
    std::vector<Hexagon> deplacementsPossibles(std::map<Hexagon, Insecte*> p) override;
    bool estEntouree(const std::map<Hexagon, Insecte*>& p) const;
};

class Fourmi : public Insecte {
public:
    Fourmi(Hexagon coords, Joueur *owner) : Insecte("Fourmi", coords, owner) {}
    std::vector<Hexagon> deplacementsPossibles(std::map<Hexagon, Insecte*> p);
};

class Sauterelle : public Insecte {
public:
    Sauterelle(Hexagon coords, Joueur *owner) : Insecte("Sauterelle", coords, owner) {}
    std::vector<Hexagon> deplacementsPossibles(std::map<Hexagon, Insecte*> p);
};

class Coccinelle : public Insecte {
public:
    Coccinelle(Hexagon coords, Joueur *owner) : Insecte("Coccinelle", coords, owner) {}
    std::vector<Hexagon> deplacementsPossibles(std::map<Hexagon, Insecte*> p);
};

class Scarabee : public Insecte {
public:
    Scarabee(Hexagon coords, Joueur *owner) : Insecte("Scarabee", coords, owner) {}
    std::vector<Hexagon> deplacementsPossibles(std::map<Hexagon, Insecte*> p);
};

class Araignee : public Insecte {
public:
    Araignee(Hexagon coords, Joueur *owner) : Insecte("Araignée", coords, owner) {}
    std::vector<Hexagon> deplacementsPossibles(std::map<Hexagon, Insecte*> p);
};

class Moustique : public Insecte {
public:
    Moustique(Hexagon coords, Joueur *owner) : Insecte("Moustique", coords, owner) {}
    std::vector<Hexagon> deplacementsPossibles(std::map<Hexagon, Insecte*> p);
};

// Fonctions supplémentaires
std::vector<Hexagon> deplacementsPossiblesReineAbeille(Hexagon coords, std::map<Hexagon, Insecte*> p);
std::vector<Hexagon> deplacementsPossiblesFourmi(Hexagon coords, std::map<Hexagon, Insecte*> p, std::vector<Hexagon>& cheminInsecte, std::set<Hexagon>& deplacements);
std::vector<Hexagon> deplacementsPossiblesSauterelle(Hexagon coords, std::map<Hexagon, Insecte*> p);
std::vector<Hexagon> deplacementsPossiblesCoccinelle(Hexagon coords, std::map<Hexagon, Insecte*> p);
std::vector<Hexagon> deplacementsPossiblesScarabee(Hexagon coords, std::map<Hexagon, Insecte*> p);
std::vector<Hexagon> deplacementsPossiblesAraignee(Hexagon coords, std::map<Hexagon, Insecte*> p);
std::vector<Hexagon> deplacementsPossiblesMoustique(Hexagon coords, std::map<Hexagon, Insecte*> p);
std::vector<Hexagon> getVoisins(Hexagon coords);
std::vector<Hexagon> casesAdjacentesVides(Hexagon coords, std::map<Hexagon, Insecte*> p);
std::vector<Hexagon> casesAdjacentesOccupees(Hexagon coords, std::map<Hexagon, Insecte*> p);
std::vector<Hexagon> getLongueurChaine(Insecte *i, std::map<Hexagon, Insecte*> p, std::vector<Hexagon> chemin);
bool getChaineBrisee(Insecte *i, std::map<Hexagon, Insecte*> p, std::vector<Hexagon> chemin);
bool getGlissementPossible(const Insecte *i, const std::map<Hexagon, Insecte*> p, const Hexagon destination);

#endif // INSECTE_H
