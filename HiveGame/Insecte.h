#pragma once
#ifndef INSECTE_H
#define INSECTE_H
#include "Hexagon.h"
#include <string>
#include <vector>
#include <map>


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
    Insecte(std::string nom, Hexagon coords) : nom(nom), coords(coords) {}
    Hexagon getCoords() const { return coords; }
    std::string getNom() const { return nom; }
    void setDessus(Insecte *insecte){
        dessus = insecte;
    }
    void setDessous(Insecte *insecte){
        dessous = insecte;
    }
    void setCoords(Hexagon newCoords){
        coords = newCoords;
    }
};


class ReineAbeille : public Insecte {
public:
    ReineAbeille(Hexagon coords) : Insecte("Reine", coords) {}
    std::vector<Hexagon> deplacementsPossibles() const;
};


class Fourmi : public Insecte {
public:
    Fourmi(Hexagon coords) : Insecte("Fourmi", coords) {}
    std::vector<Hexagon> deplacementsPossibles() const;
};


class Sauterelle : public Insecte {
public:
    Sauterelle(Hexagon coords) : Insecte("Sauterelle", coords) {}
    std::vector<Hexagon> deplacementsPossibles() const;
};


class Coccinelle : public Insecte {
public:
    Coccinelle(Hexagon coords) : Insecte("Coccinelle", coords) {}
    std::vector<Hexagon> deplacementsPossibles() const;
};


class Scarabee : public Insecte {
public:
    Scarabee(Hexagon coords) : Insecte("Scarabee", coords) {}
    std::vector<Hexagon> deplacementsPossibles() const;
};


class Araignee : public Insecte {
public:
    Araignee(Hexagon coords) : Insecte("Araignée", coords) {}
    std::vector<Hexagon> deplacementsPossibles() const;
};


class Moustique : public Insecte {
public:
    Moustique(Hexagon coords) : Insecte("Moustique", coords) {}
    std::vector<Hexagon> deplacementsPossibles() const;
};

std::vector<Hexagon> getVoisins(Hexagon coords);
std::vector<Hexagon> casesAdjacentesVides(Hexagon coords, std::map<Hexagon, Insecte*> p);
std::vector<Hexagon> casesAdjacentesOccupees(Hexagon coords, std::map<Hexagon, Insecte*> p);

#endif // INSECTE_H
