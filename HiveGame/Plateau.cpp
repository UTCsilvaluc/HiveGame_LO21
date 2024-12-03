#include "Plateau.h"

void Plateau::ajouterInsecte(Insecte* insecte, Hexagon position) {

    if (plateauMap.count(position)) {
        Insecte* insecteEnDessous = plateauMap[position];
        superposerInsecte(insecteEnDessous, insecte);
        std::cout << "Pion plac� avec succ�s en " << position << "." << std::endl;
    } else {
        plateauMap[position] = insecte;
        insecte->setCoords(position);
        insectesSurPlateau.push_back(insecte);
        mettreAJourLimites();
        std::cout << "Pion plac� avec succ�s en " << position << "." << std::endl;
    }
}
void Plateau::afficherPossibiliteDeplacement(Insecte* insecte, const std::map<Hexagon, Insecte*>& plateau, Joueur* j1, Joueur* j2, Joueur* current) {
    // R�cup�rer les d�placements possibles
    std::vector<Hexagon> deplacements = insecte->deplacementsPossibles(plateau);
    // Afficher les d�placements
    std::cout << "D�placements possibles pour " << insecte->getNom() << " :\n";
    for (const Hexagon& hex : deplacements) {
        std::cout << "[" << hex.getQ() << ", " << hex.getR() << "]\n";
    }
    // Afficher visuellement sur le plateau si besoin
    afficherPlateauAvecPossibilites(deplacements, j1, j2, current);

}
std::vector<Hexagon> Plateau::getPlacementsPossibles(Insecte* insecte) {
    std::vector<Hexagon> placements;
    if (plateauMap.size() == 1) {
        Insecte* seulInsecte = getSeulInsecteSurPlateau();
        if (seulInsecte == nullptr) {
            std::cerr << "Erreur : Aucun insecte trouvé sur le plateau." << std::endl;
            return {};  // Retourne un vecteur vide en cas d'erreur.
        }
        placements = getVoisins(seulInsecte->getCoords());
        std::cout << "quatorze";
    }else {
        std::cout <<"quinze";
        placements = insecte->placementsPossiblesDeBase(plateauMap);
    }
    // Afficher le plateau avec les emplacements possibles marqu�s
    std::cout << "Emplacements possibles pour placer " << insecte->getNom() << " :\n";
    for (const Hexagon& hex : placements) {
        std::cout << "[" << hex.getQ() << ", " << hex.getR() << "]\n";
    }
    std::cout <<"seize";
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
