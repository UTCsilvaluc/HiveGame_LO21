#pragma once
#ifndef INSECTE_H
#define INSECTE_H
#include "Hexagon.h"
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <functional>

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
    Insecte* getDessus(){
        return dessus;
    }
    Insecte* getDessous(){
        return dessous;
    }
    std::string toJson() const;

    virtual std::vector<Hexagon> deplacementsPossibles(std::map<Hexagon, Insecte*> p) = 0;

    std::string getFirstCarac() {
        return std::string(1, this->nom[0]);
    }

    std::vector<Hexagon> placementsPossiblesDeBase(const std::map<Hexagon, Insecte*>& plateau) const;
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
class InsecteFictif : public Insecte {
public:
    InsecteFictif(Hexagon coords, Joueur* player) : Insecte("X", coords, player) {}
    // Implémentation correcte de la fonction pure virtuelle
    std::vector<Hexagon> deplacementsPossibles(std::map<Hexagon, Insecte*> p) override {
        return {}; // Pas de déplacement pour cet insecte fictif
    }
};

class Papillon : public Insecte {
public:
    Papillon(Hexagon coords, Joueur* owner) : Insecte("Papillon", coords, owner) {}


    std::vector<Hexagon> deplacementsPossibles(std::map<Hexagon, Insecte*> p) override {
        return {};
    }
};

// Interface Factory
class InsecteFactory {
public:
    virtual Insecte* createInsecte(const std::string& type, Hexagon coords, Joueur* owner) = 0;
};

class InsecteFactoryImpl {
private:
    std::map<std::string, std::function<Insecte*(Hexagon, Joueur*)>> insecteCreators;
    std::set<std::string> insecteExtensionsActives;  // Extensions activées
    std::vector<std::string> insecteExtensionsDisponibles;  // Extensions disponibles mais non activées

public:
    InsecteFactoryImpl() {
        // Insectes de base
        insecteCreators["Reine"] = [](Hexagon coords, Joueur* owner) { return new ReineAbeille(coords, owner); };
        insecteCreators["Fourmi"] = [](Hexagon coords, Joueur* owner) { return new Fourmi(coords, owner); };
        insecteCreators["Sauterelle"] = [](Hexagon coords, Joueur* owner) { return new Sauterelle(coords, owner); };
        insecteCreators["Coccinelle"] = [](Hexagon coords, Joueur* owner) { return new Coccinelle(coords, owner); };
        insecteCreators["Scarabee"] = [](Hexagon coords, Joueur* owner) { return new Scarabee(coords, owner); };
        insecteCreators["Araignee"] = [](Hexagon coords, Joueur* owner) { return new Araignee(coords, owner); };
        insecteCreators["Moustique"] = [](Hexagon coords, Joueur* owner) { return new Moustique(coords, owner); };
        ajouterExtensionInsecte("Papillon", [](Hexagon coords, Joueur* owner) { return new Papillon(coords, owner); });
    }

    Insecte* createInsecte(const std::string& type, Hexagon coords, Joueur* owner) {
        if (insecteCreators.find(type) != insecteCreators.end()) {
            return insecteCreators[type](coords, owner);
        }
        return nullptr;
    }

    // Création d'un insecte pour une extension activée
    std::vector<Insecte*> createInsecteExtension(const std::string& nomExtension, Hexagon coords, Joueur* owner, int count) {
        std::vector<Insecte*> insectes;
        if (insecteExtensionsActives.find(nomExtension) != insecteExtensionsActives.end()) {
            auto creator = insecteCreators.find(nomExtension);
            if (creator != insecteCreators.end()) {
                for (int i = 0; i < count; ++i) {
                    insectes.push_back(creator->second(coords, owner));
                }
            }
        }
        return insectes;
    }

    // Ajouter une nouvelle extension à la liste des extensions disponibles
    void ajouterExtensionInsecte(const std::string& nomExtension, std::function<Insecte*(Hexagon, Joueur*)> creator) {
        if (std::find(insecteExtensionsDisponibles.begin(), insecteExtensionsDisponibles.end(), nomExtension) == insecteExtensionsDisponibles.end()) {
            insecteCreators[nomExtension] = creator;
            insecteExtensionsDisponibles.push_back(nomExtension);
        }
    }

    // Activer une extension d'insecte (permet d'utiliser cette extension dans le jeu)
    void activerExtension(const std::string& nomExtension) {
        if (std::find(insecteExtensionsDisponibles.begin(), insecteExtensionsDisponibles.end(), nomExtension) != insecteExtensionsDisponibles.end()) {
            insecteExtensionsActives.insert(nomExtension);
        }
    }

    // Désactiver une extension d'insecte (ne permet plus de l'utiliser)
    void desactiverExtension(const std::string& nomExtension) {
        insecteExtensionsActives.erase(nomExtension);
    }

    // Liste des extensions activées
    std::vector<std::string> getInsecteExtensionsActives() {
        return std::vector<std::string>(insecteExtensionsActives.begin(), insecteExtensionsActives.end());
    }

    // Liste des extensions disponibles (non activées)
    std::vector<std::string> getInsecteExtensionsDisponibles() {
        return insecteExtensionsDisponibles;
    }
    std::vector<std::string> getInsecteExtensionsNonActivees() {
        std::vector<std::string> extensionsNonActivees;
        for (const auto& extension : insecteExtensionsDisponibles) {
            if (insecteExtensionsActives.find(extension) == insecteExtensionsActives.end()) {
                extensionsNonActivees.push_back(extension);
            }
        }

        return extensionsNonActivees;
    }
    bool estExtensionActive(const std::string& nomExtension) {
        return insecteExtensionsActives.find(nomExtension) != insecteExtensionsActives.end();
    }
};

// Fonctions supplémentaires
std::vector<Hexagon> deplacementsPossiblesReineAbeille(Hexagon coords, std::map<Hexagon, Insecte*> p);
void deplacementsPossiblesFourmi(Hexagon coords, std::map<Hexagon, Insecte*> p, std::vector<Hexagon>& cheminInsecte, std::set<Hexagon>& deplacements);
void deplacementsPossiblesSauterelle(Hexagon coords, std::map<Hexagon, Insecte*> p);
void deplacementsPossiblesCoccinelle(Hexagon coords, std::map<Hexagon, Insecte*> p, int i, std::vector<Hexagon> &cheminFinal, std::set<Hexagon> &visited);
std::vector<Hexagon> deplacementsPossiblesScarabee(Hexagon coords, std::map<Hexagon, Insecte*> p);
void deplacementsPossiblesAraignee(Hexagon coords, std::map<Hexagon, Insecte*> p, int i, std::vector<Hexagon>& cheminInsecte, std::set<Hexagon>& deplacementsFinaux);
std::vector<Hexagon> deplacementsPossiblesMoustique(Hexagon coords, std::map<Hexagon, Insecte*> p);
std::vector<Hexagon> getVoisins(const Hexagon& coords);
std::vector<Hexagon> casesAdjacentesVides(Hexagon coords, const std::map<Hexagon, Insecte*>& p);
std::vector<Hexagon> casesAdjacentesOccupees(Hexagon coords, const std::map<Hexagon, Insecte*>& p);
void getLongueurChaine(Hexagon coords, std::map<Hexagon, Insecte*> p, std::set<Hexagon> &chemin);
bool getChaineBrisee(Hexagon coords, std::map<Hexagon, Insecte*> p, std::set<Hexagon> &chemin);
bool getGlissementPossible(const Insecte *i, const std::map<Hexagon, Insecte*> p, const Hexagon destination);


#endif // INSECTE_H
