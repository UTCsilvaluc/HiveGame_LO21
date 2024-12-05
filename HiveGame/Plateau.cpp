#include "Plateau.h"

void Plateau::ajouterInsecte(Insecte* insecte, Hexagon position) {

    if (plateauMap.count(position)) {
        Insecte* insecteEnDessous = plateauMap[position];
        superposerInsecte(insecteEnDessous, insecte);
        std::cout << "Pion place avec succes en " << position << "." << std::endl;
    } else {
        plateauMap[position] = insecte;
        insecte->setCoords(position);
        insectesSurPlateau.push_back(insecte);
        mettreAJourLimites();
        std::cout << "Pion place avec succes en " << position << "." << std::endl;
    }
}
void Plateau::afficherPossibilitesDeplacements(const Insecte* insecte, const std::vector<Hexagon> deplacementsPossibles) const {
    std::cout << "Déplacements possibles pour " << insecte->getNom() << " : \n";
    for (size_t i = 0; i < deplacementsPossibles.size(); ++i) {
        std::cout << i + 1 << ". (" << deplacementsPossibles[i].getQ() << ", " << deplacementsPossibles[i].getR() << ")\n";
    }
    std::cout << "-1. Annuler le déplacement\n";

}
void Plateau::afficherPossibilitesPlacements(const Insecte* insecte, const std::vector<Hexagon> placementsPossibles) const{
    std::cout << "Placements possibles pour " << insecte->getNom() << " : \n";
    for (size_t i = 0; i < placementsPossibles.size(); ++i) {
        std::cout << i + 1 << ". (" << placementsPossibles[i].getQ() << ", " << placementsPossibles[i].getR() << ")\n";
    }
    std::cout << "-1. Annuler le placement\n";
}

std::vector<Hexagon> Plateau::getPlacementsPossibles(Insecte* insecte) {
    std::vector<Hexagon> placements;
    if (plateauMap.size() == 1) {
        Insecte* seulInsecte = getSeulInsecteSurPlateau();
        if (seulInsecte == nullptr) {
            std::cerr << "Erreur : Aucun insecte trouve sur le plateau." << std::endl;
            return {};  // Retourne un vecteur vide en cas d'erreur.
        }
        placements = getVoisins(seulInsecte->getCoords());
    }else {
        placements = insecte->placementsPossiblesDeBase(plateauMap);
    }
    return placements;
}

void Plateau::afficherPlateauAvecPossibilites(const std::vector<Hexagon>& emplacementsPossibles, Joueur* j1, Joueur* j2, Joueur* current) {
    // Cr�er une copie temporaire du plateau pour l'affichage
    std::map<Hexagon, Insecte*> plateauTemp = plateauMap;
    // Ajouter des insectes fictifs aux emplacements possibles dans le plateau temporaire
    for (const Hexagon& hex : emplacementsPossibles) {
        if (plateauTemp.find(hex) == plateauTemp.end()) {  // Si la position est vide
            plateauTemp[hex] = new InsecteFictif(hex, current);  // Ajouter un insecte fictif
        }
    }
    // Afficher le plateau avec les insectes fictifs en utilisant afficherPlateau
    std::swap(plateauMap, plateauTemp);  // �change temporairement plateauMap et plateauTemp
    mettreAJourLimites();
    afficherPlateau(j1, j2);
    std::swap(plateauMap, plateauTemp);  // Restaure plateauMap
    // Nettoyer les insectes fictifs ajout�s dans le plateau temporaire
    for (const Hexagon& hex : emplacementsPossibles) {
        if (plateauTemp[hex]->getNom() == "?") {  // V�rifie si c'est un insecte fictif
            delete plateauTemp[hex];
            plateauTemp.erase(hex);
        }
    }
}
