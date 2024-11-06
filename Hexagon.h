#ifndef HEXAGON_H
#define HEXAGON_H
#include <cstdlib>
#include <iostream>

class Hexagon {
private:
    int q;  // Coordonn�e axiale q (colonne)
    int r;  // Coordonn�e axiale r (ligne)
public:
    int getQ() const {return q;}
    int getR() const {return r;}
    Hexagon(int q = 0, int r = 0) : q(q), r(r) {}
    std::string toJson() const;

    // Calculer la distance hexagonale , voisin => distance = 1
    int distance(const Hexagon& other) const {
        return (abs(q - other.q) + abs(r - other.r) + abs((q + r) - (other.q + other.r))) / 2;
    }
    bool estVoisin(const Hexagon& autre) const {
        return distance(autre) == 1;  // Voisins si la distance est 1
    }
    bool operator==(const Hexagon& other) const {return q == other.q && r == other.r;}
    void afficherCoordonnees() const {
        std::cout << "Coordonn�es: (" << q << ", " << r << ")" << std::endl;
    }
    void deplacer(const Hexagon& autre) {
        q = autre.q;
        r = autre.r;
    }
    // Op�rateur de comparaison pour std::map sinon erreur , permet d'ordonner les �l�ments et pas de doublon
    bool operator<(const Hexagon& other) const {
        // Comparer d'abord par q, puis par r
        if (q != other.q) {
            return q < other.q;
        }
        return r < other.r;
    }
    friend std::ostream& operator<<(std::ostream& os, const Hexagon& hex);

};



#endif

/*
Direction	(dq, dr)
Droite	(1, 0)
Droite-Haut	(1, -1)
Gauche-Haut	(0, -1)
Gauche	(-1, 0)
Gauche-Bas	(-1, 1)
Droite-Bas	(0, 1)
*/
