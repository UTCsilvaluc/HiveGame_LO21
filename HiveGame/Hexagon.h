#ifndef HEXAGON_H
#define HEXAGON_H
#include <cstdlib>
#include <iostream>
#include <vector>

class Hexagon {
private:
    int q;  // Coordonnée axiale q (colonne)
    int r;  // Coordonnée axiale r (ligne)
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
        std::cout << "Coordonnées: (" << q << ", " << r << ")" << std::endl;
    }
    void deplacer(const Hexagon& autre) {
        q = autre.q;
        r = autre.r;
    }
    // Opérateur de comparaison pour std::map sinon erreur , permet d'ordonner les éléments et pas de doublon
    bool operator<(const Hexagon& other) const {
        // Comparer d'abord par q, puis par r
        if (q != other.q) {
            return q < other.q;
        }
        return r < other.r;
    }
    bool operator!=(const Hexagon& other) const {
        if (q != other.q || r != other.r) {
            return false;
        }
        return true;
    }
    friend std::ostream& operator<<(std::ostream& os, const Hexagon& hex);

    std::vector<Hexagon> getVoisins() const {
        std::vector<Hexagon> voisins;
        if (r % 2 == 0) {  // Colonne paire
            voisins = {
                Hexagon(q - 1, r - 1),
                Hexagon(q, r - 1),
                Hexagon(q + 1, r),
                Hexagon(q, r + 1),
                Hexagon(q - 1, r + 1),
                Hexagon(q - 1, r)
            };
        } else {  // Colonne impaire
            voisins = {
                Hexagon(q, r - 1),
                Hexagon(q + 1, r - 1),
                Hexagon(q+1, r),
                Hexagon(q+1, r+1),
                Hexagon(q, r+1),
                Hexagon(q-1, r)
            };
        }
        return voisins;
    }

};



#endif
